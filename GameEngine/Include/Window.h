#pragma once

#include <cstdint>
#include <string>
#include <windows.h>

#include "Macro.h"


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
	 * @brief 윈도우를 생성하고 관리하는 클래스의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Window);


	/**
	 * @brief 윈도우를 생성합니다.
	 * 
	 * @note 풀 스크린 모드 설정 시 일부 옵션은 무시됩니다.
	 * 
	 * @param title 윈도우의 타이틀입니다.
	 * @param x 윈도우 위치의 X좌표입니다. 
	 * @param y 윈도우 위치의 Y좌표입니다. 
	 * @param w 윈도우의 가로 크기입니다.
	 * @param h 윈도우의 세로 크기입니다.
	 * @param bIsResizable 윈도우의 크기 변환 여부입니다.
	 * @param bIsShow 윈도우를 표시할 시 여부입니다
	 * @param bIsFullscreenMode 윈도우를 풀 스크린 모드로 설정할 지 여부입니다.
	 */
	void Create(const std::wstring& title, int32_t x, int32_t y, int32_t w, int32_t h, bool bIsResizable, bool bIsShow, bool bIsFullscreenMode);


	/**
	 * @brief 윈도우를 파괴합니다.
	 */
	void Destroy();


	/**
	 * @brief 윈도우가 풀 스크린모드인지 확인합니다.
	 * 
	 * @return 윈도우가 풀 스크린모드라면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsFullscreenMode() const { return bIsFullscreenMode_; }


	/**
	 * @brief 윈도우의 크기를 변경할 수 있는지 확인합니다.
	 * 
	 * @return 윈도우의 크기를 변경할 수 있다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsResizable() const { return bIsResizable_; }


	/**
	 * @brief 윈도우 핸들을 얻습니다.
	 * 
	 * @return 윈도우 핸들을 반환합니다.
	 */
	HWND GetHandle() { return windowHandle_; }


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
	 * @brief 윈도우 핸들입니다.
	 */
	HWND windowHandle_ = nullptr;


	/**
	 * @brief 윈도우의 크기를 바꿀 수 있는지 확인합니다.
	 */
	bool bIsResizable_ = false;


	/**
	 * @brief 풀 스크린 모드인지 확인합니다.
	 */
	bool bIsFullscreenMode_ = false;
	

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
};