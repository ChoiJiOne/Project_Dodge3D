#include "Camera3D.h"

#include "Assertion.h"
#include "MathUtils.h"

Camera3D::~Camera3D()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Camera3D::Initialize(
	const Vector3f& eyePosition, 
	const Vector3f& eyeDirection, 
	const Vector3f& upDirection, 
	float fovRadians, 
	float aspectRatio, 
	float nearZ, 
	float farZ
)
{
	ASSERT(!bIsInitialized_, "already initialize 3d camera object...");

	eyePosition_ = eyePosition;
	eyeDirection_ = eyeDirection;
	upDirection_ = upDirection;
	fov_ = fovRadians;
	aspectRatio_ = aspectRatio;
	nearZ_ = nearZ;
	farZ_ = farZ;

	UpdateViewMatrix();
	UpdateProjectionMatrix();

	bIsInitialized_ = true;
}

void Camera3D::Tick(float deltaSeconds)
{
}

void Camera3D::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	bIsInitialized_ = false;
}

void Camera3D::UpdateViewMatrix()
{
	view_ = MathUtils::CreateLookAt(eyePosition_, eyePosition_ + eyeDirection_, upDirection_);
}

void Camera3D::UpdateProjectionMatrix()
{
	projection_ = MathUtils::CreatePerspective(fov_, aspectRatio_, nearZ_, farZ_);
}