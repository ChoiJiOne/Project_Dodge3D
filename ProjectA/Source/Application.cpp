#include <cstdint>
#include <windows.h>

HINSTANCE GInstance = nullptr;
HWND GWindowHandle = nullptr;

LRESULT CALLBACK WindowProc(HWND windowHandle, uint32_t message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		DestroyWindow(windowHandle);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProcW(windowHandle, message, wParam, lParam);
}

int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
	GInstance = hInstance;

	WNDCLASSEXW wcexw = {};
	wcexw.cbSize = sizeof(WNDCLASSEXW);
	wcexw.style = CS_HREDRAW | CS_VREDRAW;
	wcexw.lpfnWndProc = WindowProc;
	wcexw.cbClsExtra = 0;
	wcexw.cbWndExtra = 0;
	wcexw.hInstance = GInstance;
	wcexw.hIcon = LoadIcon(GInstance, IDI_APPLICATION);
	wcexw.hIconSm = LoadIcon(GInstance, IDI_APPLICATION);
	wcexw.hCursor = LoadCursor(GInstance, IDC_ARROW);
	wcexw.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcexw.lpszMenuName = nullptr;
	wcexw.lpszClassName = L"ProjectA";

	if (!RegisterClassExW(&wcexw))
	{
		return -1;
	}

	RECT windowRect = {0, 0, 800, 600};
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	GWindowHandle = CreateWindowExW(
		0,
		L"ProjectA",
		L"ProjectA",
		WS_OVERLAPPEDWINDOW, // WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX 크기 변경 불가
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr,
		nullptr,
		GInstance,
		nullptr
	);

	if (!GWindowHandle)
	{
		return -1;
	}

	ShowWindow(GWindowHandle, SW_SHOW);

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}

	BOOL check = UnregisterClassW(L"ProjectA", GInstance);
	
	return 0;
}