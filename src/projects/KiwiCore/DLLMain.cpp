#include <Windows.h>

DWORD APIENTRY MainThread(LPVOID lpParam)
{


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