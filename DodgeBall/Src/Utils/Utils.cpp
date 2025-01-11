#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include <windows.h>
#include <Shlwapi.h>

#include "Utils/Utils.h"

static const int32_t MAX_BUFFER_SIZE = 1024;

void DebugPrintF(const char* format, ...)
{
#if defined(DEBUG_MODE) || defined(RELWITHDEBINFO_MODE)
	char buffer[MAX_BUFFER_SIZE];

	va_list args;
	va_start(args, format);
	int32_t size = _vsnprintf_s(buffer, MAX_BUFFER_SIZE, MAX_BUFFER_SIZE, format, args);
	va_end(args);

	OutputDebugStringA(buffer);
#endif
}