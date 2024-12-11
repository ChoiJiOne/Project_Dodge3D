#include "Sphere3D.h"

#include "Assertion.h"
#include "Box3D.h"
#include "MathUtils.h"

bool Sphere3D::Intersect(const IShape3D* shape) const
{
	bool bIntersect = false;
	EType type = shape->GetType();

	switch (type)
	{
	case IShape3D::EType::Box:
		bIntersect = IntersectBox3D(shape);
		break;

	case IShape3D::EType::Sphere:
		bIntersect = IntersectSphere3D(shape);
		break;

	case IShape3D::EType::None:
		bIntersect = false;
		break;

	default:
		ASSERT(false, "undefined %d 3d shape type...", static_cast<int32_t>(type));
		break;
	}

	return bIntersect;
}

bool Sphere3D::IntersectBox3D(const IShape3D* shape) const
{
	const Box3D* box = reinterpret_cast<const Box3D*>(shape);

	Vector3f minPos = box->GetMinPosition();
	Vector3f maxPos = box->GetMaxPosition();

	Vector3f closest(
		MathUtils::Clamp<float>(center_.x, minPos.x, maxPos.x),
		MathUtils::Clamp<float>(center_.y, minPos.y, maxPos.y),
		MathUtils::Clamp<float>(center_.z, minPos.z, maxPos.z)
	);

	float distSquare = MathUtils::LengthSquare(center_ - closest);
	float radiusSquare = radius_ * radius_;

	return distSquare <= radiusSquare;
}

bool Sphere3D::IntersectSphere3D(const IShape3D* shape) const
{
	const Sphere3D* sphere = reinterpret_cast<const Sphere3D*>(shape);

	float lengthSq = MathUtils::LengthSquare(center_ - sphere->GetCenter());
	float sumRadius = (radius_ + sphere->GetRadius());

	return lengthSq <= (sumRadius * sumRadius);
}