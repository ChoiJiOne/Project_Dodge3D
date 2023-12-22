#include "InputManager.h"

#include "Assertion.h"
#include "Window.h"
#include "WindowsAssertion.h"

void InputManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup input manager...");
	ASSERT(inputControlWindow_ != nullptr, "haven't set the input control window...");

	bIsStartup_ = true;
}

void InputManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

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
