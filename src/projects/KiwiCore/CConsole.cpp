//============ Copyright KiwiHax, All rights reserved ============//
//
//  Purpose: Console IO
//
//================================================================//

#include "CConsole.h"
#include <Windows.h>
#include <string>

CConsole::CConsole()
{
	m_pFile = nullptr;

#if ( CONSOLE_SECURITY_CHECK == 1 )
	m_bInputEnabled = false;
	m_bOutputEnabled = false;
#endif
}

CConsole::~CConsole()
{
	this->Shutdown();
}

bool CConsole::Initialize(const char* console_title, bool input, bool output)
{
	AllocConsole();

	if (output) {
		freopen_s(&m_pFile, "CONOUT$", "w", stdout);
		if (m_pFile == nullptr) {
			return false;
		}
	}

	if (input) {
		freopen_s(&m_pFile, "CONIN$", "r", stdin);
		if (m_pFile == nullptr) {
			return false;
		}
	}

	SetConsoleTitle(console_title);

	return true;
}

void CConsole::Shutdown()
{
	fclose(m_pFile);
	FreeConsole();
}

void CConsole::Print(const char* format, ...)
{
#if ( CONSOLE_SECURITY_CHECK == 1 )
	if (!m_bOutputEnabled) {
		return;
	}
#endif

	va_list args;
	va_start(args, format);

	char buffer[256];
	vsprintf_s(buffer, format, args);
	std::string message = buffer;

	printf("%s", message.c_str());
	va_end(args);
	printf("\n");
}

const char* CConsole::Input(const char* format, ...)
{
#if ( CONSOLE_SECURITY_CHECK == 1 )
	if (!m_bOutputEnabled) {
		return nullptr;
	}
#endif

	va_list args;
	va_start(args, format);

	char buffer[256];
	vsprintf_s(buffer, format, args);
	std::string message = buffer;

	std::string value = std::string("");

	std::cout << message;
	std::getline(std::cin, value);
	std::cout << std::endl;

	return value.c_str();
}