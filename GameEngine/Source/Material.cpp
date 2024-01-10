#include "Material.h"

#include "Assertion.h"

Material::~Material()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Material::Initialize(const Vector3f& ambientRGB, const Vector3f& diffuseRGB, const Vector3f& specularRGB, float shininess)
{
	ASSERT(!bIsInitialized_, "already initialize material resource...");

	ambientRGB_ = ambientRGB;
	diffuseRGB_ = diffuseRGB;
	specularRGB_ = specularRGB;
	shininess_ = shininess;
	
	bIsInitialized_ = true;
}

void Material::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	bIsInitialized_ = false;
}
