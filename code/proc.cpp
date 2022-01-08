#include "proc.h"
DWORD GETPROCID(const wchar_t* procname)
{
	DWORD procid = 0;
	HANDLE hsnap = (CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));
	if (hsnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);
		if (Process32First(hsnap, &procEntry)) 
		{
			do {
				if (!_wcsicmp(procEntry.szExeFile, procname))
				{
					procid = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hsnap,&procEntry));
		}
	}
	CloseHandle(hsnap); // stops memory leaks 
	return procid;
}
uintptr_t GetModuleBaseAddress(DWORD procid, const wchar_t* modname)
{
	uintptr_t modBaseADDr = 0 ;
	HANDLE hsnap= CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procid);
	if (hsnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if(Module32First(hsnap,&modEntry))
		{
			do {
				if (!_wcsicmp(modEntry.szModule, modname)) {
					modBaseADDr = (uintptr_t)modEntry.modBaseAddr;
				}
			} while (Module32Next(hsnap,&modEntry));
		}
	}
	CloseHandle(hsnap);
	return modBaseADDr;
}
uintptr_t FindDMAddy(HANDLE hproc, uintptr_t ptr, std::vector<unsigned int> offsets) 
// stands fotr dynamic memory allocation
{
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size();i++) 
	{
		ReadProcessMemory(hproc, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += offsets[i];
	}
	return addr;
}
