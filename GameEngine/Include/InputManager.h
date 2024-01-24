#pragma once

#include <array>
#include <cstdint>
#include <functional>
#include <string>
#include <unordered_map>
#include <windows.h>

#include "IManager.h"
#include "Vector2.h"

class Window;


/**
 * @brief 입력 상태를 나타냅니다.
 *
 * --------------------------------------
 * | 이전 프레임 | 현재 프레임 | 입력 상태 |
 * --------------------------------------
 * |     0      |     0      | NONE     |
 * |     0      |     1      | PRESSED  |
 * |     1      |     0      | RELEASED |
 * |     1      |     1      | HELD     |
 * --------------------------------------
 */
enum class EPressState
{
	None     = 0x00,
	Pressed  = 0x01,
	Released = 0x02,
	Held     = 0x03
};


/**
 * @brief 가상 키의 값입니다.
 * 
 * @see https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
 */
enum class EVirtualKey : int32_t
{
	VKEY_NONE = 0x00,
	VKEY_LBUTTON = 0x01,
	VKEY_RBUTTON = 0x02,
	VKEY_CANCEL = 0x03,
	VKEY_MBUTTON = 0x04,
	VKEY_XBUTTON1 = 0x05,
	VKEY_XBUTTON2 = 0x06,
	VKEY_BACK = 0x08,
	VKEY_TAB = 0x09,
	VKEY_CLEAR = 0x0C,
	VKEY_RETURN = 0x0D,
	VKEY_SHIFT = 0x10,
	VKEY_CONTROL = 0x11,
	VKEY_MENU = 0x12,
	VKEY_PAUSE = 0x13,
	VKEY_CAPITAL = 0x14,
	VKEY_KANA = 0x15,
	VKEY_HANGUEL = 0x15,
	VKEY_HANGUL = 0x15,
	VKEY_IME_ON = 0x16,
	VKEY_JUNJA = 0x17,
	VKEY_FINAL = 0x18,
	VKEY_HANJA = 0x19,
	VKEY_KANJI = 0x19,
	VKEY_IME_OFF = 0x1A,
	VKEY_ESCAPE = 0x1B,
	VKEY_CONVERT = 0x1C,
	VKEY_NONCONVERT = 0x1D,
	VKEY_ACCEPT = 0x1E,
	VKEY_MODECHANGE = 0x1F,
	VKEY_SPACE = 0x20,
	VKEY_PRIOR = 0x21,
	VKEY_NEXT = 0x22,
	VKEY_END = 0x23,
	VKEY_HOME = 0x24,
	VKEY_LEFT = 0x25,
	VKEY_UP = 0x26,
	VKEY_RIGHT = 0x27,
	VKEY_DOWN = 0x28,
	VKEY_SELECT = 0x29,
	VKEY_PRINT = 0x2A,
	VKEY_EXECUTE = 0x2B,
	VKEY_SNAPSHOT = 0x2C,
	VKEY_INSERT = 0x2D,
	VKEY_DELETE = 0x2E,
	VKEY_HELP = 0x2F,
	VKEY_0 = 0x30,
	VKEY_1 = 0x31,
	VKEY_2 = 0x32,
	VKEY_3 = 0x33,
	VKEY_4 = 0x34,
	VKEY_5 = 0x35,
	VKEY_6 = 0x36,
	VKEY_7 = 0x37,
	VKEY_8 = 0x38,
	VKEY_9 = 0x39,
	VKEY_A = 0x41,
	VKEY_B = 0x42,
	VKEY_C = 0x43,
	VKEY_D = 0x44,
	VKEY_E = 0x45,
	VKEY_F = 0x46,
	VKEY_G = 0x47,
	VKEY_H = 0x48,
	VKEY_I = 0x49,
	VKEY_J = 0x4A,
	VKEY_K = 0x4B,
	VKEY_L = 0x4C,
	VKEY_M = 0x4D,
	VKEY_N = 0x4E,
	VKEY_O = 0x4F,
	VKEY_P = 0x50,
	VKEY_Q = 0x51,
	VKEY_R = 0x52,
	VKEY_S = 0x53,
	VKEY_T = 0x54,
	VKEY_U = 0x55,
	VKEY_V = 0x56,
	VKEY_W = 0x57,
	VKEY_X = 0x58,
	VKEY_Y = 0x59,
	VKEY_Z = 0x5A,
	VKEY_LWIN = 0x5B,
	VKEY_RWIN = 0x5C,
	VKEY_APPS = 0x5D,
	VKEY_SLEEP = 0x5F,
	VKEY_NUMPAD0 = 0x60,
	VKEY_NUMPAD1 = 0x61,
	VKEY_NUMPAD2 = 0x62,
	VKEY_NUMPAD3 = 0x63,
	VKEY_NUMPAD4 = 0x64,
	VKEY_NUMPAD5 = 0x65,
	VKEY_NUMPAD6 = 0x66,
	VKEY_NUMPAD7 = 0x67,
	VKEY_NUMPAD8 = 0x68,
	VKEY_NUMPAD9 = 0x69,
	VKEY_MULTIPLY = 0x6A,
	VKEY_ADD = 0x6B,
	VKEY_SEPARATOR = 0x6C,
	VKEY_SUBTRACT = 0x6D,
	VKEY_DECIMAL = 0x6E,
	VKEY_DIVIDE = 0x6F,
	VKEY_F1 = 0x70,
	VKEY_F2 = 0x71,
	VKEY_F3 = 0x72,
	VKEY_F4 = 0x73,
	VKEY_F5 = 0x74,
	VKEY_F6 = 0x75,
	VKEY_F7 = 0x76,
	VKEY_F8 = 0x77,
	VKEY_F9 = 0x78,
	VKEY_F10 = 0x79,
	VKEY_F11 = 0x7A,
	VKEY_F12 = 0x7B,
	VKEY_F13 = 0x7C,
	VKEY_F14 = 0x7D,
	VKEY_F15 = 0x7E,
	VKEY_F16 = 0x7F,
	VKEY_F17 = 0x80,
	VKEY_F18 = 0x81,
	VKEY_F19 = 0x82,
	VKEY_F20 = 0x83,
	VKEY_F21 = 0x84,
	VKEY_F22 = 0x85,
	VKEY_F23 = 0x86,
	VKEY_F24 = 0x87,
	VKEY_NUMLOCK = 0x90,
	VKEY_SCROLL = 0x91,
	VKEY_LSHIFT = 0xA0,
	VKEY_RSHIFT = 0xA1,
	VKEY_LCONTROL = 0xA2,
	VKEY_RCONTROL = 0xA3,
	VKEY_LMENU = 0xA4,
	VKEY_RMENU = 0xA5,
	VKEY_BROWSER_BACK = 0xA6,
	VKEY_BROWSER_FORWARD = 0xA7,
	VKEY_BROWSER_REFRESH = 0xA8,
	VKEY_BROWSER_STOP = 0xA9,
	VKEY_BROWSER_SEARCH = 0xAA,
	VKEY_BROWSER_FAVORITES = 0xAB,
	VKEY_BROWSER_HOME = 0xAC,
	VKEY_VOLUME_MUTE = 0xAD,
	VKEY_VOLUME_DOWN = 0xAE,
	VKEY_VOLUME_UP = 0xAF,
	VKEY_MEDIA_NEXT_TRACK = 0xB0,
	VKEY_MEDIA_PREV_TRACK = 0xB1,
	VKEY_MEDIA_STOP = 0xB2,
	VKEY_MEDIA_PLAY_PAUSE = 0xB3,
	VKEY_LAUNCH_MAIL = 0xB4,
	VKEY_LAUNCH_MEDIA_SELECT = 0xB5,
	VKEY_LAUNCH_APP1 = 0xB6,
	VKEY_LAUNCH_APP2 = 0xB7,
	VKEY_OEM_1 = 0xBA,
	VKEY_OEM_PLUS = 0xBB,
	VKEY_OEM_COMMA = 0xBC,
	VKEY_OEM_MINUS = 0xBD,
	VKEY_OEM_PERIOD = 0xBE,
	VKEY_OEM_2 = 0xBF,
	VKEY_OEM_3 = 0xC0,
	VKEY_OEM_4 = 0xDB,
	VKEY_OEM_5 = 0xDC,
	VKEY_OEM_6 = 0xDD,
	VKEY_OEM_7 = 0xDE,
	VKEY_OEM_8 = 0xDF,
	VKEY_OEM_102 = 0xE2,
	VKEY_PACKET = 0xE7,
	VKEY_ATTN = 0xF6,
	VKEY_CRSEL = 0xF7,
	VKEY_EXSEL = 0xF8,
	VKEY_EREOF = 0xF9,
	VKEY_PLAY = 0xFA,
	VKEY_ZOOM = 0xFB,
	VKEY_NONAME = 0xFC,
	VKEY_PA1 = 0xFD,
	VKEY_OEM_CLEAR = 0xFE,
};


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
	 * @brief ImGui 라이브러리 활성화 여부를 설정합니다.
	 * 
	 * @param bIsEnable ImGui 라이브러리 활성화 여부입니다.
	 */
	void SetEnableImGui(bool bIsEnable) { bIsEnableImGui_ = bIsEnable; }


	/**
	 * @brief 입력 처리 대상이 되는 윈도우를 얻습니다.
	 * 
	 * @return 입력 처리 대상이 되는 윈도우의 포인터를 얻습니다.
	 */
	Window* GetInputControlWindow() const { return inputControlWindow_; }


	/**
	 * @brief 가상 키 값의 입력 상태를 얻습니다.
	 * 
	 * @param virtualKey 입력 상태를 얻을 가상 키 값입니다.
	 * 
	 * @return 키 값의 입력 상태를 반환합니다.
	 */
	EPressState GetVirtualKeyPressState(const EVirtualKey& virtualKey);


	/**
	 * @brief Tick 호출 이후의 커서 위치를 얻습니다.
	 *
	 * @return Tick 호출 이후의 커서 위치를 반환합니다.
	 */
	Vector2i GetPrevCursorPosition() const { return prevCursorPosition_; }


	/**
	 * @brief Tick 호출 이전의 커서 위치를 얻습니다.
	 * 
	 * @return Tick 호출 이전의 커서 위치를 반환합니다.
	 */
	Vector2i GetCurrCursorPosition() const { return currCursorPosition_; }


	/**
	 * @brief Tick 호출 이전과 이후의 커서 위치 차이를 얻습니다.
	 * 
	 * @return Tick 호출 이전과 이후의 커서 위치 차이값을 반환합니다.
	 */
	Vector2i GetDiffCursorPosition() const { return currCursorPosition_ - prevCursorPosition_; }


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


	/**
	 * @brief 특정 가상 키가 눌렸는지 확인합니다.
	 * 
	 * @param keyBufferPtr 검사를 수행할 가상 키 버퍼의 포인터입니다.
	 * @param virtualKey 눌렸는지 확인할 가상 키입니다.
	 * 
	 * @return 키가 눌렸다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsPressKey(const uint8_t* keyBufferPtr, const EVirtualKey& virtualKey) const;


	/**
	 * @brief 현재 마우스의 위치를 얻습니다.
	 * 
	 * @return 윈도우 좌표계 기준의 마우스 위치를 반환합니다.
	 */
	Vector2i GetCurrentCursorPosition();


private:
	/**
	 * @brief 입력 처리 대상이 되는 윈도우입니다.
	 */
	Window* inputControlWindow_ = nullptr;


	/**
	 * @brief IMGUI가 활성화 되었는지 확인합니다.
	 */
	bool bIsEnableImGui_ = false;


	/**
	 * @brief 가상 키 버퍼의 크기입니다.
	 */
	static const int32_t VIRTUAL_KEY_BUFFER_SIZE = 256;


	/**
	 * @brief 업데이트(Tick) 이전의 가상 키 버퍼의 상태입니다.
	 */
	std::array<uint8_t, VIRTUAL_KEY_BUFFER_SIZE> prevKeyboardState_ = {};


	/**
	 * @brief 업데이트(Tick) 이후의 가상 키 버퍼의 상태입니다.
	 */
	std::array<uint8_t, VIRTUAL_KEY_BUFFER_SIZE> currKeyboardState_ = {};


	/**
	 * @brief 업데이트(Tick) 이전의 커서 위치입니다.
	 */
	Vector2i prevCursorPosition_;


	/**
	 * @brief 업데이트(Tick) 이후의 커서 위치입니다.
	 */
	Vector2i currCursorPosition_;

	
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