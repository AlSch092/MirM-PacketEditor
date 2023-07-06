#include "PacketParsing.hpp"
#include "Tasker.hpp"

std::list<uint16_t> IgnoredList;
std::queue<PacketWriter*> SendPacketQueue;
std::queue<PacketWriter*> RecvPacketQueue;

extern Tasker* g_Robot;
extern SOCKET lpGameSocket;

int PacketHelper::rand_lim(int limit)
{
	int divisor = RAND_MAX / (limit + 1);
	int retval;

	do {
		retval = rand() / divisor;
	} while (retval > limit);

	return retval;
}

LPBYTE PacketHelper::ToPacketFormat(const CHAR* input) //wrote this routine in 2015, not a prime example of 'clean' code but it works just fine
{
	if (input == NULL)
		return NULL;

	int in_len = strlen(input);

	if (strlen(input) > 4096)
		return NULL;

	char* fixedString = new char[in_len + 1];
	LPBYTE bytestring = NULL;

	//strip spaces, bad text
	int i; int j = 0;

	for (i = 0; input[i] != '\0'; i++) {
		
		if ((input[i] >= 'A' && input[i] <= 'F') || (input[i] >= '0' && input[i] <= '9') || (input[i] >= 'a' && input[i] <= 'f'))  {
			fixedString[j] = input[i];
			j++;
		}
		else if (input[i] == '*') {

			int random = rand_lim(15);

			if (random >= 0 && random <= 9)
				fixedString[j] = random + 0x30;
			else if (random >= 9 && random <= 15)
				fixedString[j] = random + 0x55;

			j++;
		}
		else { //found non-hex digit in string
			delete[] fixedString;
			return NULL;
		}
	}

	bytestring = (unsigned char*)malloc((j * 2) + 1);

	j = 0;

	for (i = 0; fixedString[i] != '\0'; i++) {

		if (i % 2 == 0) { //even number iterator

			if (fixedString[i] >= 'a' && fixedString[i] <= 'f') {

				bytestring[j] = ((fixedString[i] - 0x57) << 4);

				if (fixedString[i + 1] >= 'A' && fixedString[i + 1] <= 'F')
					bytestring[j] = bytestring[j] + (fixedString[i + 1] - 0x37);
				else if (fixedString[i + 1] >= '0' && fixedString[i + 1] <= '9')
					bytestring[j] = bytestring[j] + (fixedString[i + 1] - 0x30);
				else if (fixedString[i + 1] >= 'a' && fixedString[i + 1] <= 'f')
					bytestring[j] = bytestring[j] + (fixedString[i + 1] - 0x57);

			}
			else if (fixedString[i] >= '0' && fixedString[i] <= '9') {

				bytestring[j] = ((fixedString[i] - 0x30) << 4);

				if (fixedString[i + 1] >= 'A' && fixedString[i + 1] <= 'F')
					bytestring[j] = bytestring[j] + (fixedString[i + 1] - 0x37);
				else if (fixedString[i + 1] >= '0' && fixedString[i + 1] <= '9')
					bytestring[j] = bytestring[j] + (fixedString[i + 1] - 0x30);
				else if (fixedString[i + 1] >= 'a' && fixedString[i + 1] <= 'f')
					bytestring[j] = bytestring[j] + (fixedString[i + 1] - 0x57);

			}
			else if (fixedString[i] >= 'A' && fixedString[i] <= 'F') {

				bytestring[j] = ((fixedString[i] - 0x37) << 4);

				if (fixedString[i + 1] >= 'A' && fixedString[i + 1] <= 'F')
					bytestring[j] = bytestring[j] + (fixedString[i + 1] - 0x37);
				else if (fixedString[i + 1] >= '0' && fixedString[i + 1] <= '9')
					bytestring[j] = bytestring[j] + (fixedString[i + 1] - 0x30);
				else if (fixedString[i + 1] >= 'a' && fixedString[i + 1] <= 'f')
					bytestring[j] = bytestring[j] + (fixedString[i + 1] - 0x57);
			}

			j++;
			i++;
		}
	}

	delete[] fixedString;
	return bytestring;
}

std::string PacketHelper::ToString(LPBYTE packetStr, int byteLength)
{
	if (byteLength <= 0)
		return NULL;

	std::string newStr = std::string();
	CHAR* convertStr = (CHAR*)malloc(byteLength * 3); //* 3 since 00[ ] an extra 0 with a space for each byte in the str.

	for (int i = 0; i < byteLength; i++) {
		byte ch = packetStr[i];
		sprintf(&convertStr[i], "%.2X", ch);
		newStr.append(&convertStr[i]);
		newStr.append(" ");
	}

	free(convertStr);
	return newStr;
}

int PacketHelper::GetPacketLength(const char* input)
{
	int length = 0;

	for (int i = 0; input[i] != '\0'; i++) {
		if (input[i] == ' ')
			length = length;
		else
			length++;
	}

	length = length / 2;

	return length;
}


byte g_EchoBuffer[1024] = { 0 };
int g_EchoLength = 0;

void EchoPacket()
{
	PacketBuilder::EncryptAndSend(g_EchoBuffer, g_EchoLength);
}

BOOL PacketHelper::LogSendPacketToQueue(LPBYTE data, UINT length)
{
	if (length < 0 || data == nullptr)
		return FALSE;

	bool shouldLogPacket = true;
	uint32_t Opcode = 0;
	memcpy(&Opcode, (void*)&data[4], sizeof(uint32_t)); 

	switch (Opcode)
	{
		case Opcodes::Send::Fishing: //data[8] == 1st data byte
		{	
			printf("Processing fishing packet...\n");

			if (length < 15)
				break;

			byte bAction = 0;
			uint32_t hash = 0;
			memcpy(&hash, (void*)&data[8], sizeof(uint32_t));
			memcpy(&bAction, (void*)&data[16], 1);

			g_Robot->FishingHash = hash;

			if (g_Robot->IsFishingExploit)
			{
				if (bAction == 2 && hash != 0)
				{
					printf("Action == 2! Starting thread...\n");
					CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Tasker::SpamFishing, (LPVOID)g_Robot, 0, 0);
				}
			}

			printf("Fishing hash: %x, action: %d\n", g_Robot->FishingHash, bAction);

		}break;

		case Opcodes::Send::Attack:
		{
			uint32_t skillID = 0;
			uint64_t hash1 = 0;
			memcpy(&skillID, (void*)&data[8], sizeof(uint32_t));
			memcpy(&hash1, (void*)&data[12], sizeof(uint64_t));

			printf("PlayerAttack: %d, %llX\n", skillID, hash1); 

		}break;


		default:
		{

		}break;
	};

	if (g_Robot->EchoPackets)
	{
		ZeroMemory(g_EchoBuffer, 1024);
		memcpy((void*)&g_EchoBuffer[0], (void*)&data[4], length - 4);
		g_EchoLength = length - 4;
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&EchoPacket, 0, 0, 0);
	}

	if (shouldLogPacket)
	{
		PacketWriter* p = new PacketWriter();

		if (p != nullptr)
		{
			for (int i = 0; i < length; i++)
				p->Write<byte>(data[i]);

			SendPacketQueue.push(p);
		}
	}

	return TRUE;
}

BOOL PacketHelper::LogRecvPacketToQueue(LPBYTE data, UINT length)
{
	if (length < 0 || data == nullptr)
		return FALSE;

	bool shouldLogPacket = true;
	uint32_t Opcode = 0;
	memcpy(&Opcode, (void*)&data[0], sizeof(uint32_t));

	switch (Opcode)
	{
		default:
		{
			printf("Got RECV packet: %x\n", Opcode);
		}break;
	};

	if (shouldLogPacket)
	{
		PacketWriter* p = new PacketWriter();

		if (p != nullptr) //for this hook there is no LENGTH before opcode.
		{
			for (int i = 0; i < length; i++)
				p->Write<byte>(data[i]);

			RecvPacketQueue.push(p);
		}
	}

	return TRUE;
}

uint16_t PacketHelper::changeEndianness16(UINT16 val)
{
	return (val << 8) | ((val >> 8) & 0x00ff); // right-shift sign-extends, so force to zero
}


int32_t PacketHelper::changeEndianness32(int32_t val)
{
	int32_t tmp = (val << 16) |
		((val >> 16) & 0x00ffff);
	return ((tmp >> 8) & 0x00ff00ff) | ((tmp & 0x00ff00ff) << 8);
}

std::string PacketHelper::randomStr(size_t size)
{
	std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

	std::random_device rd;
	std::mt19937 generator(rd());

	std::shuffle(str.begin(), str.end(), generator);

	return str.substr(0, size);    // assumes 32 < number of characters in str         
}

std::wstring PacketHelper::randomWStr(size_t size)
{
	std::wstring str(L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

	std::random_device rd;
	std::mt19937 generator(rd());

	std::shuffle(str.begin(), str.end(), generator);

	return str.substr(0, size);    // assumes 32 < number of characters in str         
}

std::string PacketHelper::string_to_hex(const std::string& in)
{
	std::stringstream ss;

	ss << std::hex << std::setfill('0');
	for (size_t i = 0; in.length() > i; ++i) {
		ss << std::setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(in[i]));
	}

	return ss.str();
}

std::string PacketHelper::hex_to_string(const std::string& input)
{
	std::string output;

	if ((input.length() % 2) != 0) {
		throw std::runtime_error("String is not valid length ...");
	}

	size_t cnt = input.length() / 2;

	for (size_t i = 0; cnt > i; ++i) {
		uint32_t s = 0;
		std::stringstream ss;
		ss << std::hex << input.substr(i * 2, 2);
		ss >> s;

		output.push_back(static_cast<unsigned char>(s));
	}

	return output;
}