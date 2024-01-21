#include "Player.h"
#include "EastWall.h"
#include "NorthWall.h"
#include "SouthWall.h"
#include "WestWall.h"

#include "Assertion.h"
#include "Camera3D.h"
#include "GeometryGenerator.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "MathUtils.h"
#include "RenderManager.h"
#include "ResourceManager.h"

Player::~Player()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Player::Initialize()
{
	ASSERT(!bIsInitialized_, "already initialize player object...");

	mesh_ = ResourceManager::Get().GetResource<StaticMesh>("PlayerMesh");
	if (!mesh_)
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		GeometryGenerator::CreateCone(0.5f, 1.0f, 40, vertices, indices);
		
		mesh_ = ResourceManager::Get().CreateResource<StaticMesh>("PlayerMesh");
		mesh_->Initialize(vertices, indices);
	}

	material_ = ResourceManager::Get().GetResource<Material>("PlayerMaterial");
	if (!material_)
	{
		material_ = ResourceManager::Get().CreateResource<Material>("PlayerMaterial");
		material_->Initialize(
			Vector3f(0.2125f, 0.1275f, 0.054f),
			Vector3f(0.714f, 0.4284f, 0.18144f),
			Vector3f(0.393548f, 0.271906f, 0.166721f),
			0.2f * 128.0f
		);
	}

	transform_ = Transform(Vector3f(0.0f, 0.5f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
	boundingVolume_ = Sphere3D(transform_.GetLocation(), 0.25f);
	currentHP_ = maxHP_;
	playTime_ = 0.0f;
	hpWidth_ = 1.0f;
	hpHeight_ = 0.2f;
	hpColor_ = Vector4f(1.0f, 0.0f, 0.0f, 1.0f);
	backgroundColor_ = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);

	bIsInitialized_ = true;
}

void Player::Tick(float deltaSeconds)
{
	playTime_ += deltaSeconds;

	Vector3f position = transform_.GetLocation();

	if (InputManager::Get().GetVirtualKeyPressState(EVirtualKey::VKEY_LEFT) == EPressState::Held)
	{
		position.x -= deltaSeconds * 5.0f;
	}

	if (InputManager::Get().GetVirtualKeyPressState(EVirtualKey::VKEY_RIGHT) == EPressState::Held)
	{
		position.x += deltaSeconds * 5.0f;
	}

	if (InputManager::Get().GetVirtualKeyPressState(EVirtualKey::VKEY_UP) == EPressState::Held)
	{
		position.z -= deltaSeconds * 5.0f;
	}

	if (InputManager::Get().GetVirtualKeyPressState(EVirtualKey::VKEY_DOWN) == EPressState::Held)
	{
		position.z += deltaSeconds * 5.0f;
	}

	boundingVolume_.SetCenter(position);

	if (!CheckCollisionToWall())
	{
		transform_.SetLocation(position);
	}
	else
	{
		boundingVolume_.SetCenter(transform_.GetLocation());
	}
}

void Player::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	bIsInitialized_ = false;
}

void Player::SetHP(int32_t hp)
{
	currentHP_ = MathUtils::Clamp<int32_t>(hp, minHP_, maxHP_);
}

void Player::RenderHP(const Camera3D* camera)
{
	Matrix4x4f world = transform_.GetWorldMatrix() * MathUtils::CreateTranslation(Vector3f(0.0f, 1.0f, 0.0f));
	float rate = static_cast<float>(currentHP_) / static_cast<float>(maxHP_ - minHP_);

	RenderManager::Get().RenderHorizonDividQuad3D(world, camera, hpWidth_, hpHeight_, rate, hpColor_, backgroundColor_);
}

bool Player::CheckCollisionToWall()
{
	NorthWall* northWall = ObjectManager::Get().GetObject<NorthWall>("NorthWall");
	SouthWall* southWall = ObjectManager::Get().GetObject<SouthWall>("SouthWall");
	WestWall* westWall = ObjectManager::Get().GetObject<WestWall>("WestWall");
	EastWall* eastWall = ObjectManager::Get().GetObject<EastWall>("EastWall");

	return IsCollision(northWall) || IsCollision(southWall) || IsCollision(westWall) || IsCollision(eastWall);
}