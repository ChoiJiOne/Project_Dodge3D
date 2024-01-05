#include "Material.h"

#include "Assertion.h"

Material::~Material()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Material::Initialize(const Vector3f& ambient, const Vector3f& diffuse, const Vector3f& specular, float shininess)
{
	ASSERT(!bIsInitialized_, "already initialize material resource...");

	ambient_ = ambient;
	diffuse_ = diffuse;
	specular_ = specular;
	shininess_ = shininess;

	bIsInitialized_ = true;
}

void Material::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");
	bIsInitialized_ = false;
}