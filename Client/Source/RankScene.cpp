#include "RankScene.h"

#include "Assertion.h"
#include "RenderManager.h"
#include "ResourceManager.h"
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
	RenderManager::Get().SetWindowViewport();
	RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

	RenderManager::Get().EndFrame();
}

void RankScene::EnterScene()
{
	bIsEnterScene_ = true;
	bDetectSwitchScene_ = false;
}

void RankScene::ExitScene()
{
	bIsEnterScene_ = false;
}