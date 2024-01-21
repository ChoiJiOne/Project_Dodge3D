#include "StartScene.h"

#include "RenderManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "TTFont.h"

StartScene::StartScene()
{
	LoadObjects();
}

StartScene::~StartScene()
{
}

void StartScene::Tick(float deltaSeconds)
{
	mainTitle_->Tick(deltaSeconds);
	startButton_->Tick(deltaSeconds);
	quitButton_->Tick(deltaSeconds);

	RenderManager::Get().SetWindowViewport();
	RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

	mainTitle_->Render();
	startButton_->Render();
	quitButton_->Render();

	RenderManager::Get().EndFrame();
}

void StartScene::LoadObjects()
{
	mainTitle_ = ObjectManager::Get().GetObject<UIMainTitle>("StartScene_MainTitle");
	if (!mainTitle_)
	{
		mainTitle_ = ObjectManager::Get().CreateObject<UIMainTitle>("StartScene_MainTitle");
		mainTitle_->Initialize();
	}

	startButton_ = ObjectManager::Get().GetObject<UIMouseButton>("StartScene_StartButton");
	if (!startButton_)
	{
		startButton_ = ObjectManager::Get().CreateObject<UIMouseButton>("StartScene_StartButton");
		startButton_->Initialize(
			UIMouseButton::UIButtonConstructParam{
				200.0f,
				50.0f,
				Vector2f(500.0f, 400.0f),
				L"Start",
				ResourceManager::Get().GetResource<TTFont>("Font32"),
				Vector4f(0.227f, 0.663f, 1.0f, 0.7f),
				Vector4f(0.227f, 0.663f, 1.0f, 1.0f),
				Vector4f(0.118f, 0.180f, 0.286f, 0.7f),
				Vector4f(0.145f, 0.267f, 0.431f, 0.7f),
				Vector4f(0.224f, 0.486f, 0.804f, 0.7f),
				Vector4f(0.118f, 0.180f, 0.286f, 0.7f),
				UIMouseButton::EType::LButton,
				[&]() {
					OutputDebugStringA("Start\n");
				}
			}
		);
	}

	quitButton_ = ObjectManager::Get().GetObject<UIMouseButton>("StartScene_QuitButton");
	if (!quitButton_)
	{
		quitButton_ = ObjectManager::Get().CreateObject<UIMouseButton>("StartScene_QuitButton");
		quitButton_->Initialize(
			UIMouseButton::UIButtonConstructParam{
				200.0f,
				50.0f,
				Vector2f(500.0f, 500.0f),
				L"Quit",
				ResourceManager::Get().GetResource<TTFont>("Font32"),
				Vector4f(0.227f, 0.663f, 1.0f, 0.7f),
				Vector4f(0.227f, 0.663f, 1.0f, 1.0f),
				Vector4f(0.118f, 0.180f, 0.286f, 0.7f),
				Vector4f(0.145f, 0.267f, 0.431f, 0.7f),
				Vector4f(0.224f, 0.486f, 0.804f, 0.7f),
				Vector4f(0.118f, 0.180f, 0.286f, 0.7f),
				UIMouseButton::EType::LButton,
				[&]() {
					OutputDebugStringA("Quit\n");
				}
			}
		);
	}
}