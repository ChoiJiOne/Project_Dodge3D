#pragma once

#include <cstdint>
#include <functional>
#include <unordered_map>
#include <windows.h>

#include "IManager.h"

class Window;


/**
 * @brief 윈도우 이벤트입니다.
 */
enum class EWindowEvent : int32_t
{
	None          = 0x0000,
	Active        = 0x0001,
	Inactive      = 0x0002,
	Close         = 0x0003,
	Move          = 0x0004,
	Resize        = 0x0005,
	EnterResize   = 0x0006,
	ExitResize    = 0x0007,
	EnterMinimize = 0x0008,
	ExitMinimize  = 0x0009,
	EnterMaximize = 0x0010,
	ExitMaximize  = 0x0011,
};


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
	 * @brief 입력 상태를 업데이트합니다.
	 */
	void Tick();


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
	 * @brief 윈도우 이벤트 액션을 추가합니다.
	 *
	 * @param signature 윈도우 이벤트 액션의 시그니처 값입니다.
	 * @param windowEvent 동작할 액션에 대응하는 윈도우 이벤트입니다.
	 * @param eventAction 이벤트 액션에 대응하는 액션입니다.
	 * @param bIsActive 윈도우 이벤트 액션 활성화 여부입니다. 기본 값은 true입니다.
	 *  
	 * @note 시그니처 문자열의 값은 윈도우 이벤트 액션들에 대응하는 문자열 내에서 유일해야 합니다.
	 */
	void AddWindowEventAction(const std::string& signature, const EWindowEvent& windowEvent, const std::function<void()>& eventAction, bool bIsActive = true);


	/**
	 * @brief 윈도우 이벤트 액션을 삭제합니다.
	 * 
	 * @param signature 윈도우 이벤트 액션의 시그니처 값입니다.
	 * 
	 * @note 시그니처에 대응하는 윈도우 이벤트가 존재하지 않으면 아무 동작도 수행하지 않습니다.
	 */
	void DeleteWindowEventAction(const std::string& signature);


	/**
	 * @brief 윈도우 이벤트 액션의 활성화 여부를 설정합니다.
	 * 
	 * @param signature 윈도우 이벤트 액션의 시그니처 값입니다.
	 * @param bIsActive 윈도우 이벤트의 활성화 여부입니다.
	 * 
	 * @note 시그니처에 대응하는 윈도우 이벤트가 존재하지 않으면 아무 동작도 수행하지 않습니다.
	 */
	void SetActiveWindowEventAction(const std::string& signature, bool bIsActive);


	/**
	 * @brief 윈도우 이벤트에 대응하는 액션들을 실행합니다.
	 * 
	 * @param signature 실행할 윈도우 이벤트입니다.
	 */
	void ExecuteWindowEventAction(const EWindowEvent& windowEvent);


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


	/**
	 * @brief 윈도우 이벤트에 대응하는 액션입니다.
	 */
	struct WindowEventAction
	{
		bool				  bIsActive;         // 윈도우 이벤트의 활성화 여부입니다.
		EWindowEvent		  windowEvent;       // 윈도우 이벤트입니다.
		std::function<void()> windowEventAction; // 윈도우 이벤트에 대응하는 액션입니다.
	};


	/**
	 * @brief 윈도우 이벤트 풀링을 수행합니다.
	 */
	void PollWindowEvents();


private:
	/**
	 * @brief 입력 처리 대상이 되는 윈도우입니다.
	 */
	Window* inputControlWindow_ = nullptr;


	/**
	 * @brief 윈도우 창이 최소화 상태인지 확인합니다.
	 */
	bool bIsMinimize_ = false;


	/**
	 * @brief 윈도우 창이 최대화 상태인지 확인합니다.
	 */
	bool bIsMaximize_ = false;

	
	/**
	 * @brief 윈도우 이벤트에 대응하는 액션입니다.
	 */
	std::unordered_map<std::string, WindowEventAction> windowEventActions_;
};