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

void DebugPrintF(const wchar_t* format, ...)
{
#if defined(DEBUG_MODE) || defined(RELWITHDEBINFO_MODE)
	wchar_t buffer[MAX_BUFFER_SIZE];

	va_list args;
	va_start(args, format);
	int32_t size = _vsnwprintf_s(buffer, MAX_BUFFER_SIZE, format, args);
	va_end(args);

	OutputDebugStringW(buffer);
#endif
}

std::string PrintF(const char* format, ...)
{
	char buffer[MAX_BUFFER_SIZE];

	va_list args;
	va_start(args, format);
	int32_t size = vsnprintf(buffer, MAX_BUFFER_SIZE, format, args);
	va_end(args);

	return std::string(buffer, size);
}

std::wstring PrintF(const wchar_t* format, ...)
{
	wchar_t buffer[MAX_BUFFER_SIZE];

	va_list args;
	va_start(args, format);
	int32_t size = _vsnwprintf_s(buffer, MAX_BUFFER_SIZE, format, args);
	va_end(args);

	return std::wstring(buffer, size);
}