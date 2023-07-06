#pragma once
#include <Windows.h>
#include <stdint.h>

namespace Hooks
{
	VOID InstallHook(void* func2hook, void* payloadFunction);
	VOID WriteAbsoluteJump64(void* absJumpMemory, void* addrToJumpTo);
	VOID RemoveHook(UINT64 HookAddress, INT ByteLength, BYTE* OriginalBytes);
	VOID* AllocatePageNearAddress(void* targetAddr);
}