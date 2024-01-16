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
	camera_ = ObjectManager::Get().CreateObject<MovableCamera>("MainCamera");
	camera_->Initialize();

	light_ = ObjectManager::Get().CreateObject<StaticLight>("GlobalLight");
	light_->Initialize();

	Player* player = ObjectManager::Get().CreateObject<Player>("Player");
	player->Initialize();
	updateObjects_.push_back(player);
	renderObjects_.push_back(player);

	Floor* floor = ObjectManager::Get().CreateObject<Floor>("Floor");
	floor->Initialize();
	updateObjects_.push_back(floor);
	renderObjects_.push_back(floor);
	
	NorthWall* northWall = ObjectManager::Get().CreateObject<NorthWall>("NorthWall");
	northWall->Initialize();
	updateObjects_.push_back(northWall);
	renderObjects_.push_back(northWall);

	SouthWall* southWall = ObjectManager::Get().CreateObject<SouthWall>("SouthWall");
	southWall->Initialize();
	updateObjects_.push_back(southWall);
	renderObjects_.push_back(southWall);

	WestWall* westWall = ObjectManager::Get().CreateObject<WestWall>("WestWall");
	westWall->Initialize();
	updateObjects_.push_back(westWall);
	renderObjects_.push_back(westWall);

	EastWall* eastWall = ObjectManager::Get().CreateObject<EastWall>("EastWall");
	eastWall->Initialize();
	updateObjects_.push_back(eastWall);
	renderObjects_.push_back(eastWall);
	
	BulletSpawner* bulletSpawner0 = ObjectManager::Get().CreateObject<BulletSpawner>(StringUtils::PrintF("BulletSpawner_%d", BulletSpawner::GetCountOfBulletSpawner()));
	bulletSpawner0->Initialize(Vector3f(-4.0f, 0.5f, +4.0f));
	updateObjects_.push_back(bulletSpawner0);
	renderObjects_.push_back(bulletSpawner0);

	BulletSpawner* bulletSpawner1 = ObjectManager::Get().CreateObject<BulletSpawner>(StringUtils::PrintF("BulletSpawner_%d", BulletSpawner::GetCountOfBulletSpawner()));
	bulletSpawner1->Initialize(Vector3f(+4.0f, 0.5f, +4.0f));
	updateObjects_.push_back(bulletSpawner1);
	renderObjects_.push_back(bulletSpawner1);

	BulletSpawner* bulletSpawner2 = ObjectManager::Get().CreateObject<BulletSpawner>(StringUtils::PrintF("BulletSpawner_%d", BulletSpawner::GetCountOfBulletSpawner()));
	bulletSpawner2->Initialize(Vector3f(+4.0f, 0.5f, -4.0f));
	updateObjects_.push_back(bulletSpawner2);
	renderObjects_.push_back(bulletSpawner2);

	BulletSpawner* bulletSpawner3 = ObjectManager::Get().CreateObject<BulletSpawner>(StringUtils::PrintF("BulletSpawner_%d", BulletSpawner::GetCountOfBulletSpawner()));
	bulletSpawner3->Initialize(Vector3f(-4.0f, 0.5f, -4.0f));
	updateObjects_.push_back(bulletSpawner3);
	renderObjects_.push_back(bulletSpawner3);

	shadowMap_ = ResourceManager::Get().CreateResource<ShadowMap>("shadowMap");
	shadowMap_->Initialize(SHADOW_WIDTH, SHADOW_HEIGHT);

	shadowShader_ = ResourceManager::Get().GetResource<ShadowShader>("ShadowShader");
	lightShader_ = ResourceManager::Get().GetResource<LightShader>("LightShader");

	auto gameSceneResizeEvent = [&]() {
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
	{ // ±íÀÌ °ª ·»´õ¸µ
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
	{ // ¶óÀÌÆ® È¿°ú ·»´õ¸µ
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
	}
	RenderManager::Get().EndFrame();
}
