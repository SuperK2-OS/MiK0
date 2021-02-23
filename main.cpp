#include <Windows.h>
#include <iostream>

#include "memory.hpp"
#include "ifexist.hpp"

using namespace std;

Injector inj;

DWORD pid;

//now it's global
LPVOID ntOpenFile = GetProcAddress(LoadLibraryW(L"ntdll"), "NtOpenFile");

void bypass()
{
	// Restore original NtOpenFile from external process
	//credits: Daniel Krupiñski(pozdro dla ciebie byczku <3)
	if (ntOpenFile) {
		char originalBytes[5];
		memcpy(originalBytes, ntOpenFile, 5);
		WriteProcessMemory(inj.process, ntOpenFile, originalBytes, 5, NULL);
	}
	else
	{
		cout << "Imposible Hacer Bypass :(\n";
		Sleep(2000);
		exit(-1);
	}
}

void Backup()
{
	if (ntOpenFile) {
		//So, when I patching first 5 bytes I need to backup them to 0? (I think)
		char originalBytes[5];
		memcpy(originalBytes, ntOpenFile, 5);
		WriteProcessMemory(inj.process, ntOpenFile, originalBytes, 0, NULL);
	}
	else
	{
		cout << "NO SE PUEDE HACER BACKUP :(\n";
		Sleep(2000);
		exit(-1);
	}
}

int main()
{
	SetConsoleTitle(" Inyector VACa v.3.0 - www.CheatersUnidos.com - 29 - Enero - 2021 :)");

	cout << " " << endl;
	cout << "    ##     ##       ###        ######        ***              44    44 " << endl;
	cout << "    ##     ##      ## ##      ##    ##      ** **             44    44 " << endl;
	cout << "    ##     ##     ##   ##     ##           **   **            44    44 " << endl;
	cout << "    ##     ##    ##     ##    ##          **     **           44    44 " << endl;
	cout << "    ##   ##      #########    ##          *********           444444444" << endl;
	cout << "    ## ##        ##     ##    ##          **     **                 44 " << endl;
	cout << "    ###          ##     ##    ##    ##    **     **                 44 " << endl;
	cout << "    #            ##     ##     ######     **     **                 44  ]:-)\n\n" << endl;

	cout << "    ***************************************************************************" << endl;
	cout << "    *  Inyector VACa v.4.0 - www.CheatersUnidos.com - 23 - Febrero - 2021 :)  *" << endl;
	cout << "    ***************************************************************************\n" << endl;
	cout << "    Traducido y Recompilado: SuperK2 & Gauxalot https://github.com/SuperK2-OS/VACa \n" << endl;
	cout << "    Creadores y Agradecimientos Especiales para: Daniel Krupinski, online-9, Hitchance\n" << endl;
	cout << "    https://www.CheatersUnidos.com - Discord: https://discord.gg/4Sh8PJP \n\n" << endl;

	inj.hwndproc = FindWindowA(0, "Counter-Strike: Global Offensive");


	GetWindowThreadProcessId(inj.hwndproc, &pid);
	inj.process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	inj.clientDLL = inj.GetModule(pid, "client.dll");

	if (DoesFileExist("cheat.dll")) {
		bypass();

		if (inj.inject(pid, "cheat.dll")) {
			cout << "    >>>>>> Inyector VACa v.4.0 HA FUNCIONADO !!! CHEAT INYECTADO CORRECTAMENTE, DISFRUTA ! GLHF !!\n\n" << endl;
			Backup();
			Sleep(5000);
			exit(0);
		}
		else
		{
			cout << "    ######### ERROR ##########! La Inyeccion ha fallado!\n\n" << endl;
			Backup();
			Sleep(5000);
			exit(-1);
		}
	
	}
	else
	{
		cout << "    *** IMPORTANTE: *** EL FICHERO cheat.dll NO SE HA ENCONTRADO, RECUERDA RENOMBRAR TU .DLL como cheat.dll\n\n";
		Sleep(5000);
		exit(-1);
	}

	return 0;
}
