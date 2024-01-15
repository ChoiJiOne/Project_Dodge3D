#include "Box3D.h"

#include "Assertion.h"
#include "MathUtils.h"

bool Box3D::IsCollision(const Box3D& box) const
{
	Vector3f minPos = GetMinPosition();
	Vector3f maxPos = GetMaxPosition();
	Vector3f otherMinPos = box.GetMinPosition();
	Vector3f otherMaxPos = box.GetMaxPosition();

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