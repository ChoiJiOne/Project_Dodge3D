#include "StartScene.h"

#include "RenderManager.h"
#include "ObjectManager.h"

StartScene::StartScene()
{
	mainTitle_ = ObjectManager::Get().CreateObject<UIMainTitle>("MainTitle");
	mainTitle_->Initialize();
}

StartScene::~StartScene()
{
}

void StartScene::Tick(float deltaSeconds)
{
	mainTitle_->Tick(deltaSeconds);

	RenderManager::Get().SetWindowViewport();
	RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

	mainTitle_->Render();

	RenderManager::Get().EndFrame();
}