#include "GameObject.h"

bool GameObject::IsCollision(GameObject* object) const
{
	if (this == object) return false; // 자기 자신과는 충돌 여부 X

	const IShape3D* boundingVolume = GetBoundingVolume();
	return boundingVolume->Intersect(object->GetBoundingVolume());
}