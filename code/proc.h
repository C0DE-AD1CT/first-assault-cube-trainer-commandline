// includes

#include<Windows.h>
#include<TlHelp32.h>
#include<vector>

//function declarations

DWORD GETPROCID(const wchar_t* procname);
uintptr_t GetModuleBaseAddress(DWORD procid, const wchar_t* modname);
uintptr_t FindDMAddy(HANDLE hproc, uintptr_t ptr, std::vector<unsigned int>);

//
