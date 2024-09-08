//============ Copyright KiwiHax, All rights reserved ============//
//
//  Purpose: 
//  Resources: https://github.com/ZeroMemoryEx/Dll-Injector/blob/master/DLL-Injector/Dll-Injector.cpp
//
//================================================================//

#include "CInjector.h"

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <iomanip>
#include <Shlwapi.h>

CInjector::CInjector()
{

}

CInjector::~CInjector()
{

}

DWORD CInjector::GetProcID(const char* pn, unsigned short int fi)
{
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 pE;
        pE.dwSize = sizeof(pE);

        if (Process32First(hSnap, &pE))
        {
            if (!pE.th32ProcessID)
            {
                Process32Next(hSnap, &pE);
            }

            do
            {
                if (fi == 0b10100111001)
                {
                    std::cout << pE.szExeFile << "\x9\x9\x9" << pE.th32ProcessID << std::endl;
                }

                if (!_stricmp(pE.szExeFile, pn))
                {
                    procId = pE.th32ProcessID;
                    printf("Process : 0x%lX\n", pE);
                    break;
                }
            } while (Process32Next(hSnap, &pE));
        }
    }

    CloseHandle(hSnap);

    return procId;
}

BOOL CInjector::InjectDLL(DWORD procID, const char* dllPath)
{
    BOOL WPM = 0;

    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procID);
    if (hProc == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }

    void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    WPM = WriteProcessMemory(hProc, loc, dllPath, strlen(dllPath) + 1, 0);
    if (!WPM)
    {
        CloseHandle(hProc);
        return FALSE;
    }

    printf("DLL Injected Succesfully 0x%lX\n", WPM);

    HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);
    if (!hThread)
    {
        VirtualFree(loc, strlen(dllPath) + 1, MEM_RELEASE);
        CloseHandle(hProc);
        return FALSE;
    }

    printf("Thread Created Succesfully 0x%lX\n", hThread);

    CloseHandle(hProc);
    VirtualFree(loc, strlen(dllPath) + 1, MEM_RELEASE);
    CloseHandle(hThread);

    return TRUE;
}