#include "BulletSpawner.h"

#include "Assertion.h"
#include "Camera3D.h"
#include "GeometryGenerator.h"
#include "MathUtils.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "StringUtils.h"

BulletSpawner::~BulletSpawner()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void BulletSpawner::Initialize(const Vector3f& location, float respawnTime, const std::function<void()>& respawnTrigger)
{
	ASSERT(!bIsInitialized_, "already initialize bullet spawner object...");

	mesh_ = ResourceManager::Get().GetResource<StaticMesh>("BulletSpawnerMesh");
	if (!mesh_)
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		GeometryGenerator::CreateCylinder(0.25f, 1.0f, 40, vertices, indices);

		mesh_ = ResourceManager::Get().CreateResource<StaticMesh>("BulletSpawnerMesh");
		mesh_->Initialize(vertices, indices);
	}

	material_ = ResourceManager::Get().GetResource<Material>("BulletSpawnerMaterial");
	if (!material_)
	{
		material_ = ResourceManager::Get().CreateResource<Material>("BulletSpawnerMaterial");
		material_->Initialize(
			Vector3f(0.1745f, 0.01175f, 0.01175f),
			Vector3f(0.61424f, 0.04136f, 0.04136f),
			Vector3f(0.727811f, 0.626959f, 0.626959f),
			0.6f * 128.0f
		);
	}
	
	transform_ = Transform(location, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));

	stepTime_ = 0.0f;
	respawnTime_ = respawnTime;
	width_ = 1.0f;
	height_ = 0.2f;
	mainColor_ = Vector4f(1.0f, 0.0f, 0.0f, 1.0f);
	subColor_ = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
	respawnTrigger_ = respawnTrigger;

	bIsInitialized_ = true;
}

void BulletSpawner::Tick(float deltaSeconds)
{
	stepTime_ += deltaSeconds;

	if (stepTime_ >= respawnTime_)
	{
		stepTime_ -= respawnTime_;
		respawnTrigger_();
	}
}

void BulletSpawner::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	bIsInitialized_ = false;
}

void BulletSpawner::RenderRespawnTime(const Camera3D* camera)
{
	Matrix4x4f world = transform_.GetWorldMatrix() * MathUtils::CreateTranslation(Vector3f(0.0f, 1.0f, 0.0f));
	float rate = stepTime_ / respawnTime_;

	RenderManager::Get().RenderHorizonDividQuad3D(world, camera, width_, height_, rate, mainColor_, subColor_);
}