#include "include.h";

HANDLE hProc;
void log(const char* print)
{
	std::cout << print << std::endl;
}
uintptr_t attachToProcess(const wchar_t* ProcName)
{
	HANDLE hSnap = NULL;
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (hSnap == INVALID_HANDLE_VALUE)
	{
		log("Faild Taking SnapShot of running Processes!");
		return false;
	}
	else if (hSnap == NULL)
	{
		log("something went wrong! ");
		return 0;
	}
	else if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);
		while (Process32Next(hSnap, &procEntry))
		{
			if (!_wcsicmp(ProcName, procEntry.szExeFile))
			{	
				auto ProcID = procEntry.th32ProcessID;
				std::cout << "PROC NAME: ";
				std::wcout << ProcName << std::endl;
				std::cout << "PROC ID: " << ProcID << std::endl;
				std::cout << "PROC ID IN HEX: " << std::hex <<ProcID << std::endl;
				hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, procEntry.th32ProcessID);
				return ProcID;
				CloseHandle(hSnap);
			}
		}
	}
	std::cout << "Process is Not Running!\n";
	return false;
	CloseHandle(hSnap);
}


int main()
{
	attachToProcess(L"ac_client.exe");
	return 0;
}