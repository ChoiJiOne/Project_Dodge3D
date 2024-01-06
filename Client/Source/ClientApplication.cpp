#include "ClientApplication.h"

ClientApplication::~ClientApplication()
{
	Shutdown();
}

void ClientApplication::Setup()
{
	IGameFramework::Setup();
	clientPath_ = rootPath_ + L"Client/";
}

void ClientApplication::Shutdown()
{
}

void ClientApplication::Run()
{
	int32_t windowWidth;
	int32_t windowHeight;
	window_->GetSize(windowWidth, windowHeight);

	auto clientResizeEvent = [&]() {
		window_->GetSize(windowWidth, windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);
	};
	InputManager::Get().AddWindowEventAction("ClientResizeEvent",   EWindowEvent::Resize,        clientResizeEvent, true);
	InputManager::Get().AddWindowEventAction("ClientExitMinimize",  EWindowEvent::ExitMinimize,  clientResizeEvent, true);
	InputManager::Get().AddWindowEventAction("ClientEnterMaximize", EWindowEvent::EnterMaximize, clientResizeEvent, true);
	InputManager::Get().AddWindowEventAction("ClientExitMaximize",  EWindowEvent::ExitMaximize,  clientResizeEvent, true);

	timer_.Reset();
	while (!bIsDoneLoop_)
	{
		timer_.Tick();
		InputManager::Get().Tick();
		
		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
		{ // ∑ª¥ı∏µ Ω√¿€...
		}
		RenderManager::Get().EndFrame();
	}
}