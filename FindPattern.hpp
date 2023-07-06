#pragma once
#include <Windows.h>
#include <stdio.h>

BOOL Check(const BYTE* pData, const BYTE* bMask, const char* szMask);
UINT64 FindPattern(const BYTE *bMask, const char* szMask, UINT64 dwOffset, UINT64 dwStartAddress);

namespace Signatures
{
	static const BYTE EncryptPacket[] = { 0x00 }; //no spoon feeding addresses, sorry
};