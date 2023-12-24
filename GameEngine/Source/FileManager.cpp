#include "FileManager.h"

#include "Assertion.h"
#include "WindowsAssertion.h"

void FileManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup file manager...");

	bIsStartup_ = true;
}

void FileManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

	bIsStartup_ = false;
}
