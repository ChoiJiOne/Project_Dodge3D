#include "Transform.h"

#include "Assertion.h"
#include "MathUtils.h"

void Transform::SetLocation(const Vector3f& location)
{
	location_ = location;
	ComputeWorldMatrix();
}

void Transform::SetRotate(const Vector3f& rotate)
{
	rotate_ = rotate;
	ComputeWorldMatrix();
}

void Transform::SetScale(const Vector3f& scale)
{
	scale_ = scale;
	ComputeWorldMatrix();
}

void Transform::SetProperties(const Vector3f& location, const Vector3f& rotate, const Vector3f& scale)
{
	location_ = location;
	rotate_ = rotate;
	scale_ = scale;
	ComputeWorldMatrix();
}

void Transform::ComputeWorldMatrix()
{
	Matrix4x4f transform = MathUtils::CreateTranslation(location_);
	Matrix4x4f rotate = MathUtils::CreateRotateY(rotate_.y) * MathUtils::CreateRotateX(rotate_.x) * MathUtils::CreateRotateZ(rotate_.z);
	Matrix4x4f scale = MathUtils::CreateScale(scale_);

	worldMatrix_ = scale * rotate * transform;
}