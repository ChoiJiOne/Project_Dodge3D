#pragma once

#include <string>
#include <windows.h>


/**
 * @brief Windows 크래시에 대한 확장 기능을 제공합니다.
 */
namespace WindowsCrashUtils
{
	/**
	 * @brief 최상위 예외 처리기를 등록합니다.
	 *
	 * @see https://learn.microsoft.com/ko-kr/windows/win32/api/errhandlingapi/nf-errhandlingapi-setunhandledexceptionfilter
	 */
	void RegisterWindowsExceptionFilter();


	/**
	 * @brief 최상위 예외 처리기 등록을 해제합니다.
	 */
	void UnregisterWindowsExceptionFilter();
};