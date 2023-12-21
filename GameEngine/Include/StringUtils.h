#pragma once

#include <vector>
#include <string>
#include <cstdarg>


/**
 * @brief 표준 문자열(std::string, std::wstring)의 확장 기능을 제공합니다.
 */
class StringUtils
{
public:


private:
	/**
	 * @brief 문자열 버퍼의 크기입니다.
	 */
	static const int32_t STRING_BUFFER_SIZE = 1024;


	/**
	 * @brief char 문자열 버퍼입니다.
	 */
	static char charBuffer_[STRING_BUFFER_SIZE];


	/**
	 * @brief wchar_t 문자열 버퍼입니다.
	 */
	static wchar_t wcharBuffer_[STRING_BUFFER_SIZE];
};