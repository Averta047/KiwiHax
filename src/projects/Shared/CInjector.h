//============ Copyright KiwiHax, All rights reserved ============//
//
//  Purpose: 
//  Resources: https://github.com/ZeroMemoryEx/Dll-Injector/blob/master/DLL-Injector/Dll-Injector.cpp
//
//================================================================//

#pragma once

#include <Windows.h>

class CInjector
{
public:
	CInjector();
	~CInjector();

public:
	DWORD GetProcID(const char* pn, unsigned short int fi = 0b1101);
	BOOL InjectDLL(DWORD procID, const char* dllPath);
};