#include "ObjectManager.h"

void ObjectManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup object manager...");

	objectCache_ = std::unordered_map<std::string, std::unique_ptr<IObject>>();

	bIsStartup_ = true;
}

void ObjectManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

	for (auto& object : objectCache_)
	{
		object.second->Release();
		object.second.reset();
	}

	bIsStartup_ = false;
}

void ObjectManager::DestroyObject(const std::string& signature)
{
	if (IsValidObjectKey(signature))
	{
		IObject* object = objectCache_.at(signature).get();
		if (object && object->IsInitialized())
		{
			object->Release();
		}

		objectCache_.erase(signature);
	}
}

bool ObjectManager::IsValidObjectKey(const std::string& key)
{
	return objectCache_.find(key) != objectCache_.end();
}