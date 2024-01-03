#include "ClientApplication.h"

ClientApplication::~ClientApplication()
{
	Shutdown();
}

void ClientApplication::Setup()
{
	IGameFramework::Setup();

	clientPath_ = rootPath_ + L"Client/";

	auto clientResizeEvent = [&]() {
		int32_t width;
		int32_t height;
		window_->GetSize(width, height);
		glViewport(0, 0, width, height);
	};
	InputManager::Get().AddWindowEventAction("ClientResizeEvent",   EWindowEvent::Resize,        clientResizeEvent, true);
	InputManager::Get().AddWindowEventAction("ClientExitMinimize",  EWindowEvent::ExitMinimize,  clientResizeEvent, true);
	InputManager::Get().AddWindowEventAction("ClientEnterMaximize", EWindowEvent::EnterMaximize, clientResizeEvent, true);
	InputManager::Get().AddWindowEventAction("ClientExitMaximize",  EWindowEvent::ExitMaximize,  clientResizeEvent, true);
}

void ClientApplication::Shutdown()
{
}

void ClientApplication::Run()
{
	Skybox* skybox = ResourceManager::Get().CreateResource<Skybox>("SkyboxResource");
	skybox->Initialize(
		clientPath_ + L"Resource/Right.png",
		clientPath_ + L"Resource/Left.png",
		clientPath_ + L"Resource/Top.png",
		clientPath_ + L"Resource/Bottom.png",
		clientPath_ + L"Resource/Front.png",
		clientPath_ + L"Resource/Back.png"
	);

	timer_.Reset();
	while (!bIsDoneLoop_)
	{
		timer_.Tick();
		InputManager::Get().Tick();

		int32_t width;
		int32_t height;
		window_->GetSize(width, height);

		Matrix4x4f view = MathUtils::CreateLookAt(Vector3f(2.0f, 2.0f, 2.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
		Matrix4x4f projection = MathUtils::CreatePerspective(MathUtils::ToRadian(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.01f, 1000.0f);

		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
		RenderManager::Get().RenderSkybox3D(view, projection, skybox);
		RenderManager::Get().RenderGrid3D(view, projection, -10.0f, 10.0f, 1.0f, -10.0f, 10.0f, 1.0f, Vector4f(0.0f, 0.0f, 0.0f, 0.5f));
		RenderManager::Get().EndFrame();
	}
}