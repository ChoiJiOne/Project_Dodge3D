#include "InputManager.h"

#include "Assertion.h"
#include "CommandLineUtils.h"
#include "Window.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_win32.h>
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

InputManager* inputManagerPtr = nullptr;

void InputManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup input manager...");
	ASSERT(inputControlWindow_ != nullptr, "haven't set the input control window...");
	ASSERT(!inputManagerPtr, "already setup input manager pointer...");

	std::fill(prevKeyboardState_.begin(), prevKeyboardState_.end(), 0);
	std::fill(currKeyboardState_.begin(), currKeyboardState_.end(), 0);

	windowEventActions_ = std::unordered_map<std::string, WindowEventAction>();

	if (bIsEnableImGui_)
	{
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = nullptr; // 현재 사용하지 않음.
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
	}

	inputManagerPtr = this;
	bIsStartup_ = true;
}

void InputManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

	if (bIsEnableImGui_)
	{
		ImGui::DestroyContext();
	}

	inputManagerPtr = nullptr;
	inputControlWindow_ = nullptr;
	bIsStartup_ = false;
}

void InputManager::Tick()
{
	PollWindowEvents();
	
	std::copy(currKeyboardState_.begin(), currKeyboardState_.end(), prevKeyboardState_.begin());
	WINDOWS_ASSERT(GetKeyboardState(currKeyboardState_.data()), "failed to get current keyboard state...");

	prevCursorPosition_ = currCursorPosition_;
	currCursorPosition_ = GetCurrentCursorPosition();

	if (bIsEnableImGui_)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}
}

EPressState InputManager::GetVirtualKeyPressState(const EVirtualKey& virtualKey)
{
	EPressState pressState = EPressState::None;

	if (IsPressKey(prevKeyboardState_.data(), virtualKey))
	{
		if (IsPressKey(currKeyboardState_.data(), virtualKey))
		{
			pressState = EPressState::Held;
		}
		else
		{
			pressState = EPressState::Released;
		}
	}
	else
	{
		if (IsPressKey(currKeyboardState_.data(), virtualKey))
		{
			pressState = EPressState::Pressed;
		}
		else
		{
			pressState = EPressState::None;
		}
	}

	return pressState;
}

void InputManager::AddWindowEventAction(const std::string& signature, const EWindowEvent& windowEvent, const std::function<void()>& eventAction, bool bIsActive)
{
	ASSERT(windowEventActions_.find(signature) == windowEventActions_.end(), "already bind window event action : %s", signature.c_str());

	WindowEventAction windowEventAction{ bIsActive, windowEvent, eventAction };
	windowEventActions_.insert({ signature, windowEventAction });
}

void InputManager::DeleteWindowEventAction(const std::string& signature)
{
	if (windowEventActions_.find(signature) != windowEventActions_.end())
	{
		windowEventActions_.erase(signature);
	}
}

void InputManager::SetActiveWindowEventAction(const std::string& signature, bool bIsActive)
{
	if (windowEventActions_.find(signature) != windowEventActions_.end())
	{
		windowEventActions_.at(signature).bIsActive = bIsActive;
	}
}

void InputManager::ExecuteWindowEventAction(const EWindowEvent& windowEvent)
{
	for (auto& windowEventAction : windowEventActions_)
	{
		WindowEventAction& executeWindowEvent = windowEventAction.second;

		if (executeWindowEvent.windowEvent == windowEvent && executeWindowEvent.bIsActive)
		{
			executeWindowEvent.windowEventAction();
		}
	}
}

LRESULT InputManager::ProcessWindowMessage(HWND windowHandle, uint32_t message, WPARAM wParam, LPARAM lParam)
{
	if (bIsEnableImGui_ && ImGui_ImplWin32_WndProcHandler(windowHandle, message, wParam, lParam))
	{
		return 1;
	}

	EWindowEvent windowEvent = EWindowEvent::None;

	switch (message)
	{
	case WM_ACTIVATE:
		windowEvent = (LOWORD(wParam) == WA_INACTIVE) ? EWindowEvent::Inactive : EWindowEvent::Active;
		break;

	case WM_CLOSE:
		windowEvent = EWindowEvent::Close;
		break;

	case WM_MOVE:
		windowEvent = EWindowEvent::Move;
		break;

	case WM_SIZE:
		switch (wParam)
		{
		case SIZE_RESTORED:
			if (bIsMinimize_)
			{
				windowEvent = EWindowEvent::ExitMinimize;
			}
			else if (bIsMaximize_)
			{
				windowEvent = EWindowEvent::ExitMaximize;
			}
			else
			{
				windowEvent = EWindowEvent::Resize;
			}
			
			bIsMinimize_ = false;
			bIsMaximize_ = false;
			break;
		
		case SIZE_MINIMIZED:
			bIsMinimize_ = true;
			bIsMaximize_ = false;
			windowEvent = EWindowEvent::EnterMinimize;
			break;

		case SIZE_MAXIMIZED:
			bIsMinimize_ = false;
			bIsMaximize_ = true;
			windowEvent = EWindowEvent::EnterMaximize;
			break;

		default:
			windowEvent = EWindowEvent::None;
			break;
		}
		break;

	case WM_ENTERSIZEMOVE:
		windowEvent = EWindowEvent::EnterResize;
		break;

	case WM_EXITSIZEMOVE:
		windowEvent = EWindowEvent::ExitResize;
		break;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProcW(windowHandle, message, wParam, lParam);
	}

	ExecuteWindowEventAction(windowEvent);
	return 0;
}

LRESULT InputManager::WindowProc(HWND windowHandle, uint32_t message, WPARAM wParam, LPARAM lParam)
{
	if (inputManagerPtr)
	{
		return inputManagerPtr->ProcessWindowMessage(windowHandle, message, wParam, lParam);
	}

	return DefWindowProcW(windowHandle, message, wParam, lParam);
}

void InputManager::PollWindowEvents()
{
	MSG msg = {};
	while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

bool InputManager::IsPressKey(const uint8_t* keyBufferPtr, const EVirtualKey& virtualKey) const
{
	return (keyBufferPtr[static_cast<int32_t>(virtualKey)] & 0x80);
}

Vector2i InputManager::GetCurrentCursorPosition()
{
	POINT cursorPos;

	WINDOWS_ASSERT(GetCursorPos(&cursorPos), "failed to get cursor position...");
	WINDOWS_ASSERT(ScreenToClient(inputControlWindow_->GetHandle(), &cursorPos), "failed to convert screen to client cursor position...");

	return Vector2i(static_cast<int32_t>(cursorPos.x), static_cast<int32_t>(cursorPos.y));
}