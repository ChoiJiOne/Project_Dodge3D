#include "Box3D.h"

#include "Assertion.h"
#include "MathUtils.h"
#include "Sphere3D.h"

bool Box3D::Intersect(const IShape3D* shape) const
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
		bIntersect =  false;
		break;

	default:
		ASSERT(false, "undefined %d 3d shape type...", static_cast<int32_t>(type));
		break;
	}

	return bIntersect;
}

bool Box3D::IntersectBox3D(const IShape3D* shape) const
{
	const Box3D* box = reinterpret_cast<const Box3D*>(shape);

	Vector3f minPos = GetMinPosition();
	Vector3f maxPos = GetMaxPosition();
	Vector3f otherMinPos = box->GetMinPosition();
	Vector3f otherMaxPos = box->GetMaxPosition();

	if (minPos.x > otherMaxPos.x || maxPos.x < otherMinPos.x)
	{
		return false;
	}

	if (minPos.y > otherMaxPos.y || maxPos.y < otherMinPos.y)
	{
		return false;
	}

	if (minPos.z > otherMaxPos.z || maxPos.z < otherMinPos.z)
	{
		return false;
	}

	return true;
}

bool Box3D::IntersectSphere3D(const IShape3D* shape) const
{
	const Sphere3D* sphere = reinterpret_cast<const Sphere3D*>(shape);
	Vector3f center = sphere->GetCenter();

	Vector3f minPos = GetMinPosition();
	Vector3f maxPos = GetMaxPosition();

	Vector3f closest(
		MathUtils::Clamp<float>(center.x, minPos.x, maxPos.x),
		MathUtils::Clamp<float>(center.y, minPos.y, maxPos.y),
		MathUtils::Clamp<float>(center.z, minPos.z, maxPos.z)
	);

	float distSquare = MathUtils::LengthSquare(center - closest);
	float radiusSquare = sphere->GetRadius() * sphere->GetRadius();

	return distSquare <= radiusSquare;
}