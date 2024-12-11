#include "ResourceManager.h"

#include "Assertion.h"

void ResourceManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup resource manager...");

	resourceCache_ = std::unordered_map<std::string, std::unique_ptr<IResource>>();

	bIsStartup_ = true;
}

void ResourceManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

	for (auto& resource : resourceCache_)
	{
		resource.second->Release();
		resource.second.reset();
	}
	
	bIsStartup_ = false;
}

void ResourceManager::DestroyResource(const std::string& signature)
{
	if (IsValidResourceKey(signature))
	{
		IResource* resource = resourceCache_.at(signature).get();
		if (resource && resource->IsInitialized())
		{
			resource->Release();
		}

		resourceCache_.erase(signature);
	}
}

bool ResourceManager::IsValidResourceKey(const std::string& key)
{
	return resourceCache_.find(key) != resourceCache_.end();
}