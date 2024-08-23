#include <windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    return MessageBoxA(NULL, "You sure we need injector ?", "KiwiInjector", MB_ICONQUESTION);
}