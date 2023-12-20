#include <cstdint>
#include <string>
#include <windows.h>

#include "RenderManager.h"
#include "Window.h"

Window window;

LRESULT CALLBACK WindowProc(HWND windowHandle, uint32_t message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		break;

	case WM_CLOSE:
		RenderManager::Get().Shutdown();
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

	window.Create(L"ProjectA", 200, 200, 800, 600, true, false);
	RenderManager::Get().SetRenderTargetWindow(&window);

	RenderManager::Get().Startup();

	while (true)
	{
		MSG msg = {};
		while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			break;
		}

		RenderManager::Get().BeginFrame(1.0f, 0.0f, 0.0f, 1.0f);
		RenderManager::Get().EndFrame();
	}

	Window::UnregisterWindowClass();
	return 0;
}