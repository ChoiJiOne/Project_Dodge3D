#include "Window.h"

#include "WindowsAssertion.h"

bool Window::bIsRegisterWindowClass_ = false;
HINSTANCE Window::hInstance_ = nullptr;
std::wstring Window::windowClassName_;

Window::~Window()
{
}

void Window::RegisterWindowClass(const std::wstring& windowClassName, WINDOWPROC windowProc)
{
	ASSERT(!bIsRegisterWindowClass_, "already register window class...");
	ASSERT(windowProc != nullptr, "Window procedure is nullptr...");

	hInstance_ = GetModuleHandleW(nullptr);
	windowClassName_ = windowClassName;

	WNDCLASSEXW wcexw = {};
	wcexw.cbSize = sizeof(WNDCLASSEXW);
	wcexw.style = CS_HREDRAW | CS_VREDRAW;
	wcexw.lpfnWndProc = windowProc;
	wcexw.cbClsExtra = 0;
	wcexw.cbWndExtra = 0;
	wcexw.hInstance = hInstance_;
	wcexw.hIcon = LoadIcon(hInstance_, IDI_APPLICATION);
	wcexw.hIconSm = LoadIcon(hInstance_, IDI_APPLICATION);
	wcexw.hCursor = LoadCursor(hInstance_, IDC_ARROW);
	wcexw.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcexw.lpszMenuName = nullptr;
	wcexw.lpszClassName = windowClassName_.c_str();

	WINDOWS_ASSERT(RegisterClassExW(&wcexw) != 0, "failed to register window class...");
	bIsRegisterWindowClass_ = true;
}

void Window::UnregisterWindowClass()
{
	ASSERT(bIsRegisterWindowClass_, "haven't registered before or have already unregistered...");

	UnregisterClassW(windowClassName_.c_str(), hInstance_);

	hInstance_ = nullptr;
	bIsRegisterWindowClass_ = false;
}