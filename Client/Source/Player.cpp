#include "Player.h"

#include "Assertion.h"
#include "GeometryGenerator.h"
#include "InputManager.h"
#include "Material.h"
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

	position_ = Vector3f(0.0f, 0.5f, 0.0f);
	boundingVolume_ = Sphere3D(position_, 0.5f);

	bIsInitialized_ = true;
}

void Player::Tick(float deltaSeconds)
{
	if (InputManager::Get().GetVirtualKeyPressState(EVirtualKey::VKEY_LEFT) == EPressState::Held)
	{
		position_.x -= deltaSeconds * 5.0f;
	}

	if (InputManager::Get().GetVirtualKeyPressState(EVirtualKey::VKEY_RIGHT) == EPressState::Held)
	{
		position_.x += deltaSeconds * 5.0f;
	}

	if (InputManager::Get().GetVirtualKeyPressState(EVirtualKey::VKEY_UP) == EPressState::Held)
	{
		position_.z -= deltaSeconds * 5.0f;
	}

	if (InputManager::Get().GetVirtualKeyPressState(EVirtualKey::VKEY_DOWN) == EPressState::Held)
	{
		position_.z += deltaSeconds * 5.0f;
	}
}

void Player::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	bIsInitialized_ = false;
}