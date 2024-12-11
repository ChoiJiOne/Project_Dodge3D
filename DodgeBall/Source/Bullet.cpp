#include "Bullet.h"
#include "EastWall.h"
#include "NorthWall.h"
#include "Player.h"
#include "SouthWall.h"
#include "WestWall.h"

#include "Assertion.h"
#include "GeometryGenerator.h"
#include "MathUtils.h"
#include "ObjectManager.h"
#include "ResourceManager.h"
#include "Sound.h"

Bullet::~Bullet()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Bullet::Initialize(const Vector3f& location, const Vector3f& direction, float speed, float boundRadius)
{
	ASSERT(!bIsInitialized_, "already initialize bullet object...");

	mesh_ = ResourceManager::Get().GetResource<StaticMesh>("BulletMesh");
	if (!mesh_)
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		GeometryGenerator::CreateSphere(1.0f, 40, vertices, indices);

		mesh_ = ResourceManager::Get().CreateResource<StaticMesh>("BulletMesh");
		mesh_->Initialize(vertices, indices);
	}

	material_ = ResourceManager::Get().GetResource<Material>("BulletMaterial");
	if (!material_)
	{
		material_ = ResourceManager::Get().CreateResource<Material>("BulletMaterial");
		material_->Initialize(
			Vector3f(0.19225f, 0.19225f, 0.19225f),
			Vector3f(0.50754f, 0.50754f, 0.50754f),
			Vector3f(0.508273f, 0.508273f, 0.508273f),
			0.4f * 128.0f
		);
	}

	hitSound_ = ResourceManager::Get().GetResource<Sound>("Hit");

	transform_ = Transform(location, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(boundRadius, boundRadius, boundRadius));
	
	direction_ = direction;
	speed_ = speed;
	boundingVolume_ = Sphere3D(transform_.GetLocation(), boundRadius);

	bIsInitialized_ = true;
}

void Bullet::Tick(float deltaSeconds)
{
	if (bIsCollisionToWall_ || bIsCollisionToPlayer_)
	{
		return;
	}

	Vector3f location = transform_.GetLocation();

	location.x += deltaSeconds * direction_.x * speed_;
	location.z += deltaSeconds * direction_.z * speed_;

	transform_.SetLocation(location);
	boundingVolume_.SetCenter(location);

	bIsCollisionToWall_ = CheckCollisionToWall();
	bIsCollisionToPlayer_ = CheckCollisionToPlayer();

	if (bIsCollisionToPlayer_)
	{
		Player* player = ObjectManager::Get().GetObject<Player>("Player");
		int32_t hp = player->GetHP();
		player->SetHP(--hp);

		hitSound_->Reset();
		hitSound_->Play();
	}
}

void Bullet::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	bIsInitialized_ = false;
}

bool Bullet::CheckCollisionToWall()
{
	NorthWall* northWall = ObjectManager::Get().GetObject<NorthWall>("NorthWall");
	SouthWall* southWall = ObjectManager::Get().GetObject<SouthWall>("SouthWall");
	WestWall* westWall = ObjectManager::Get().GetObject<WestWall>("WestWall");
	EastWall* eastWall = ObjectManager::Get().GetObject<EastWall>("EastWall");

	return IsCollision(northWall) || IsCollision(southWall) || IsCollision(westWall) || IsCollision(eastWall);
}

bool Bullet::CheckCollisionToPlayer()
{
	Player* player = ObjectManager::Get().GetObject<Player>("Player");
	
	return IsCollision(player);
}