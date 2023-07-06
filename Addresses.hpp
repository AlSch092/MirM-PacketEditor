#pragma once
#include "FindPattern.hpp"

#define OFFSET const UINT64
#define BASE_ADDRESS 0x140000000
namespace Offsets
{
	OFFSET LogSendPacket = 0; //server can send these to us if we are running a local 'address-feeding' server
	OFFSET EncryptPacket = 0;
	OFFSET OnRecvPacketHook = 0;
	OFFSET GetGameSocket = 0;
	OFFSET SendPacket = 0;

	OFFSET GetObjectHash = 0;

	OFFSET GetAttackSpeed = 0;

	OFFSET IsNPCDialogOpen = 0;
	OFFSET CreateGameMutex = 0;

	OFFSET PlayerMove = 0;

	OFFSET SearchDuplicateClient = 0;
	
	OFFSET AntiMultiClient = 0;
	OFFSET NopMultiClient = 0;
}

namespace MemoryAddresses
{   
	static UINT64 EncryptPacket = FindPattern(Signatures::EncryptPacket, "xxxxxxxxxxxxx", 0, BASE_ADDRESS);
}