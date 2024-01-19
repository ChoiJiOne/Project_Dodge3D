#include "StartScene.h"

#include "RenderManager.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

void StartScene::Tick(float deltaSeconds)
{
	RenderManager::Get().SetWindowViewport();
	RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

	RenderManager::Get().EndFrame();
}