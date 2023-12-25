#include "ResourceManager.h"

#include "Assertion.h"

void ResourceManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup resource manager...");

	bIsStartup_ = true;
}

void ResourceManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

	bIsStartup_ = false;
}