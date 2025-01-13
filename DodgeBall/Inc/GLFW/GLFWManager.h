#pragma once

#include <array>
#include <functional>
#include <string>

#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include "Utils/Macro.h"

/**
 * --------------------------------------
 * | 이전 프레임 | 현재 프레임 | 입력 상태 |
 * --------------------------------------
 * |     0      |     0      | NONE     |
 * |     0      |     1      | PRESSED  |
 * |     1      |     0      | RELEASED |
 * |     1      |     1      | HELD     |
 * --------------------------------------
 */
enum class EPress : int32_t
{
	NONE     = 0x00,
	PRESSED  = 0x01,
	RELEASED = 0x02,
	HELD     = 0x03
};

/** 키 코드 값입니다. */
enum class EKey
{
	KEY_SPACE = 32,
	KEY_APOSTROPHE = 39,
	KEY_COMMA = 44,
	KEY_MINUS = 45,
	KEY_PERIOD = 46,
	KEY_SLASH = 47,
	KEY_0 = 48,
	KEY_1 = 49,
	KEY_2 = 50,
	KEY_3 = 51,
	KEY_4 = 52,
	KEY_5 = 53,
	KEY_6 = 54,
	KEY_7 = 55,
	KEY_8 = 56,
	KEY_9 = 57,
	KEY_SEMICOLON = 59,
	KEY_EQUAL = 61,
	KEY_A = 65,
	KEY_B = 66,
	KEY_C = 67,
	KEY_D = 68,
	KEY_E = 69,
	KEY_F = 70,
	KEY_G = 71,
	KEY_H = 72,
	KEY_I = 73,
	KEY_J = 74,
	KEY_K = 75,
	KEY_L = 76,
	KEY_M = 77,
	KEY_N = 78,
	KEY_O = 79,
	KEY_P = 80,
	KEY_Q = 81,
	KEY_R = 82,
	KEY_S = 83,
	KEY_T = 84,
	KEY_U = 85,
	KEY_V = 86,
	KEY_W = 87,
	KEY_X = 88,
	KEY_Y = 89,
	KEY_Z = 90,
	KEY_LEFT_BRACKET = 91,
	KEY_BACKSLASH = 92,
	KEY_RIGHT_BRACKET = 93,
	KEY_GRAVE_ACCENT = 96,
	KEY_WORLD_1 = 161,
	KEY_WORLD_2 = 162,
	KEY_ESCAPE = 256,
	KEY_ENTER = 257,
	KEY_TAB = 258,
	KEY_BACKSPACE = 259,
	KEY_INSERT = 260,
	KEY_DELETE = 261,
	KEY_RIGHT = 262,
	KEY_LEFT = 263,
	KEY_DOWN = 264,
	KEY_UP = 265,
	KEY_PAGE_UP = 266,
	KEY_PAGE_DOWN = 267,
	KEY_HOME = 268,
	KEY_END = 269,
	KEY_CAPS_LOCK = 280,
	KEY_SCROLL_LOCK = 281,
	KEY_NUM_LOCK = 282,
	KEY_PRINT_SCREEN = 283,
	KEY_PAUSE = 284,
	KEY_F1 = 290,
	KEY_F2 = 291,
	KEY_F3 = 292,
	KEY_F4 = 293,
	KEY_F5 = 294,
	KEY_F6 = 295,
	KEY_F7 = 296,
	KEY_F8 = 297,
	KEY_F9 = 298,
	KEY_F10 = 299,
	KEY_F11 = 300,
	KEY_F12 = 301,
	KEY_F13 = 302,
	KEY_F14 = 303,
	KEY_F15 = 304,
	KEY_F16 = 305,
	KEY_F17 = 306,
	KEY_F18 = 307,
	KEY_F19 = 308,
	KEY_F20 = 309,
	KEY_F21 = 310,
	KEY_F22 = 311,
	KEY_F23 = 312,
	KEY_F24 = 313,
	KEY_F25 = 314,
	KEY_KP_0 = 320,
	KEY_KP_1 = 321,
	KEY_KP_2 = 322,
	KEY_KP_3 = 323,
	KEY_KP_4 = 324,
	KEY_KP_5 = 325,
	KEY_KP_6 = 326,
	KEY_KP_7 = 327,
	KEY_KP_8 = 328,
	KEY_KP_9 = 329,
	KEY_KP_DECIMAL = 330,
	KEY_KP_DIVIDE = 331,
	KEY_KP_MULTIPLY = 332,
	KEY_KP_SUBTRACT = 333,
	KEY_KP_ADD = 334,
	KEY_KP_ENTER = 335,
	KEY_KP_EQUAL = 336,
	KEY_LEFT_SHIFT = 340,
	KEY_LEFT_CONTROL = 341,
	KEY_LEFT_ALT = 342,
	KEY_LEFT_SUPER = 343,
	KEY_RIGHT_SHIFT = 344,
	KEY_RIGHT_CONTROL = 345,
	KEY_RIGHT_ALT = 346,
	KEY_RIGHT_SUPER = 347,
	KEY_MENU = 348
};

/** 마우스 코드 값입니다. */
enum class EMouse
{
	LEFT   = 0,
	RIGHT  = 1,
	MIDDLE = 2,
};

/** GLFW 윈도우 이벤트입니다. */
enum class EWindowEvent
{
	NONE         = 0x00,
	MOVE_ENTER   = 0x01,
	MOVE_LEAVE   = 0x02,
	FOCUS_GAIN   = 0x03,
	FOCUS_LOST   = 0x04,
	CLOSE_WINDOW = 0x05,
};

/** 윈도우 이벤트의 ID 값입니다. */
using WindowEventID = uint32_t;

/**
 * GLFW 관련 처리를 수행하는 매니저입니다.
 * 이때, 이 매니저 클래스는 싱글턴입니다.
 */
class GLFWManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(GLFWManager);

	/** GLFW 매니저의 싱글턴 객체 참조자를 얻습니다. */
	static GLFWManager& GetRef();

	/** GLFW 매니저의 싱글턴 객체 포인터를 얻습니다. */
	static GLFWManager* GetPtr();

	/** GLFW 매니저의 초기화를 수행합니다. */
	void Startup(int32_t width, int32_t height, const char* title, bool bIsWindowCentered);

	/** GLFW 매니저의 초기화 해제를 수행합니다. */
	void Shutdown();

	/** 한 프레임을 시작합니다. */
	void Tick();

	/** 현재 윈도우 크기를 얻습니다. */
	void GetWindowSize(float& outWidth, float& outHeight);

	/** 커서가 윈도우 내부에 있는지 확인합니다. */
	bool IsEnterCursor() const { return bIsEnterCursor_; }

	/** 현재 키 값의 입력 상태를 얻습니다. */
	EPress GetKeyPress(const EKey& key);

	/** 현재 마우스의 입력 상태를 얻습니다. */
	EPress GetMousePress(const EMouse& mouse);

	/** Tick 호출 이전의 커서 위치를 얻습니다. */
	const glm::vec2& GetPrevCursorPos() const { return prevCursorPos_; }

	/** Tick 호출 이후의 커서 위치를 얻습니다. */
	const glm::vec2& GetCurrCursorPos() const { return currCursorPos_; }

	/** GLFW 매니저에 윈도우 이벤트 액션을 등록합니다. */
	WindowEventID AddWindowEventAction(const EWindowEvent& windowEvent, const std::function<void()>& eventAction, bool bIsActive = true);

	/** GLFW 매니저에 윈도우 이벤트 액션을 삭제합니다. */
	void DeleteWindowEventAction(const WindowEventID& windowEventID);

	/** 등록된 윈도우 이벤트 액션의 활성화 여부를 설정합니다. */
	void SetActiveWindowEventAction(const WindowEventID& windowEventID, bool bIsActive);

private:
	/**
	 * GLFW 매니저의 기본 생성자와 빈 가상 소멸자입니다.
	 * 싱글턴으로 구현하기 위해 private으로 숨겼습니다.
	 */
	GLFWManager() = default;
	virtual ~GLFWManager() {}

	/** 윈도우 이벤트 발생 시 실행할 동작입니다. */
	struct WindowEventAction
	{
		EWindowEvent          windowEvent = EWindowEvent::NONE; /** 윈도우 이벤트의 종류입니다. */
		std::function<void()> windowEventAction = nullptr;      /** 이벤트 감지 시 실행할 액션입니다. */
		bool                  bIsActive = false;                /** 이벤트 활성화 여부입니다. */

	};

	/** GLFW 에러 처리를 위한 콜백 함수입니다. */
	static void ErrorCallback(int32_t errorCode, const char* description);

	/** 마우스 커서가 움직일 때 호출되는 콜백 함수입니다. */
	static void CursorMoveCallback(GLFWwindow* window, double x, double y);

	/** 마우스 커서가 진입했을 때 호출되는 콜백 함수입니다. */
	static void CursorEnterCallback(GLFWwindow* window, int32_t entered);

	/** 윈도우 창이 움직였을 때 호출되는 콜백 함수입니다. */
	static void MoveWindowCallback(GLFWwindow* window, int32_t x, int32_t y);

	/** 윈도우 창의 포커스 관련 요소가 변경되었을 때 콜백 함수입니다. */
	static void FocusWindowCallback(GLFWwindow* window, int32_t focused);

	/** 윈도우 창을 닫았을 때 호출되는 콜백 함수입니다. */
	static void CloseWindowCallback(GLFWwindow* window);

	/** 커서의 윈도우 창 진입 여부를 설정합니다. */
	void SetCursorEnter(int32_t entered);

	/** 현재 커서 위치를 설정합니다. */
	void SetCursorPosition(double x, double y);

	/** 윈도우 움직임을 설정합니다. */
	void SetWindowMove(int32_t x, int32_t y);

	/** 윈도우 포커스 여부를 설정합니다. */
	void SetWindowFocus(int32_t focused);

	/** 윈도우 종료 이벤트를 설정합니다. */
	void SetWindowClose();

	/** 해당 키가 눌렸는지 확인합니다. */
	bool IsPressKey(const int32_t* keyboardState, const EKey& key);

	/** 키보드 상태를 업데이트합니다. */
	void UpdateKeyboardState();

	/** 마우스 버튼이 눌렸는지 확인합니다. */
	bool IsPressButton(const int32_t* mouseState, const EMouse& mouse);

	/** 마우스 상태를 업데이트합니다. */
	void UpdateMouseState();

	/** 윈도우 이벤트 액션을 실행합니다. */
	void RunWindowEventAction(const EWindowEvent& windowEvent);

private:
	/** GLFW 매니저의 싱글턴 객체입니다. */
	static GLFWManager singleton_;

	/** GLFW 매니저가 관리하는 메인 윈도우입니다. */
	GLFWwindow* mainWindow_ = nullptr;

	/** GLFW 매니저가 관리하는 메인 윈도우의 가로/세로 크기입니다. */
	int32_t mainWindowWidth_ = 0;
	int32_t mainWindowHeight_ = 0;

	/** 커서가 윈도우 내부에 있는지 확인합니다. */
	bool bIsEnterCursor_ = true;

	/** Tick 호출 이전의 커서 위치입니다. */
	glm::vec2 prevCursorPos_ = glm::vec2();

	/** Tick 호출 이후의 커서 위치입니다. */
	glm::vec2 currCursorPos_ = glm::vec2();

	/** 키 상태 배열의 크기 값입니다. */
	static const uint32_t KEY_BOARD_STATE_SIZE = 348;

	/** Tick 호출 이전의 키 상태입니다. */
	std::array<int32_t, KEY_BOARD_STATE_SIZE> prevKeyboardState_;

	/** Tick 호출 이후의 키 상태입니다. */
	std::array<int32_t, KEY_BOARD_STATE_SIZE> currKeyboardState_;

	/** 마우스 상태 배열의 크기 값입니다. */
	static const uint32_t MOUSE_STATE_SIZE = 3;

	/** Tick 호출 이전의 마우스 상태입니다. */
	std::array<int32_t, MOUSE_STATE_SIZE> prevMouseState_;

	/** Tick 호출 이후의 마우스 상태입니다. */
	std::array<int32_t, MOUSE_STATE_SIZE> currMouseState_;

	/** 윈도우 움직임이 시작 되었는지 확인합니다. */
	bool bIsStartMoveWindow_ = false;

	/** 윈도우 움직임이 감지되었는지 확인합니다. */
	bool bIsDetectMoveWindow_ = false;

	/** GLFW 에러 발생 여부입니다. */
	bool bIsDetectError_ = false;

	/** 최대 등록할 수 있는 윈도우 이벤트 액션 수입니다. */
	static const uint32_t MAX_EVENT_ACTION_SIZE = 100;

	/** 현재 윈도우 이벤트 액션의 버퍼 크기입니다. */
	uint32_t windowEventActionSize_ = 0;

	/** 동작할 윈도우 이벤트 액션 목록입니다. */
	std::array<WindowEventAction, MAX_EVENT_ACTION_SIZE> windowEventActions_;
};