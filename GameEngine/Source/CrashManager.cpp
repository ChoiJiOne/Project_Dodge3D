#include "CrashManager.h"

#include "StringUtils.h"

void CrashManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup crash manager...");

	bIsStartup_ = true;
}

void CrashManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

	bIsStartup_ = false;
}
