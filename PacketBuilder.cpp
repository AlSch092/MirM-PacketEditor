#include "PacketBuilder.hpp"

extern BOOL g_LoggingOutboundTraffic;
extern std::queue<PacketWriter*> SendPacketQueue;

extern "C" SOCKET lpGameSocket;
extern "C" UINT64 lpKeyPtrLong;
extern "C" UINT64 lpKeyPtrShort;

int PacketBuilder::EncryptAndSend(BYTE* bPacket, DWORD dwLen)
{
	if (!lpKeyPtrLong || !bPacket)
	{
		printf("[ERROR] KeyPtr or bPacket was NULL!\n");
		return 0;
	}

	if (lpGameSocket == SOCKET_ERROR)
	{
		printf("sGameSocket was NULL!\n");
		return 0;
	}

	BYTE* EncryptedData = nullptr;
	int sentBytes = 0;
	
	if (dwLen > 4)
	{
		printf("Sending with long key ptr\n");
		EncryptedData = EncryptPacket((BYTE*)lpKeyPtrLong, bPacket, dwLen);
	}
	else
	{
		printf("Sending with short key ptr\n");
		EncryptedData = EncryptPacket((BYTE*)lpKeyPtrShort, bPacket, dwLen);
	}

	int finalLength = dwLen + 4;

	printf("Sending %d bytes..\n", finalLength);

	if (EncryptedData)
	{
		sentBytes = send(lpGameSocket, (const char*)EncryptedData, finalLength, 0);
	}

	free(EncryptedData);
	return sentBytes;
}

BYTE* PacketBuilder::EncryptPacket(BYTE* keyPtr, BYTE* bPacket, DWORD dwLen) //encrypts full length packets in one call
{
	if (keyPtr == nullptr || bPacket == nullptr)
	{
		printf("keyPtr or bPacket was NULL!\n");
		return NULL;
	}

	//we need to form a new packet with 4 bytes extra length at the start.
	BYTE* bFinalPacket = (BYTE*)malloc(dwLen + 4);
	DWORD FinalLen = dwLen + 4;
	
	memcpy(bFinalPacket, &FinalLen, sizeof(uint32_t));
	memcpy(bFinalPacket + 4, bPacket, dwLen);

	if (g_LoggingOutboundTraffic)
	{
		//Log to editor
		PacketWriter* p = new PacketWriter();

		for (unsigned int i = 0; i < FinalLen; i++)
		{
			p->Write<BYTE>(bFinalPacket[i]);		
		} 

		SendPacketQueue.push(p);
	}

	int EncryptedLen = _EncryptPacket(keyPtr, HEADER_LENGTH, bFinalPacket, bFinalPacket);

	if (EncryptedLen)
	{
		printf("Encrypted successfully!\n");
	}
	else
	{
		if (bFinalPacket != nullptr)
			free(bFinalPacket);
	
		bFinalPacket = NULL;
		return NULL;
	}

	return bFinalPacket; //remember to free() memory yourself after finished with the packet
}
