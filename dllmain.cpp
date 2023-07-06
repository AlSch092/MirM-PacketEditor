/*
* 
 alsch092 @ github - Mir-M Packet Logger + Sender
*/
// 
// dllmain.cpp : Defines the entry point for the DLL application.
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "HWID.hpp"
#include "Process.hpp"

extern int Main();

extern "C" //PROXY Dll hooks
{
	UINT64 lpXAudio2Create;
	UINT64 lpCreateAudioReverb;
	UINT64 lpCreateAudioVolumeMeter;
	UINT64 lpX3DAudioInitialize;
	UINT64 lpX3DAudioCalculate;
	UINT64 lpCreateFX;
}


VOID GetRealExportAddresses() //our proxy DLL looks up the addresses of the actual funcitons so that we can re-direct calls to the real ones and pass back the return value
{
	HMODULE xaudio9 = LoadLibraryA("XAudio2_9redist_REAL.dll"); //SPOOF DLL

	if (xaudio9)
	{
		UINT64 CreateAudioReverb_Addr = (UINT64)GetProcAddress(xaudio9, "CreateAudioReverb");

		if (CreateAudioReverb_Addr)
		{
			printf("CreateAudioReverb: %llX\n", CreateAudioReverb_Addr);
			lpCreateAudioReverb = CreateAudioReverb_Addr;
		}
		else
			printf("Failed to get address: CreateAudioReverb.\n");

		UINT64 CreateFX_Addr = (UINT64)GetProcAddress(xaudio9, "CreateFX");

		if (CreateFX_Addr)
		{
			printf("CreateFX: %llX\n", CreateFX_Addr);
			lpCreateFX = CreateFX_Addr;
		}
		else
			printf("Failed to get address: CreateFX.\n");

		UINT64 X3DAudioCalculate_Addr = (UINT64)GetProcAddress(xaudio9, "X3DAudioCalculate");

		if (X3DAudioCalculate_Addr)
		{
			printf("X3DAudioCalculate: %llX\n", X3DAudioCalculate_Addr);
			lpX3DAudioCalculate = X3DAudioCalculate_Addr;
		}

		UINT64 X3DAudioInitialize_Addr = (UINT64)GetProcAddress(xaudio9, "X3DAudioInitialize");

		if (X3DAudioInitialize_Addr)
		{
			printf("X3DAudioInitialize: %llX\n", X3DAudioInitialize_Addr);
			lpX3DAudioInitialize = X3DAudioInitialize_Addr;
		}

		UINT64 CreateAudioVolumeMeter_Addr = (UINT64)GetProcAddress(xaudio9, "CreateAudioVolumeMeter");

		if (CreateAudioVolumeMeter_Addr)
		{
			printf("CreateAudioVolumeMeter: %llX\n", CreateAudioVolumeMeter_Addr);
			lpCreateAudioVolumeMeter = CreateAudioVolumeMeter_Addr;
		}

		UINT64 XAudio2Create_Addr = (UINT64)GetProcAddress(xaudio9, "XAudio2Create");

		if (XAudio2Create_Addr)
		{
			printf("XAudio2Create: %llX\n", XAudio2Create_Addr);
			lpXAudio2Create = XAudio2Create_Addr;
		}
	}
	else
	{
		printf("FATAL ERROR: Failed to find XAudio2_9redist_REAL.dll: %d\n", GetLastError());
		MessageBoxA(0, "FATAL ERROR: Failed to find XAudio2_9redist_REAL.dll", 0, 0);
		TerminateProcess(GetCurrentProcess(), 0);
	}
}

VOID Start()
{
	Sleep(2000);
	HWND hwnd = FindWindowA(NULL, "MIRMG(1)");
	SetWindowTextA(hwnd, "_1");

	hwnd = FindWindowA(NULL, "MIRMG(2)");
	SetWindowTextA(hwnd, "_2");

	Main();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		{
			AllocConsole();
			freopen("CON", "w", stdout);
			freopen("CON", "r", stdin);

			GetRealExportAddresses();

			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Start, 0, 0, 0);

		}break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


