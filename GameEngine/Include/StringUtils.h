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
	/**
	 * @brief 형식화된 문자열을 반환합니다.
	 *
	 * @note
	 * - 이 메서드는 snprintf와 같은 함수를 대체하기 위한 것입니다.
	 * - 문자열의 길이는 최대 1024 입니다.
	 *
	 * @param format 형식 문자열입니다.
	 * @param ... 문자열의 형식에 대응하는 가변인자입니다.
	 *
	 * @return 형식화된 표준 문자열을 반환합니다.
	 *
	 * @see https://learn.microsoft.com/ko-kr/cpp/c-runtime-library/reference/vsnprintf-vsnprintf-vsnprintf-l-vsnwprintf-vsnwprintf-l?view=msvc-170
	 */
	static std::string PrintF(const char* format, ...);


	/**
	 * @brief 형식화된 문자열을 반환합니다.
	 *
	 * @note
	 * - 이 메서드는 snprintf와 같은 함수를 대체하기 위한 것입니다.
	 * - 문자열의 길이는 최대 1024 입니다.
	 *
	 * @param format 형식 문자열입니다.
	 * @param ... 문자열의 형식에 대응하는 가변인자입니다.
	 *
	 * @return 형식화된 표준 문자열을 반환합니다.
	 *
	 * @see https://learn.microsoft.com/ko-kr/cpp/c-runtime-library/reference/vsnprintf-vsnprintf-vsnprintf-l-vsnwprintf-vsnwprintf-l?view=msvc-170
	 */
	static std::wstring PrintF(const wchar_t* format, ...);


	/**
	 * @brief 특정 문자열을 기준으로 텍스트를 분리합니다.
	 *
	 * @param text 분리할 대상 문자열입니다.
	 * @param delimiter 분리를 위한 기준 문자열입니다.
	 *
	 * @return 분리된 문자열을 담고 있는 벡터(std::vector)를 반환합니다.
	 */
	static std::vector<std::string> Split(const std::string& text, const std::string& delimiter);


	/**
	 * @brief 특정 문자열을 기준으로 텍스트를 분리합니다.
	 *
	 * @param text 분리할 대상 문자열입니다.
	 * @param delimiter 분리를 위한 기준 문자열입니다.
	 *
	 * @return 분리된 문자열을 담고 있는 벡터(std::vector)입니다.
	 */
	static std::vector<std::wstring> Split(const std::wstring& text, const std::wstring& delimiter);


	/**
	 * @brief char 문자열을 wchar_t 문자열로 변환합니다.
	 *
	 * @see https://en.cppreference.com/w/cpp/string/multibyte/mbstowcs
	 *
	 * @param text 변환할 표준 텍스트입니다.
	 *
	 * @return 변환된 문자열을 반환합니다.
	 */
	static std::wstring Convert(const std::string& text);


	/**
	 * @brief wchar_t 문자열을 char 문자열로 변환합니다.
	 *
	 * @see https://en.cppreference.com/w/cpp/string/multibyte/wcstombs
	 *
	 * @param text 변환할 표준 텍스트입니다.
	 *
	 * @return 변환된 문자열을 반환합니다.
	 */
	static std::string Convert(const std::wstring& text);


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