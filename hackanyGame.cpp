
#include <iostream>
#include <vector>
#include <Windows.h>
#include "proc.h"
#include<string>

int main()

{
	//variable definitions
	//std::vector<unsigned int> OffsetsX;
	HANDLE hProcess = 0;
	int ammoValue = 0, health = 0, grenadeAmmo = 0; 
	int newAmmo = 657, newHealth = 0, newGrenadeAmmo = 0;
	int choice = 0;
	std::vector <unsigned int> ammoOffsets = { 0x150 }, healthOffsets = {0xF8 }, grenadeAMMOOffsets = { 0x158 };
	std::vector<std::vector<int>> variables = { {ammoValue  , health  ,grenadeAmmo }, { newAmmo,newHealth,newGrenadeAmmo} };
	// i put all the offsets into a vector of vectors to keep size down
	// also kept each individual one above so it is easier for later debugging
	std::vector<std::vector<unsigned int>> OFFSETS = { ammoOffsets,healthOffsets,grenadeAMMOOffsets };
	std::vector <uintptr_t> resolvedPointers = {};

	// get process id
	DWORD procId = GETPROCID(L"ac_client.exe");

	//get module base addr
	uintptr_t ModuleBase = GetModuleBaseAddress(procId, L"ac_client.exe");

	//get handle to process
	
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	//resolve base pointer chain for 
	uintptr_t dynamicPtrBaseAddr = ModuleBase + 0x10f4f4;

	//std::cout << "DYNAMIC PTR BASE =" << "0x" << std::hex << dynamicPtrBaseAddr << "\n";
	

	//resolve pointer chains 
	for (int index = 0; index < OFFSETS.size(); index++) 
	{
		// OFFSETS[index];
	//	std::cout << index << "\n"<< FindDMAddy(hProcess, dynamicPtrBaseAddr, OFFSETS[index]) << "\n";
		resolvedPointers.push_back( FindDMAddy(hProcess, dynamicPtrBaseAddr, OFFSETS[index]));
	}
	
	//std::cout << "AMMO ADDR =" << "0x" << std::hex << ammoAddr << "\n";

	//read  x value
	//for (int index = 0; index < variables[0].size(); index++) {
	//	std::cout << "\n" << index <<"\n"<<resolvedPointers[index];
	//	ReadProcessMemory(hProcess, (BYTE*)resolvedPointers[index], &variables[0][index], sizeof(variables[0][index]), nullptr);
	//	ReadProcessMemory(hProcess, (BYTE*)resolvedPointers[1], &health, sizeof(health), nullptr);
	
	//ReadProcessMemory(hProcess, (BYTE*)resolvedPointers[0], &ammoValue, sizeof(ammoValue), nullptr);
	while (true) 
	{
		for (int index = 0; index < variables[0].size(); index++) {
			//std::cout << "\n" << index << "\n" << resolvedPointers[index];
			ReadProcessMemory(hProcess, (BYTE*)resolvedPointers[index], &variables[0][index], sizeof(variables[0][index]), nullptr);
			ReadProcessMemory(hProcess, (BYTE*)resolvedPointers[1], &health, sizeof(health), nullptr);
		}
		//ReadProcessMemory(hProcess, (BYTE*)resolvedPointers[1], &health, sizeof(health), nullptr);
		system("color a");

		std::cout << "CURRENT AMMO\t\t[   " << std::dec << variables[0][0] <<"\t ]" << "\n";
		std::cout << "CURRENT HEALTH\t\t[   " << std::dec << variables[0][1] << "\t ]" << "\n";
		std::cout << "CURRENT Grenade ammo:\t[   " << std::dec << variables[0][2] << "\t ]" << "\n\n\n";
		std::cout 
			<< "===============================" << "\n"
			<< "===============================" << "\n"
			<< "press 1 to change ammo value"    << "\n"
			<< "press 2 to change health value"  << "\n"
			<< "press 3 to change grenade ammo"  << "\n"
			<< "===============================" << "\n"
			<< "===============================" << "\n\n\n";
		std::cout << "ENTER YOUR CHOICE-->\t"; std::cin >> choice; std::cout << "\n";
		if (choice == 1) 
		{
			//ammoValue = 0;
			ReadProcessMemory(hProcess, (BYTE*)resolvedPointers[0], &variables[0][0], sizeof(variables[0][0]), nullptr);
			std::cout << "CURRENT AMMO --> " << std::dec << variables[0][0] << "\n";
			//write to x value
			newAmmo = 0;
			std::cout << "enter ammo amount:";
			std::cin >> newAmmo;
			std::cout << "\n";
			WriteProcessMemory(hProcess, (BYTE*)resolvedPointers[0], &newAmmo, sizeof(newAmmo), nullptr);
			//read x value again
			//ReadProcessMemory(hProcess, (BYTE*)resolvedPointers[0], &variables[0][0], sizeof(variables[0][0]), nullptr);
			//std::cout << "CURRENT AMMO --> " << std::dec << ammoValue << "\n";
		}
		if (choice == 2)
		{
			newHealth = 0;
			ReadProcessMemory(hProcess,(BYTE*)resolvedPointers[1],&variables[0][1],sizeof(variables[0][1]),nullptr);
			std::cout << "CURRENT HEALTH --> " << std::dec << variables[0][1] << "\n";
			std::cout << "enter Health amount:";
			std::cin >> newHealth;
			WriteProcessMemory(hProcess, (BYTE*)resolvedPointers[1], &newHealth, sizeof(newHealth), nullptr);
		}
		if (choice == 3) 
		{

		}
		system("cls");
	}
	/**/

}