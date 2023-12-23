#include "InputManager.h"

#include "Assertion.h"
#include "Window.h"
#include "WindowsAssertion.h"

InputManager* inputManagerPtr = nullptr;

void InputManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup input manager...");
	ASSERT(inputControlWindow_ != nullptr, "haven't set the input control window...");
	ASSERT(!inputManagerPtr, "already setup input manager pointer...");

	windowEventActions_ = std::unordered_map<std::string, WindowEventAction>();

	inputManagerPtr = this;
	bIsStartup_ = true;
}

void InputManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

	inputManagerPtr = nullptr;
	inputControlWindow_ = nullptr;
	bIsStartup_ = false;
}

void InputManager::Tick()
{
	PollWindowEvents();
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
			windowEvent = EWindowEvent::Resize;
			break;
		
		case SIZE_MINIMIZED:
			windowEvent = EWindowEvent::Minimize;
			break;

		case SIZE_MAXIMIZED:
			windowEvent = EWindowEvent::Maximize;
			break;

		default:
			windowEvent = EWindowEvent::None;
			break;
		}
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