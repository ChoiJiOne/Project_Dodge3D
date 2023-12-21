#include "StringUtils.h"

char StringUtils::charBuffer_[STRING_BUFFER_SIZE];
wchar_t StringUtils::wcharBuffer_[STRING_BUFFER_SIZE];

std::string StringUtils::PrintF(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	int32_t size = vsnprintf(charBuffer_, STRING_BUFFER_SIZE, format, args);
	va_end(args);

	return std::string(charBuffer_, size);
}

std::wstring StringUtils::PrintF(const wchar_t* format, ...)
{
	va_list args;
	va_start(args, format);
	int32_t size = _vsnwprintf_s(wcharBuffer_, STRING_BUFFER_SIZE, format, args);
	va_end(args);

	return std::wstring(wcharBuffer_, size);
}
