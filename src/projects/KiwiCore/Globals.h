#pragma once

#define PROJECT_NAME	"KiwiHax"

#ifdef _M_X64
#define PROJECT_ARCH	"x64"
#elif defined(_M_IX86)
#define PROJECT_ARCH	"x86"
#else
#define PROJECT_ARCH	"*Unkown*"
#endif

#ifdef CONSOLE_MODE
#define PROJECT_MODE		"CONSOLE"
#elif defined(D3D9_MODE)
#define PROJECT_MODE		"D3D9"
#else
#define PROJECT_MODE		"*Unkown*"
#endif