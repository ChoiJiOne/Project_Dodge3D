#pragma once

#include <cstdint>
#include <windows.h>

#include "IManager.h"

class Window;


/**
 * @brief 입력 처리를 수행하는 매니저입니다.
 * 
 * @note 이 클래스는 싱글턴입니다.
 */
class InputManager : public IManager
{
public:
	/**
	 * @brief 입력 처리를 수행하는 매니저의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(InputManager);


	/**
	 * @brief 입력 처리를 수행하는 매니저의 참조 인스턴스를 얻습니다.
	 * 
	 * @return 입력 처리를 수행하는 매니저의 참조자를 반환합니다.
	 */
	static InputManager& Get()
	{
		static InputManager instance;
		return instance;
	}


	/**
	 * @brief 입력 처리를 수행하는 매니저의 사용을 시작합니다.
	 *
	 * @note
	 * - 이 메서드 호출 전에 입력 처리 대상이 되는 윈도우 포인터를 설정해야 합니다.
	 * - 이 메서드는 한 번만 호출되어야 합니다.
	 */
	virtual void Startup() override;


	/**
	 * @brief 입력 처리를 수행하는 매니저의 사용을 종료합니다.
	 *
	 * @note
	 * - 애플리케이션 종료 전에 이 메서드를 반드시 호출하여 내부 리소스를 정리해야 합니다.
	 * - 이 메서드는 반드시 한 번만 호출되어야 합니다.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief 입력 처리 대상이 되는 윈도우를 설정합니다.
	 * 
	 * @param window 입력 처리 대상이 되는 윈도우입니다.
	 */
	void SetInputControlWindow(Window* window) { inputControlWindow_ = window; }


	/**
	 * @brief 입력 처리 대상이 되는 윈도우를 얻습니다.
	 * 
	 * @return 입력 처리 대상이 되는 윈도우의 포인터를 얻습니다.
	 */
	Window* GetInputControlWindow() const { return inputControlWindow_; }


	/**
	 * @brief 윈도우 메시지를 처리합니다.
	 *
	 * @param windowHandle 프로시저를 처리할 윈도우 핸들입니다.
	 * @param message 메시지 식별자입니다.
	 * @param wParam 메시지의 부가 정보입니다.
	 * @param lParam 메시지의 부가 정보입니다.
	 *
	 * @return 메시지를 처리했을 경우 0을 반환합니다. 그렇지 않으면 DefWindowProcW가 반환된 값을 반환합니다.
	 *
	 * @see
	 * - https://learn.microsoft.com/ko-kr/windows/win32/winmsg/window-procedures
	 * - ProcessWindowMessage 내부에서 메시지를 처리했을 경우는 0을 반환
	 */
	LRESULT ProcessWindowMessage(HWND windowHandle, uint32_t message, WPARAM wParam, LPARAM lParam);


	/**
	 * @brief 기본적인 윈도우 메시지를 처리합니다.
	 * 
	 * @param windowHandle 프로시저를 처리할 윈도우 핸들입니다.
	 * @param message 메시지 식별자입니다.
	 * @param wParam 메시지의 부가 정보입니다.
	 * @param lParam 메시지의 부가 정보입니다.
	 * 
	 * @return 메시지를 처리했을 경우 0을 반환합니다. 그렇지 않으면 DefWindowProcW가 반환된 값을 반환합니다.
	 * 
	 * @see 
	 * - https://learn.microsoft.com/ko-kr/windows/win32/winmsg/window-procedures
	 * - ProcessWindowMessage 내부에서 메시지를 처리했을 경우는 0을 반환
	 */
	static LRESULT CALLBACK WindowProc(HWND windowHandle, uint32_t message, WPARAM wParam, LPARAM lParam);


private:
	/**
	 * @brief 렌더링 처리를 수행하는 매니저에 디폴트 생성자와 빈 가상 소멸자를 삽입합니다.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(InputManager);


private:
	/**
	 * @brief 입력 처리 대상이 되는 윈도우입니다.
	 */
	Window* inputControlWindow_ = nullptr;
};