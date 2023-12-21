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

std::vector<std::string> StringUtils::Split(const std::string& text, const std::string& delimiter)
{
	std::vector<std::string> tokens;
	std::size_t position = 0ULL;
	std::string remain = text;

	while ((position = remain.find(delimiter)) != std::string::npos)
	{
		tokens.push_back(remain.substr(0, position));
		remain.erase(0, position + delimiter.length());
	}

	tokens.push_back(remain);
	return tokens;
}

std::vector<std::wstring> StringUtils::Split(const std::wstring& text, const std::wstring& delimiter)
{
	std::vector<std::wstring> tokens;
	std::size_t position = 0ULL;
	std::wstring remain = text;

	while ((position = remain.find(delimiter)) != std::string::npos)
	{
		tokens.push_back(remain.substr(0, position));
		remain.erase(0, position + delimiter.length());
	}

	tokens.push_back(remain);
	return tokens;
}
