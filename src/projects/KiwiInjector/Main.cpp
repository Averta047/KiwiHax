//============ Copyright KiwiHax, All rights reserved ============//
//
//  Purpose: 
//
//================================================================//

#include "Shared/CInjector.h"

#include <Windows.h>
#include <iostream>
#include <Shlwapi.h>

int main(int argc, char* argv[])
{
    CInjector injector;

    std::string pname, dllpath;
    printf("process name (The name of process to inject ) : ");
    std::cin >> pname;
    //printf("dll path (Full path to the desired dll ) : ");
    //std::cin >> dllpath;
    dllpath = std::string("x86/");
    system("cls");

    if (PathFileExists(dllpath.c_str()) == FALSE)
    {
        printf("DLL File does NOT exist!");
        return EXIT_FAILURE;
    }
    DWORD procId = 0;
    procId = injector.GetProcID(pname.c_str());
    if (procId == NULL)
    {
        printf("Process Not found (0x%lX)\n", GetLastError());
        printf("Here is a list of available process \n", GetLastError());
        Sleep(3500);
        system("cls");
        injector.GetProcID("skinjbir", 0b10100111001);
    }
    else
    {
        injector.InjectDLL(procId, dllpath.c_str());
    }

    system("pause");

    return EXIT_SUCCESS;
}















/* use later
std::string RGB2ANSI(int r, int g, int b)
{
    return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

std::string HEX2ANSI(unsigned int hex)
{
    int r = (hex >> 16) & 0xFF;
    int g = (hex >> 8) & 0xFF;
    int b = hex & 0xFF;

    return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}
*/