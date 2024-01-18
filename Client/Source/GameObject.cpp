#include "GameObject.h"

bool GameObject::IsCollision(const GameObject* object) const
{
	if (this == object || object == nullptr)
	{
		return false;
	}

	const IShape3D* boundingVolume = GetBoundingVolume();
	return boundingVolume->Intersect(object->GetBoundingVolume());
}