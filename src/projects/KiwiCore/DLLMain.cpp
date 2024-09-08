//============ Copyright KiwiHax, All rights reserved ============//
//
//  Purpose: 
//
//================================================================//

#include "CConsole.h"
#include "Globals.h"

#include <Windows.h>

#include "lua.hpp"
#include "luajit.h"

DWORD APIENTRY MainThread(LPVOID lpParam)
{
	Globals::Console.Initialize(	// TODO: make a console title string generator
		PROJECT_NAME " - " PROJECT_MODE " - " PROJECT_ARCH,
		true,
		true
	);

	//Globals::Console.Input("HELLO WORLD: ??? > ");
	Globals::Console.Print(PROJECT_NAME " Attacked successfully!");
	Globals::Console.Print("DLL Instance: 0x%p", lpParam);
	Globals::Console.Print("Architecture: " PROJECT_ARCH);
	Globals::Console.Print("Mode: " PROJECT_MODE "\0");

    /*
	char dllPath[MAX_PATH];
	GetModuleFileNameA(static_cast<HMODULE>(lpParam), dllPath, MAX_PATH);
	PathRemoveFileSpec(dllPath); // remove DLL file name from the path

	std::string luaPath = std::string(dllPath) + "\\lua51.dll";
	if (!InjectDLL(luaPath)) {
		Globals::Console.Print("Failed to inject lua51.dll: %d", GetLastError());
		FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), EXIT_FAILURE);
	}
	Globals::Console.Print(luaPath.c_str());

	lua_State* L = luaL_newstate();
	if (!L) {
		Globals::Console.Print("Failed to create Lua state");
		FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), EXIT_FAILURE);
	}
	luaL_openlibs(L);
	
	luaL_openlibs(L); 
	luaL_dostring(L, "print(\"hello world\")");
	lua_close(L);
    */

	// Exit
	Globals::Console.Shutdown(); // FIX ME

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