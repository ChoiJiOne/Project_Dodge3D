#include "StartScene.h"

#include "RenderManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "TTFont.h"

StartScene::StartScene()
{
	mainTitle_ = ObjectManager::Get().CreateObject<UIMainTitle>("MainTitle");
	mainTitle_->Initialize();

	button_ = ObjectManager::Get().CreateObject<UIButton>("Button");
	button_->Initialize(
		UIButton::UIButtonConstructParam {
			100.0f,
			50.0f,
			Vector2f(500.0f, 400.0f),
			L"Button",
			ResourceManager::Get().GetResource<TTFont>("Font32"),
			Vector4f(1.0f, 1.0f, 1.0f, 1.0f),
			Vector4f(0.5f, 0.5f, 0.5f, 0.5f),
			Vector4f(1.0f, 1.0f, 1.0f, 0.7f),
			Vector4f(1.0f, 1.0f, 1.0f, 0.5f),
			Vector4f(1.0f, 1.0f, 1.0f, 0.7f),
			EVirtualKey::VKEY_LBUTTON,
			[&]() {
				OutputDebugStringA("Click!\n");
			}
		}
	);
}

StartScene::~StartScene()
{
}

void StartScene::Tick(float deltaSeconds)
{
	mainTitle_->Tick(deltaSeconds);
	button_->Tick(deltaSeconds);

	RenderManager::Get().SetWindowViewport();
	RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

	mainTitle_->Render();
	button_->Render();

	RenderManager::Get().EndFrame();
}