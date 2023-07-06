#pragma once
#include <queue>
#include "Opcodes.hpp"
#include "PacketWriter.hpp"
#include "Process.hpp"
#pragma comment(lib, "ws2_32") //send()

#define HEADER_LENGTH 6

namespace PacketBuilder
{
	int SendPacket(BYTE* bPacket, DWORD dwLen);
	BYTE* EncryptPacket(BYTE* keyPtr, BYTE* bPacket, DWORD dwLen);
	
	int EncryptAndSend(BYTE* bPacket, DWORD dwLen); //we are using this implementation
}

extern "C" //ASM files
{
	int _SendPacket(VOID* sendClass, VOID* bufferStruct);
	int _EncryptPacket(BYTE* keyPtr, int Unk1, BYTE* bPacket, BYTE* bPacket2);
}
