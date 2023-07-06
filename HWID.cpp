#include "HWID.hpp"

//WARNING: will fail if windows is not on C:/...
string GetHardwareID(string drive)
{
	string HWID;

	CHAR volumeName[MAX_PATH + 1] = { 0 };
	CHAR fileSystemName[MAX_PATH + 1] = { 0 };
	DWORD serialNumber = 0;
	DWORD maxComponentLen = 0;
	DWORD fileSystemFlags = 0;

	if (GetVolumeInformationA(drive.c_str(), volumeName, ARRAYSIZE(volumeName), &serialNumber, &maxComponentLen, &fileSystemFlags, fileSystemName, ARRAYSIZE(fileSystemName)))
	{
		CHAR serialBuf[20];
		_itoa_s(serialNumber, serialBuf, 10);

		CHAR username[1024];
		DWORD size = 1024;
		GetUserNameA((CHAR*)username, &size);

		HWID = username;
		HWID += "-";
		HWID += serialBuf;
		HWID += '\0';
	}
	else
	{
		HWID = "Failed to generate HWID.";
		return NULL;
	}

	return HWID;
}
