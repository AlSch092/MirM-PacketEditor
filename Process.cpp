#include "Process.hpp"

bool SendMouseClick(HWND hwnd, int x, int y) //todo: finish this -> PostMessage/SendMessage with correct L/WPARAM
{
	return true;
}

void Process::SuspendAllThreads()
{
	HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
		return;

	THREADENTRY32 te32;
	te32.dwSize = sizeof(THREADENTRY32);
	
	if (!Thread32First(hThreadSnap, &te32))
	{
		CloseHandle(hThreadSnap);
		return;
	}

	DWORD dwCurrentThreadId = GetCurrentThreadId();

	do
	{
		if (te32.th32ThreadID != dwCurrentThreadId ) //locks entire PC, wtf?
		{
			printf("ThreadID: %d\n", te32.th32ThreadID);
			HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te32.th32ThreadID);
			if (hThread != NULL)
			{
				printf("Suspending thread: %d\n", te32.th32ThreadID);
				SuspendThread(hThread);
				CloseHandle(hThread);
			}
		}
	} while (Thread32Next(hThreadSnap, &te32));

	CloseHandle(hThreadSnap);

	Process::g_ThreadsSuspended = true;
}

void Process::ResumeAllThreads()
{
	HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
		return;

	THREADENTRY32 te32;
	te32.dwSize = sizeof(THREADENTRY32);

	if (!Thread32First(hThreadSnap, &te32))
	{
		CloseHandle(hThreadSnap);
		return;
	}

	DWORD dwCurrentThreadId = GetCurrentThreadId();
	do
	{
		if (te32.th32ThreadID != dwCurrentThreadId)
		{
			HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te32.th32ThreadID);
			if (hThread != NULL)
			{
				ResumeThread(hThread);
				CloseHandle(hThread);
			}
		}
	} while (Thread32Next(hThreadSnap, &te32));

	CloseHandle(hThreadSnap);

	Process::g_ThreadsSuspended = false;
}

void Process::Hider::ChangeModuleName(wchar_t* szModule, wchar_t* newName)
{
	PPEB PEB = (PPEB)__readgsqword(0x60);
	_LIST_ENTRY* f = PEB->Ldr->InMemoryOrderModuleList.Flink;
	bool Found = FALSE;

	while (!Found)
	{
		PLDR_DATA_TABLE_ENTRY dataEntry = CONTAINING_RECORD(f, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

		if (wcsstr(dataEntry->FullDllName.Buffer, szModule) != NULL)
		{
			wcscpy(dataEntry->FullDllName.Buffer, newName);
			Found = TRUE;
			return;
		}

		f = dataEntry->InMemoryOrderLinks.Flink;
	}
}