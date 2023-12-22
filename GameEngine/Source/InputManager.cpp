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

LRESULT InputManager::ProcessWindowMessage(HWND windowHandle, uint32_t message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProcW(windowHandle, message, wParam, lParam);
	}

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