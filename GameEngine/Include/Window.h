#pragma once

#include <cstdint>
#include <string>
#include <windows.h>


/**
 * @brief 윈도우 프로시저입니다.
 */
typedef LRESULT(CALLBACK* WINDOWPROC)(HWND, uint32_t, WPARAM, LPARAM);


/**
 * @brief 윈도우를 생성하고 관리합니다.
 */
class Window
{
public:
	/**
	 * @brief 윈도우를 생성하고 관리하는 클래스의 디폴트 생성자입니다.
	 */
	Window() = default;


	/**
	 * @brief 윈도우를 생성하고 관리하는 클래스의 가상 소멸자입니다.
	 */
	virtual ~Window();


	/**
	 * @brief 윈도우 클래스를 등록합니다.
	 * 
	 * @note 이 정적 메서드는 한 번만 호출할 수 있습니다.
	 * 
	 * @param windowClassName 등록할 윈도우 클래스의 이름입니다.
	 * @param windowProc 등록할 윈도우 클래스의 프로시저입니다.
	 */
	static void RegisterWindowClass(const std::wstring& windowClassName, WINDOWPROC windowProc);


	/**
	 * @brief 윈도우 클래스를 등록 해제합니다.
	 */
	static void UnregisterWindowClass();


	/**
	 * @brief 윈도우 클래스를 등록했는지 확인합니다.
	 * 
	 * @return 윈도우 클래스를 등록했다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	static bool IsRegisterWindowClass() { return bIsRegisterWindowClass_; }


private:
	/**
	 * @brief 윈도우 클래스를 등록했는지 확인합니다.
	 */
	static bool bIsRegisterWindowClass_;


	/**
	 * @brief 인스턴스에 대한 핸들입니다.
	 * 
	 * @note
	 * - 인스턴스에 대한 핸들은 메모리에 있는 모듈의 기본 주소입니다.
	 * - 참조 : https://learn.microsoft.com/ko-kr/windows/win32/winprog/windows-data-types#:~:text=typedef%20HANDLE%20HICON%3B-,HINSTANCE,-instance%20%EB%8C%80%ED%95%9C%20%ED%95%B8%EB%93%A4%EC%9E%85%EB%8B%88%EB%8B%A4
	 */
	static HINSTANCE hInstance_;


	/**
	 * @brief 윈도우 클래스의 이름입니다.
	 * 
	 * @note 
	 * - 윈도우 클래스는 스타일, 아이콘, 커서, 메뉴 및 윈도우 프로시저와 같은 특성을 정의합니다.
	 * - 참조 : https://learn.microsoft.com/ko-kr/windows/win32/winmsg/about-window-classes#types-of-window-classes
	 */
	static std::wstring windowClassName_;


	/**
	 * @brief 윈도우 핸들입니다.
	 */
	HWND windowHandle_ = nullptr;


	/**
	 * @brief 윈도우의 크기를 바꿀 수 있는지 확인합니다.
	 */
	bool bIsResizable_ = false;
};