#pragma once
#include <Windows.h>
#include "log.h"

struct HACK {
	UINT64 dwAddress;
	char* szOriginalBytes;
	char* szNewBytes;
	INT nSize;
};

VOID WriteHackBytes(HACK hHack, BOOL bEnable);
VOID ReduceRAM();