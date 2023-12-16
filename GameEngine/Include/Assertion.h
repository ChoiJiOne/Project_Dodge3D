#pragma once

#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <windows.h>


#if defined(DEBUG) || defined(RELEASE)
/**
 * @brief 디버그 창에 형식화된 문자열을 출력합니다.
 *
 * @param format 형식 문자열입니다.
 * @param .. 문자열 내의 형식에 대응하는 가변인자입니다.
 *
 * @note
 * - Debug와 Release모드에서만 디버그 창에 문자열이 출력됩니다.
 * - Shipping 모드에서는 디버그 창에 문자열이 출력되지 않습니다.
 */
inline void AssertPrintF(const char* format, ...)
{
	static const int32_t BUFFER_SIZE = 1024;
	static char buffer[BUFFER_SIZE];

	va_list args;
	va_start(args, format);
	int32_t size = vsnprintf(buffer, BUFFER_SIZE, format, args);
	va_end(args);

	OutputDebugStringA(buffer);
}


/**
 * @brief 디버그 창에 형식화된 문자열을 출력합니다.
 *
 * @param format 형식 문자열입니다.
 * @param .. 문자열 내의 형식에 대응하는 가변인자입니다.
 *
 * @note
 * - Debug와 Release모드에서만 디버그 창에 문자열이 출력됩니다.
 * - Shipping 모드에서는 디버그 창에 문자열이 출력되지 않습니다.
 */
inline void AssertPrintF(const wchar_t* format, ...)
{
	static const int32_t BUFFER_SIZE = 1024;
	static wchar_t buffer[BUFFER_SIZE];

	va_list args;
	va_start(args, format);
	int32_t size = _vsnwprintf_s(buffer, BUFFER_SIZE, format, args);
	va_end(args);

	OutputDebugStringW(buffer);
}
#endif