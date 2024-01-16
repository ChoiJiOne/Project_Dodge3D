#include "SouthWall.h"

#include "Assertion.h"
#include "GeometryGenerator.h"
#include "ResourceManager.h"

SouthWall::~SouthWall()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void SouthWall::Initialize()
{
	ASSERT(!bIsInitialized_, "already initialize south wall object...");

	mesh_ = ResourceManager::Get().GetResource<StaticMesh>("SouthWallMesh");
	if (!mesh_)
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		GeometryGenerator::CreateCube(Vector3f(10.0f, 1.0f, 1.0f), vertices, indices);

		mesh_ = ResourceManager::Get().CreateResource<StaticMesh>("SouthWallMesh");
		mesh_->Initialize(vertices, indices);
	}

	material_ = ResourceManager::Get().GetResource<Material>("SouthWallMaterial");
	if (!material_)
	{
		material_ = ResourceManager::Get().CreateResource<Material>("SouthWallMaterial");
		material_->Initialize(
			Vector3f(0.19225f, 0.19225f, 0.19225f),
			Vector3f(0.50754f, 0.50754f, 0.50754f),
			Vector3f(0.508273f, 0.508273f, 0.508273f),
			0.4f * 128.0f
		);
	}
	
	transform_ = Transform(Vector3f(0.0f, 0.5f, +5.5f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
	boundingVolume_ = Box3D(transform_.GetLocation(), Vector3f(10.0f, 1.0f, 1.0f));

	bIsInitialized_ = true;
}

void SouthWall::Tick(float deltaSeconds)
{
}

void SouthWall::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	bIsInitialized_ = false;
}