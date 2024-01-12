#include "IApplication.h"

IApplication::~IApplication()
{
	if (bIsSetup_)
	{
		Shutdown();
	}
}

void IApplication::Setup()
{
	WindowsCrashUtils::RegisterWindowsExceptionFilter();

	CommandLineUtils::Parse();
	ASSERT(CommandLineUtils::GetStringValue(L"rootPath", rootPath_), "failed to get root path from command line...");

	enginePath_ = rootPath_ + L"GameEngine/";

	Window::WindowConstructParam windowParam;
	ASSERT(CommandLineUtils::GetStringValue(L"title", windowParam.title), "failed to get window title from command line...");
	ASSERT(CommandLineUtils::GetIntValue(L"x", windowParam.x), "failed to get window x position from command line...");
	ASSERT(CommandLineUtils::GetIntValue(L"y", windowParam.y), "failed to get window y position from command line...");
	ASSERT(CommandLineUtils::GetIntValue(L"w", windowParam.w), "failed to get window width size from command line...");
	ASSERT(CommandLineUtils::GetIntValue(L"h", windowParam.h), "failed to get window height size from command line...");
	ASSERT(CommandLineUtils::GetBoolValue(L"resize", windowParam.bIsResizable), "failed to get window resize option from command line...");
	ASSERT(CommandLineUtils::GetBoolValue(L"fullscreen", windowParam.bIsFullscreenMode), "failed to get window fullscreen option from command line...");

	Window::RegisterWindowClass(L"ProjectA", InputManager::WindowProc);

	window_ = std::make_unique<Window>();
	window_->Create(windowParam);

	InputManager::Get().SetInputControlWindow(window_.get());
	RenderManager::Get().SetRenderTargetWindow(window_.get());

	InputManager::Get().Startup();
	AudioManager::Get().Startup();
	ResourceManager::Get().Startup();
	RenderManager::Get().Startup();
	ObjectManager::Get().Startup();
	SceneManager::Get().Startup();

	auto defaultLoopDoneEvent = [&]() { bIsDoneLoop_ = true; };
	auto defaultResizeEvent = [&]() { RenderManager::Get().Resize(); };

	InputManager::Get().AddWindowEventAction("DefaultLoopDoneEvent", EWindowEvent::Close,         defaultLoopDoneEvent, true);
	InputManager::Get().AddWindowEventAction("DefaultResizeEvent",   EWindowEvent::Resize,        defaultResizeEvent,   true);
	InputManager::Get().AddWindowEventAction("DefaultExitMinimize",  EWindowEvent::ExitMinimize,  defaultResizeEvent,   true);
	InputManager::Get().AddWindowEventAction("DefaultEnterMaximize", EWindowEvent::EnterMaximize, defaultResizeEvent,   true);
	InputManager::Get().AddWindowEventAction("DefaultExitMaximize",  EWindowEvent::ExitMaximize,  defaultResizeEvent,   true);

	bIsSetup_ = true;
}

void IApplication::Shutdown()
{
	if (bIsSetup_)
	{
		SceneManager::Get().Shutdown();
		ObjectManager::Get().Shutdown();
		ResourceManager::Get().Shutdown();
		RenderManager::Get().Shutdown();
		AudioManager::Get().Shutdown();
		InputManager::Get().Shutdown();

		window_->Destroy();
		window_.reset();

		Window::UnregisterWindowClass();
		WindowsCrashUtils::UnregisterWindowsExceptionFilter();

		bIsSetup_ = false;
	}
}
