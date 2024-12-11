#include "Light.h"

#include "Assertion.h"
#include "MathUtils.h"

Light::~Light()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Light::Initialize(
	const Vector3f& position,
	const Vector3f& direction,
	const Vector3f& ambientRGB,
	const Vector3f& diffuseRGB,
	const Vector3f& specularRGB,
	const Vector3f& worldUp,
	const Matrix4x4f projection
)
{
	ASSERT(!bIsInitialized_, "already initialize light object...");

	position_ = position;
	direction_ = direction;
	ambientRGB_ = ambientRGB;
	diffuseRGB_ = diffuseRGB;
	specularRGB_ = specularRGB;

	view_ = MathUtils::CreateLookAt(position_, position_ + direction_, worldUp);
	projection_ = projection;

	bIsInitialized_ = true;
}

void Light::Tick(float deltaSeconds)
{
}

void Light::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	bIsInitialized_ = false;
}
