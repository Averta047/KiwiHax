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



	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	// Using LuaJIT FFI (example)
	luaL_dostring(L, "local ffi = require('ffi') ffi.cdef('int printf(const char *fmt, ...);') ffi.C.printf('Hello, LuaJIT!\\n')");

	lua_close(L);



	// Exit
	Globals::Console.Shutdown();

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