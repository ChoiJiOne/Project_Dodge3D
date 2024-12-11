#include "IApplication.h"

IApplication::IApplication()
{
	if (!bIsSetup_)
	{
		WindowsCrashUtils::RegisterWindowsExceptionFilter();
	}
}

IApplication::~IApplication()
{
	if (bIsSetup_)
	{
		Shutdown();
	}
}

void IApplication::Setup()
{
#if	defined(MIN_SIZE_REL_MODE)
	if (bIsSetup_)
	{
		MessageBoxW(nullptr, L"Already setup application...", L"Error", MB_OK);
		return;
	}

	if (!bIsPropertiesSet_)
	{
		MessageBoxW(nullptr, L"Failed to set application properties...", L"Error", MB_OK);
		return;
	}
#else
	ASSERT(!bIsSetup_, "already setup application...");
	ASSERT(bIsPropertiesSet_, "Failed to set application properties...");
#endif

	Window::RegisterWindowClass(windowTitle_, InputManager::WindowProc);

	window_ = std::make_unique<Window>();
	window_->Create(Window::WindowConstructParam{ 
		windowTitle_, windowPosition_.x, windowPosition_.y, windowWidth_, windowHeight_,
		bIsResize_, bIsFullscreen_
	});

	InputManager::Get().SetInputControlWindow(window_.get());
	InputManager::Get().SetEnableImGui(bIsImGui_);

	RenderManager::Get().SetRenderTargetWindow(window_.get());
	RenderManager::Get().SetEnableImGui(bIsImGui_);
	RenderManager::Get().SetShaderPath(L"Shader/");

	InputManager::Get().Startup();
	AudioManager::Get().Startup();
	ResourceManager::Get().Startup();
	RenderManager::Get().Startup();
	ObjectManager::Get().Startup();
	SceneManager::Get().Startup();

	auto defaultLoopDoneEvent = [&]() 
	{ 
		bIsDoneLoop_ = true; 
	};

	auto defaultResizeEvent = [&]() 
	{ 
		window_->GetSize(windowWidth_, windowHeight_);
		RenderManager::Get().Resize(); 
	};

	auto defaultMoveEvent = [&]() 
	{
		window_->GetPosition(windowPosition_.x, windowPosition_.y);
	};

	InputManager::Get().AddWindowEventAction("DefaultLoopDoneEvent", EWindowEvent::Close,         defaultLoopDoneEvent, true);
	InputManager::Get().AddWindowEventAction("DefaultMoveEvent",     EWindowEvent::Move,          defaultMoveEvent,     true);
	InputManager::Get().AddWindowEventAction("DefaultResizeEvent",   EWindowEvent::Resize,        defaultResizeEvent,   true);
	InputManager::Get().AddWindowEventAction("DefaultExitMinimize",  EWindowEvent::ExitMinimize,  defaultResizeEvent,   true);
	InputManager::Get().AddWindowEventAction("DefaultEnterMaximize", EWindowEvent::EnterMaximize, defaultResizeEvent,   true);
	InputManager::Get().AddWindowEventAction("DefaultExitMaximize",  EWindowEvent::ExitMaximize,  defaultResizeEvent,   true);
	
	RenderManager::Get().SetVsyncMode(bIsVsync_);

	bIsSetup_ = true;
}

void IApplication::Shutdown()
{
	if (bIsSetup_ && bIsPropertiesSet_)
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
		bIsPropertiesSet_ = false;
	}
}

void IApplication::SetProperties(const std::wstring& windowTitle, int32_t windowPosX, int32_t windowPosY, int32_t windowWidth, int32_t windowHeight, bool bIsResize, bool bIsFullscreen, bool bIsVsync, bool bIsImGui)
{
	windowTitle_ = windowTitle;
	windowPosition_ = Vector2i(windowPosX, windowPosY);
	windowWidth_ = windowWidth;
	windowHeight_ = windowHeight;
	bIsResize_ = bIsResize;
	bIsFullscreen_ = bIsFullscreen;
	bIsVsync_ = bIsVsync;
	bIsImGui_ = bIsImGui;
	
	bIsPropertiesSet_ = true;
}