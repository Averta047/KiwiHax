//============ Copyright KiwiHax, All rights reserved ============//
//
//  Purpose: 
//
//================================================================//

#include "CConsole.h"

#include <Windows.h>

DWORD APIENTRY MainThread(LPVOID lpParam)
{
	Globals::Console.Initialize(	// TODO: make a console title string generator
		"KiwiCore - "
#ifdef _M_X64
		"x64"
#else // very bad idea but we are limited to x86 & x64 atm
		"x86"
#endif
		" - "
//#ifdef x
		"d3d9"
//#else
//		"d3dx"
//#endif
		,
		true,
		true
	);

	FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), EXIT_SUCCESS);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	static bool bAttached = false;

	if ((fdwReason == DLL_PROCESS_ATTACH) && !bAttached)
	{
		const HANDLE hMain = CreateThread(NULL, NULL, MainThread, hinstDLL, NULL, NULL);

		if (hMain)
		{
			bAttached = true;
			CloseHandle(hMain);
		}
	}

	return TRUE;
}