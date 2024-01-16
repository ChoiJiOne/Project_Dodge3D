#include "Player.h"
#include "EastWall.h"
#include "NorthWall.h"
#include "SouthWall.h"
#include "WestWall.h"

#include "Assertion.h"
#include "GeometryGenerator.h"
#include "InputManager.h"
#include "Material.h"
#include "ObjectManager.h"
#include "ResourceManager.h"
#include "StaticMesh.h"

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
	boundingVolume_ = Sphere3D(transform_.GetLocation(), 0.5f);

	bIsInitialized_ = true;
}

void Player::Tick(float deltaSeconds)
{
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

	NorthWall* northWall = ObjectManager::Get().GetObject<NorthWall>("NorthWall");
	SouthWall* southWall = ObjectManager::Get().GetObject<SouthWall>("SouthWall");
	WestWall* westWall = ObjectManager::Get().GetObject<WestWall>("WestWall");
	EastWall* eastWall = ObjectManager::Get().GetObject<EastWall>("EastWall");

	if (!northWall->GetBoundingVolume().Intersect(&boundingVolume_) &&
		!southWall->GetBoundingVolume().Intersect(&boundingVolume_) &&
		!westWall->GetBoundingVolume().Intersect(&boundingVolume_) &&
		!eastWall->GetBoundingVolume().Intersect(&boundingVolume_)
	)
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