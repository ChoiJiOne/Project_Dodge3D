#include "RankScene.h"

#include "Assertion.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Sound.h"
#include "ObjectManager.h"
#include "MathUtils.h"
#include "Window.h"

RankScene::RankScene()
{
}

RankScene::~RankScene()
{
}

void RankScene::Tick(float deltaSeconds)
{
	playLogger_->Tick(deltaSeconds);
	resetButton_->Tick(deltaSeconds);
	quitButton_->Tick(deltaSeconds);

	RenderManager::Get().SetWindowViewport();
	RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

	playLogger_->Render();
	resetButton_->Render();
	quitButton_->Render();

	RenderManager::Get().EndFrame();
}

void RankScene::EnterScene()
{
	LoadResources();
	LoadObjects();

	bIsEnterScene_ = true;
	bDetectSwitchScene_ = false;
}

void RankScene::ExitScene()
{
	bIsEnterScene_ = false;
}

void RankScene::LoadResources()
{
	font32_ = ResourceManager::Get().GetResource<TTFont>("Font32");
	buttonClick_ = ResourceManager::Get().GetResource<Sound>("ButtonClick");
}

void RankScene::LoadObjects()
{
	int32_t windowWidth;
	int32_t windowHeight;
	RenderManager::Get().GetRenderTargetWindow()->GetSize(windowWidth, windowHeight);
	Vector2f windowCenter(static_cast<float>(windowWidth) / 2.0f, static_cast<float>(windowHeight) / 2.0f);

	resetButton_ = ObjectManager::Get().GetObject<UIMouseButton>("RankScene_ResetButton");
	if (!resetButton_)
	{
		resetButton_ = ObjectManager::Get().CreateObject<UIMouseButton>("RankScene_ResetButton");
		resetButton_->Initialize(
			UIMouseButton::UIButtonConstructParam{
				200.0f,
				50.0f,
				windowCenter + Vector2f(0.0f, 100.0f),
				L"Reset",
				font32_,
				Vector4f(0.227f, 0.663f,   1.0f, 0.7f),
				Vector4f(0.227f, 0.663f,   1.0f, 1.0f),
				Vector4f(0.118f, 0.180f, 0.286f, 0.7f),
				Vector4f(0.145f, 0.267f, 0.431f, 0.7f),
				Vector4f(0.224f, 0.486f, 0.804f, 0.7f),
				Vector4f(0.118f, 0.180f, 0.286f, 0.7f),
				UIMouseButton::EType::LButton,
				[&]() {
					buttonClick_->Play();
					bDetectSwitchScene_ = true;
				}
			}
		);
	}

	quitButton_ = ObjectManager::Get().GetObject<UIMouseButton>("RankScene_QuitButton");
	if (!quitButton_)
	{
		quitButton_ = ObjectManager::Get().CreateObject<UIMouseButton>("RankScene_QuitButton");
		quitButton_->Initialize(
			UIMouseButton::UIButtonConstructParam{
				200.0f,
				50.0f,
				windowCenter + Vector2f(0.0f, 200.0f),
				L"Quit",
				font32_,
				Vector4f(0.227f, 0.663f,   1.0f, 0.7f),
				Vector4f(0.227f, 0.663f,   1.0f, 1.0f),
				Vector4f(0.118f, 0.180f, 0.286f, 0.7f),
				Vector4f(0.145f, 0.267f, 0.431f, 0.7f),
				Vector4f(0.224f, 0.486f, 0.804f, 0.7f),
				Vector4f(0.118f, 0.180f, 0.286f, 0.7f),
				UIMouseButton::EType::LButton,
				loopQuitEvent_
			}
		);
	}

	playLogger_ = ObjectManager::Get().GetObject<PlayLogger>("PlayerLogger");
}