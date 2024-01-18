#include "GameScene.h"

#include "InputManager.h"
#include "ObjectManager.h"
#include "StringUtils.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Window.h"

#include "BulletSpawner.h"
#include "EastWall.h"
#include "Floor.h"
#include "NorthWall.h"
#include "Player.h"
#include "SouthWall.h"
#include "WestWall.h"

GameScene::GameScene()
{
	LoadResources();
	LoadObjects();
	
	auto gameSceneResizeEvent = [&]() 
	{
		camera_->SetAspectRatio(RenderManager::Get().GetRenderTargetWindow()->GetAspectSize());
	};

	InputManager::Get().AddWindowEventAction("GameSceneResizeEvent",   EWindowEvent::Resize,        gameSceneResizeEvent, true);
	InputManager::Get().AddWindowEventAction("GameSceneExitMinimize",  EWindowEvent::ExitMinimize,  gameSceneResizeEvent, true);
	InputManager::Get().AddWindowEventAction("GameSceneEnterMaximize", EWindowEvent::EnterMaximize, gameSceneResizeEvent, true);
	InputManager::Get().AddWindowEventAction("GameSceneExitMaximize",  EWindowEvent::ExitMaximize,  gameSceneResizeEvent, true);
}

GameScene::~GameScene()
{
}

void GameScene::Tick(float deltaSeconds)
{
	for (auto& object : updateObjects_)
	{
		object->Tick(deltaSeconds);
	}

	camera_->Tick(deltaSeconds);
	light_->Tick(deltaSeconds);

	RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
	RenderManager::Get().SetDepthMode(true);
	RenderDepthScene();
	RenderScene();
	RenderManager::Get().EndFrame();
}

void GameScene::LoadResources()
{
	shadowMap_ = ResourceManager::Get().GetResource<ShadowMap>("ShadowMap");
	if(!shadowMap_)
	{
		shadowMap_ = ResourceManager::Get().CreateResource<ShadowMap>("ShadowMap");
		shadowMap_->Initialize(SHADOW_WIDTH, SHADOW_HEIGHT);
	}

	shadowShader_ = ResourceManager::Get().GetResource<ShadowShader>("ShadowShader");
	lightShader_ = ResourceManager::Get().GetResource<LightShader>("LightShader");
}

void GameScene::LoadObjects()
{
	camera_ = ObjectManager::Get().CreateObject<MovableCamera>("MainCamera");
	camera_->Initialize();

	light_ = ObjectManager::Get().CreateObject<StaticLight>("GlobalLight");
	light_->Initialize();

	player_ = ObjectManager::Get().CreateObject<Player>("Player");
	player_->Initialize();

	floor_ = ObjectManager::Get().CreateObject<Floor>("Floor");
	floor_->Initialize();

	northWall_ = ObjectManager::Get().CreateObject<NorthWall>("NorthWall");
	northWall_->Initialize();

	southWall_ = ObjectManager::Get().CreateObject<SouthWall>("SouthWall");
	southWall_->Initialize();

	westWall_ = ObjectManager::Get().CreateObject<WestWall>("WestWall");
	westWall_->Initialize();

	eastWall_ = ObjectManager::Get().CreateObject<EastWall>("EastWall");
	eastWall_->Initialize();

	bulletSpawner0_ = ObjectManager::Get().CreateObject<BulletSpawner>("BulletSpawner_0");
	bulletSpawner0_->Initialize(Vector3f(-4.0f, 0.5f, +4.0f), 1.0f);

	bulletSpawner1_ = ObjectManager::Get().CreateObject<BulletSpawner>("BulletSpawner_1");
	bulletSpawner1_->Initialize(Vector3f(+4.0f, 0.5f, +4.0f), 2.0f);

	bulletSpawner2_ = ObjectManager::Get().CreateObject<BulletSpawner>("BulletSpawner_2");
	bulletSpawner2_->Initialize(Vector3f(+4.0f, 0.5f, -4.0f), 1.0f);

	bulletSpawner3_ = ObjectManager::Get().CreateObject<BulletSpawner>("BulletSpawner_3");
	bulletSpawner3_->Initialize(Vector3f(-4.0f, 0.5f, -4.0f), 2.0f);

	updateObjects_ = {
		player_,
		bulletSpawner0_,
		bulletSpawner1_,
		bulletSpawner2_,
		bulletSpawner3_,
		floor_,
		northWall_,
		southWall_,
		westWall_,
		eastWall_,
	};

	renderObjects_ = {
		floor_,
		northWall_,
		southWall_,
		westWall_,
		eastWall_,
		bulletSpawner0_,
		bulletSpawner1_,
		bulletSpawner2_,
		bulletSpawner3_,
		player_,
	};
}

void GameScene::RenderDepthScene()
{
	RenderManager::Get().SetViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	shadowMap_->Bind();
	shadowMap_->Clear();

	shadowShader_->Bind();
	shadowShader_->SetLight(light_);

	for (const auto& object : renderObjects_)
	{
		shadowShader_->DrawMesh3D(object->GetTransform().GetWorldMatrix(), object->GetMesh());
	}

	shadowShader_->Unbind();
	shadowMap_->Unbind();
}

void GameScene::RenderScene()
{
	RenderManager::Get().SetWindowViewport();

	lightShader_->Bind();
	lightShader_->SetLight(light_);
	lightShader_->SetCamera(camera_);

	for (const auto& object : renderObjects_)
	{
		lightShader_->SetMaterial(object->GetMaterial());
		lightShader_->DrawMesh3D(object->GetTransform().GetWorldMatrix(), object->GetMesh(), shadowMap_);
	}

	lightShader_->Unbind();

	bulletSpawner0_->RenderRespawnTime(camera_);
	bulletSpawner1_->RenderRespawnTime(camera_);
	bulletSpawner2_->RenderRespawnTime(camera_);
	bulletSpawner3_->RenderRespawnTime(camera_);
}