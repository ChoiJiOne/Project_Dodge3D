#pragma once

#include <string>
#include <windows.h>


/**
 * @brief Windows 크래시에 대한 확장 기능을 제공합니다.
 * 
 * @note 이 클래스의 모든 멤버 변수와 메서드는 모두 static입니다.
 */
class WindowsCrashUtils
{
public:
	/**
	 * @brief 최상위 예외 처리기를 등록합니다.
	 *
	 * @see https://learn.microsoft.com/ko-kr/windows/win32/api/errhandlingapi/nf-errhandlingapi-setunhandledexceptionfilter
	 */
	static void RegisterExceptionFilter();


	/**
	 * @brief 최상위 예외 처리기 등록을 해제합니다.
	 */
	static void UnregisterExceptionFilter();


	/**
	 * @brief 크래시를 감지하고 에러 처리를 수행합니다.
	 * 
	 * @param exceptionPtr 예외와 컨텍스트 레코드입니다.
	 * 
	 * @return EXCEPTION_EXECUTE_HANDLER 값을 반환합니다.
	 */
	static LONG WINAPI DetectApplicationCrash(EXCEPTION_POINTERS* exceptionPtr);


private:
	/**
	 * @brief 크래시가 감지된 시스템 시간값을 얻습니다.
	 * 
	 * @return 시스템 시간값을 반환합니다.
	 */
	static std::wstring GetCrashSystemTime();

	
private:
	/**
	 * @brief 크래시와 관련된 파일들을 저장할 경로입니다.
	 * 
	 * @note 크래시와 관련된 파일은 미니 덤프 파일과 콜스택 기록 파일입니다.
	 */
	static std::wstring crashInfoSavePath_;
};