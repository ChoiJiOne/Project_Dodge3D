#include "StaticLight.h"

#include "Assertion.h"
#include "MathUtils.h"

StaticLight::~StaticLight() {}

void StaticLight::Initialize()
{
	Light::Initialize(
		Vector3f(10.0f, 10.0f, 10.0f),
		Vector3f(-1.0f, -1.0f, -1.0f),
		Vector3f(0.5f, 0.5f, 0.5f),
		Vector3f(0.7f, 0.7f, 0.7f),
		Vector3f(1.0f, 1.0f, 1.0f),
		Vector3f(0.0f, 1.0f, 0.0f),
		MathUtils::CreateOrtho(-10.0f, +10.0f, -10.0f, +10.0f, 0.1f, 100.0f)
	);
}

void StaticLight::Tick(float deltaSeconds)
{
}

void StaticLight::Release()
{
	Light::Release();
}