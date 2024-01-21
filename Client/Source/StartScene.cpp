#include "StartScene.h"

#include "RenderManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "TTFont.h"

StartScene::StartScene()
{
	mainTitle_ = ObjectManager::Get().CreateObject<UIMainTitle>("MainTitle");
	mainTitle_->Initialize();

	button0_ = ObjectManager::Get().CreateObject<UIButton>("Button0");
	button0_->Initialize(
		UIButton::UIButtonConstructParam {
			200.0f,
			50.0f,
			Vector2f(500.0f, 400.0f),
			L"Button0",
			ResourceManager::Get().GetResource<TTFont>("Font32"),
			Vector4f(1.0f, 1.0f, 1.0f, 1.0f), // outline
			Vector4f(1.0f, 1.0f, 1.0f, 1.0f), // text
			Vector4f(1.0f, 0.0f, 0.0f, 1.0f), // disable
			Vector4f(0.0f, 1.0f, 0.0f, 1.0f), // enable
			Vector4f(0.0f, 0.0f, 1.0f, 1.0f), // press
			Vector4f(1.0f, 1.0f, 1.0f, 0.7f), // release
			EVirtualKey::VKEY_LBUTTON,
			[&]() {
				OutputDebugStringA("Button0_Click!\n");
			}
		}
	);

	button1_ = ObjectManager::Get().CreateObject<UIButton>("Button1");
	button1_->Initialize(
		UIButton::UIButtonConstructParam{
			200.0f,
			50.0f,
			Vector2f(500.0f, 500.0f),
			L"Button1",
			ResourceManager::Get().GetResource<TTFont>("Font32"),
			Vector4f(1.0f, 1.0f, 1.0f, 1.0f), // outline
			Vector4f(1.0f, 1.0f, 1.0f, 1.0f), // text
			Vector4f(1.0f, 0.0f, 0.0f, 1.0f), // disable
			Vector4f(0.0f, 1.0f, 0.0f, 1.0f), // enable
			Vector4f(0.0f, 0.0f, 1.0f, 1.0f), // press
			Vector4f(1.0f, 1.0f, 1.0f, 0.7f), // release
			EVirtualKey::VKEY_LBUTTON,
			[&]() {
				OutputDebugStringA("Button1_Click!\n");
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
	button0_->Tick(deltaSeconds);
	button1_->Tick(deltaSeconds);

	RenderManager::Get().SetWindowViewport();
	RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

	mainTitle_->Render();
	button0_->Render();
	button1_->Render();

	RenderManager::Get().EndFrame();
}