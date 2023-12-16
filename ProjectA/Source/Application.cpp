#include <cstdint>
#include <string>
#include <windows.h>

#include "Window.h"
#include "WindowsAssertion.h"

Window window;

LRESULT CALLBACK WindowProc(HWND windowHandle, uint32_t message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		break;

	case WM_CLOSE:
		window.Destroy();
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProcW(windowHandle, message, wParam, lParam);
}

int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
	Window::RegisterWindowClass(L"ProjectA", WindowProc);

	window.Create(L"ProjectA", 200, 200, 800, 600, true, true, true);
	ShowWindow(window.GetHandle(), SW_SHOW);

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}
	
	Window::UnregisterWindowClass();
	return 0;
}