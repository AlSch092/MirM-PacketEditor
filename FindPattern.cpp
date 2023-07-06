#include "FindPattern.hpp"

BOOL Check(const BYTE* pData, const BYTE* bMask, const char* szMask) {
	for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask != '?' && *pData != *bMask)
			return false;

	return (*szMask) == NULL;
}

UINT64 FindPattern(const BYTE *bMask, const char* szMask, UINT64 dwOffset, UINT64 dwStartAddress)
{
	UINT64 dwLen = 0x0100000000000;

	__try
	{
		for (UINT64 i = 0; i < dwLen; i++)
		{
			if (Check((BYTE*)(dwStartAddress + i), bMask, szMask))
			{
				printf("Found address from pattern: %llX\n", (UINT64)(dwStartAddress + i + dwOffset));
				return (UINT64)(dwStartAddress + i + dwOffset);
			}
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		printf("Could not find pattern (error %d): %s\n", GetLastError(), szMask);
	}

	return 0;
}