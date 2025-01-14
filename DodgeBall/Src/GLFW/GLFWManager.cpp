#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "GLFW/GLFWAssert.h"
#include "GLFW/GLFWManager.h"

#include "Utils/Assertion.h"
#include "Utils/MemoryAlloc.h"

#define GL_MAJOR_VERSION 4
#define GL_MINOR_VERSION 6

GLFWManager GLFWManager::singleton_;


static const std::array<EKey, 119> KEYS =
{
	EKey::KEY_SPACE,
	EKey::KEY_APOSTROPHE,
	EKey::KEY_COMMA,
	EKey::KEY_MINUS,
	EKey::KEY_PERIOD,
	EKey::KEY_SLASH,
	EKey::KEY_0,
	EKey::KEY_1,
	EKey::KEY_2,
	EKey::KEY_3,
	EKey::KEY_4,
	EKey::KEY_5,
	EKey::KEY_6,
	EKey::KEY_7,
	EKey::KEY_8,
	EKey::KEY_9,
	EKey::KEY_SEMICOLON,
	EKey::KEY_EQUAL,
	EKey::KEY_A,
	EKey::KEY_B,
	EKey::KEY_C,
	EKey::KEY_D,
	EKey::KEY_E,
	EKey::KEY_F,
	EKey::KEY_G,
	EKey::KEY_H,
	EKey::KEY_I,
	EKey::KEY_J,
	EKey::KEY_K,
	EKey::KEY_L,
	EKey::KEY_M,
	EKey::KEY_N,
	EKey::KEY_O,
	EKey::KEY_P,
	EKey::KEY_Q,
	EKey::KEY_R,
	EKey::KEY_S,
	EKey::KEY_T,
	EKey::KEY_U,
	EKey::KEY_V,
	EKey::KEY_W,
	EKey::KEY_X,
	EKey::KEY_Y,
	EKey::KEY_Z,
	EKey::KEY_LEFT_BRACKET,
	EKey::KEY_BACKSLASH,
	EKey::KEY_RIGHT_BRACKET,
	EKey::KEY_GRAVE_ACCENT,
	EKey::KEY_WORLD_1,
	EKey::KEY_WORLD_2,
	EKey::KEY_ESCAPE,
	EKey::KEY_ENTER,
	EKey::KEY_TAB,
	EKey::KEY_BACKSPACE,
	EKey::KEY_INSERT,
	EKey::KEY_DELETE,
	EKey::KEY_RIGHT,
	EKey::KEY_LEFT,
	EKey::KEY_DOWN,
	EKey::KEY_UP,
	EKey::KEY_PAGE_UP,
	EKey::KEY_PAGE_DOWN,
	EKey::KEY_HOME,
	EKey::KEY_END,
	EKey::KEY_CAPS_LOCK,
	EKey::KEY_SCROLL_LOCK,
	EKey::KEY_NUM_LOCK,
	EKey::KEY_PRINT_SCREEN,
	EKey::KEY_PAUSE,
	EKey::KEY_F1,
	EKey::KEY_F2,
	EKey::KEY_F3,
	EKey::KEY_F4,
	EKey::KEY_F5,
	EKey::KEY_F6,
	EKey::KEY_F7,
	EKey::KEY_F8,
	EKey::KEY_F9,
	EKey::KEY_F10,
	EKey::KEY_F11,
	EKey::KEY_F12,
	EKey::KEY_F13,
	EKey::KEY_F14,
	EKey::KEY_F15,
	EKey::KEY_F16,
	EKey::KEY_F17,
	EKey::KEY_F18,
	EKey::KEY_F19,
	EKey::KEY_F20,
	EKey::KEY_F21,
	EKey::KEY_F22,
	EKey::KEY_F23,
	EKey::KEY_F24,
	EKey::KEY_F25,
	EKey::KEY_KP_0,
	EKey::KEY_KP_1,
	EKey::KEY_KP_2,
	EKey::KEY_KP_3,
	EKey::KEY_KP_4,
	EKey::KEY_KP_5,
	EKey::KEY_KP_6,
	EKey::KEY_KP_7,
	EKey::KEY_KP_8,
	EKey::KEY_KP_9,
	EKey::KEY_KP_DECIMAL,
	EKey::KEY_KP_DIVIDE,
	EKey::KEY_KP_MULTIPLY,
	EKey::KEY_KP_SUBTRACT,
	EKey::KEY_KP_ADD,
	EKey::KEY_KP_ENTER,
	EKey::KEY_KP_EQUAL,
	EKey::KEY_LEFT_SHIFT,
	EKey::KEY_LEFT_CONTROL,
	EKey::KEY_LEFT_ALT,
	EKey::KEY_LEFT_SUPER,
	EKey::KEY_RIGHT_SHIFT,
	EKey::KEY_RIGHT_CONTROL,
	EKey::KEY_RIGHT_ALT,
	EKey::KEY_RIGHT_SUPER,
};

void GLFWManager::CursorMoveCallback(GLFWwindow* window, double x, double y)
{
	singleton_.SetCursorPosition(x, y);
}

void GLFWManager::CursorEnterCallback(GLFWwindow* window, int32_t entered)
{
	singleton_.SetCursorEnter(entered);
}

void GLFWManager::MoveWindowCallback(GLFWwindow* window, int32_t x, int32_t y)
{
	singleton_.SetWindowMove(x, y);
}

void GLFWManager::FocusWindowCallback(GLFWwindow* window, int32_t focused)
{
	singleton_.SetWindowFocus(focused);
}

void GLFWManager::CloseWindowCallback(GLFWwindow* window)
{
	singleton_.SetWindowClose();
}

GLFWManager& GLFWManager::GetRef()
{
	return singleton_;
}

GLFWManager* GLFWManager::GetPtr()
{
	return &singleton_;
}


void GLFWManager::Startup(int32_t width, int32_t height, const char* title, bool bIsWindowCentered)
{
	glfwSetErrorCallback(GLFWError::SetLastError);

	GLFWallocator allocator;
	allocator.allocate = MemoryAlloc;
	allocator.reallocate = MemoryRealloc;
	allocator.deallocate = MemoryFree;

	GLFW_API_CHECK(glfwInitAllocator(&allocator));
	GLFW_EXP_CHECK(glfwInit());

	GLFW_API_CHECK(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_MAJOR_VERSION));
	GLFW_API_CHECK(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_MINOR_VERSION));
	GLFW_API_CHECK(glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE));
	GLFW_API_CHECK(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));

	mainWindowWidth_ = width;
	mainWindowHeight_ = height;

	mainWindow_ = glfwCreateWindow(width, height, title, nullptr, nullptr);
	GLFW_EXP_CHECK(mainWindow_ != nullptr);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;

	glfwSetCursorPosCallback(mainWindow_, GLFWManager::CursorMoveCallback);
	glfwSetCursorEnterCallback(mainWindow_, GLFWManager::CursorEnterCallback);
	glfwSetWindowPosCallback(mainWindow_, GLFWManager::MoveWindowCallback);
	glfwSetWindowFocusCallback(mainWindow_, GLFWManager::FocusWindowCallback);
	glfwSetWindowCloseCallback(mainWindow_, GLFWManager::CloseWindowCallback);

	double x = 0.0;
	double y = 0.0;
	glfwGetCursorPos(mainWindow_, &x, &y);

	float cursorX = -static_cast<float>(mainWindowWidth_) * 0.5f + static_cast<float>(x);
	float cursorY = +static_cast<float>(mainWindowHeight_) * 0.5f - static_cast<float>(y);
	currCursorPos_ = glm::vec2(cursorX, cursorY);
	prevCursorPos_ = currCursorPos_;

	std::fill(prevKeyboardState_.begin(), prevKeyboardState_.end(), 0);
	std::fill(currKeyboardState_.begin(), currKeyboardState_.end(), 0);
	std::fill(prevMouseState_.begin(), prevMouseState_.end(), 0);
	std::fill(currMouseState_.begin(), currMouseState_.end(), 0);

	ASSERT(ImGui_ImplGlfw_InitForOpenGL(mainWindow_, true), "Failed to initialize ImGui for GLFW");

	if (bIsWindowCentered)
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		int32_t monitorX = 0;
		int32_t monitorY = 0;
		glfwGetMonitorPos(monitor, &monitorX, &monitorY);

		int32_t centerX = monitorX + (mode->width - mainWindowWidth_) / 2;
		int32_t centerY = monitorY + (mode->height - mainWindowHeight_) / 2;
		glfwSetWindowPos(mainWindow_, centerX, centerY);
	}
}

void GLFWManager::Shutdown()
{
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	if (mainWindow_)
	{
		glfwDestroyWindow(mainWindow_);
		mainWindow_ = nullptr;
	}

	glfwTerminate();
}

void GLFWManager::Tick()
{
	bIsDetectMoveWindow_ = false;
	prevCursorPos_ = currCursorPos_;

	glfwPollEvents();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	UpdateKeyboardState();
	UpdateMouseState();

	if (bIsStartMoveWindow_ && !bIsDetectMoveWindow_)
	{
		bIsStartMoveWindow_ = false;
		RunWindowEventAction(EWindowEvent::MOVE_LEAVE);
	}
}

void GLFWManager::GetWindowSize(float& outWidth, float& outHeight)
{
	outWidth = static_cast<float>(mainWindowWidth_);
	outHeight = static_cast<float>(mainWindowHeight_);
}

EPress GLFWManager::GetKeyPress(const EKey& key)
{
	EPress press = EPress::NONE;

	if (IsPressKey(prevKeyboardState_.data(), key))
	{
		if (IsPressKey(currKeyboardState_.data(), key))
		{
			press = EPress::HELD;
		}
		else
		{
			press = EPress::RELEASED;
		}
	}
	else
	{
		if (IsPressKey(currKeyboardState_.data(), key))
		{
			press = EPress::PRESSED;
		}
		else
		{
			press = EPress::NONE;
		}
	}

	return press;
}

EPress GLFWManager::GetMousePress(const EMouse& mouse)
{
	EPress press = EPress::NONE;

	if (IsPressButton(prevMouseState_.data(), mouse))
	{
		if (IsPressButton(currMouseState_.data(), mouse))
		{
			press = EPress::HELD;
		}
		else
		{
			press = EPress::RELEASED;
		}
	}
	else
	{
		if (IsPressButton(currMouseState_.data(), mouse))
		{
			press = EPress::PRESSED;
		}
		else
		{
			press = EPress::NONE;
		}
	}

	return press;
}

WindowEventID GLFWManager::AddWindowEventAction(const EWindowEvent& windowEvent, const std::function<void()>& eventAction, bool bIsActive)
{
	CHECK(0 <= windowEventActionSize_ && windowEventActionSize_ < MAX_EVENT_ACTION_SIZE);

	WindowEventID windowEventID = -1;
	for (int32_t index = 0; index < windowEventActionSize_; ++index)
	{
		if (windowEventActions_[index].windowEvent == EWindowEvent::NONE)
		{
			windowEventID = static_cast<WindowEventID>(index);
			break;
		}
	}

	if (windowEventID == -1)
	{
		windowEventID = windowEventActionSize_++;
	}

	windowEventActions_[windowEventID].windowEvent = windowEvent;
	windowEventActions_[windowEventID].windowEventAction = eventAction;
	windowEventActions_[windowEventID].bIsActive = bIsActive;

	return windowEventID;
}

void GLFWManager::DeleteWindowEventAction(const WindowEventID& windowEventID)
{
	CHECK(0 <= windowEventID && windowEventID < MAX_EVENT_ACTION_SIZE);

	windowEventActions_[windowEventID].windowEvent = EWindowEvent::NONE;
	windowEventActions_[windowEventID].windowEventAction = nullptr;
	windowEventActions_[windowEventID].bIsActive = false;
}

void GLFWManager::SetActiveWindowEventAction(const WindowEventID& windowEventID, bool bIsActive)
{
	CHECK(0 <= windowEventID && windowEventID < MAX_EVENT_ACTION_SIZE);
	windowEventActions_[windowEventID].bIsActive = bIsActive;
}

void GLFWManager::SetCursorEnter(int32_t entered)
{
	bIsEnterCursor_ = static_cast<bool>(entered);
}

void GLFWManager::SetCursorPosition(double x, double y)
{
	float cursorX = -static_cast<float>(mainWindowWidth_) * 0.5f + static_cast<float>(x);
	float cursorY = +static_cast<float>(mainWindowHeight_) * 0.5f - static_cast<float>(y);
	currCursorPos_ = glm::vec2(cursorX, cursorY);
}

void GLFWManager::SetWindowMove(int32_t x, int32_t y)
{
	if (bIsStartMoveWindow_)
	{
		bIsDetectMoveWindow_ = true;
		return;
	}

	bIsStartMoveWindow_ = true;
	RunWindowEventAction(EWindowEvent::MOVE_ENTER);
}

void GLFWManager::SetWindowFocus(int32_t focused)
{
	EWindowEvent windowEvent = EWindowEvent::NONE;
	if (focused)
	{
		windowEvent = EWindowEvent::FOCUS_GAIN;
	}
	else
	{
		windowEvent = EWindowEvent::FOCUS_LOST;
	}

	RunWindowEventAction(windowEvent);
}

void GLFWManager::SetWindowClose()
{
	RunWindowEventAction(EWindowEvent::CLOSE_WINDOW);
}

bool GLFWManager::IsPressKey(const int32_t* keyboardState, const EKey& key)
{
	return keyboardState[static_cast<int32_t>(key)];
}

void GLFWManager::UpdateKeyboardState()
{
	std::copy(currKeyboardState_.begin(), currKeyboardState_.end(), prevKeyboardState_.begin());
	std::fill(currKeyboardState_.begin(), currKeyboardState_.end(), 0);

	for (const auto& KEY : KEYS)
	{
		int32_t key = static_cast<int32_t>(KEY);
		currKeyboardState_[key] = glfwGetKey(mainWindow_, key);
	}
}

bool GLFWManager::IsPressButton(const int32_t* mouseState, const EMouse& mouse)
{
	return mouseState[static_cast<int32_t>(mouse)];
}

void GLFWManager::UpdateMouseState()
{
	std::copy(currMouseState_.begin(), currMouseState_.end(), prevMouseState_.begin());
	std::fill(currMouseState_.begin(), currMouseState_.end(), 0);

	static const std::array<EMouse, MOUSE_STATE_SIZE> MOUSE_CODES =
	{
		EMouse::LEFT,
		EMouse::RIGHT,
		EMouse::MIDDLE,
	};

	for (const auto& MOUSE_CODE : MOUSE_CODES)
	{
		int32_t mouse = static_cast<int32_t>(MOUSE_CODE);
		currMouseState_[mouse] = glfwGetMouseButton(mainWindow_, mouse);
	}
}

void GLFWManager::RunWindowEventAction(const EWindowEvent& windowEvent)
{
	for (uint32_t index = 0; index < windowEventActionSize_; ++index)
	{
		WindowEventAction& windowEventAction = windowEventActions_[index];

		if (windowEventAction.windowEvent == windowEvent && windowEventAction.bIsActive && windowEventAction.windowEventAction)
		{
			windowEventAction.windowEventAction();
		}
	}
}