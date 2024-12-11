#include "Floor.h"

#include "Assertion.h"
#include "GeometryGenerator.h"
#include "ResourceManager.h"

Floor::~Floor()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Floor::Initialize()
{
	ASSERT(!bIsInitialized_, "already initialize floor object...");

	mesh_ = ResourceManager::Get().GetResource<StaticMesh>("FloorMesh");
	if (!mesh_)
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		GeometryGenerator::CreateCube(Vector3f(10.0f, 1.0f, 10.0f), vertices, indices);

		mesh_ = ResourceManager::Get().CreateResource<StaticMesh>("FloorMesh");
		mesh_->Initialize(vertices, indices);
	}

	material_ = ResourceManager::Get().GetResource<Material>("FloorMaterial");
	if (!material_)
	{
		material_ = ResourceManager::Get().CreateResource<Material>("FloorMaterial");
		material_->Initialize(
			Vector3f(0.19125f, 0.0735f, 0.0225f),
			Vector3f(0.7038f, 0.27048f, 0.0828f),
			Vector3f(0.256777f, 0.137622f, 0.086014f),
			0.1f * 128.0f
		);
	}

	transform_ = Transform(Vector3f(0.0f, -0.5f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));

	bIsInitialized_ = true;
}

void Floor::Tick(float deltaSeconds)
{
}

void Floor::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	bIsInitialized_ = false;
}