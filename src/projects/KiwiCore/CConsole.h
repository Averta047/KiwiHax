//============ Copyright KiwiHax, All rights reserved ============//
//
//  Purpose: Console IO
//
//================================================================//

#pragma once

#include <iostream>

#define CONSOLE_SECURITY_CHECK 1

class CConsole
{
public:
	CConsole();
	~CConsole();

public:
	bool Initialize(const char* console_title, bool input, bool output);
	void Shutdown();

	void Print(const char* fmt, ...);
	const char* Input(const char* fmt, ...);

	void Clear();

private:
	FILE* m_pFile = nullptr;

#if ( CONSOLE_SECURITY_CHECK == 1 )
private:
	bool m_bInputEnabled;
	bool m_bOutputEnabled;
#endif
};

namespace Globals { inline CConsole Console; }