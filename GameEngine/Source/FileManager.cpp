#include "FileManager.h"

#include "Assertion.h"
#include "StringUtils.h"
#include "WindowsAssertion.h"

void FileManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup file manager...");

	wchar_t* bufferPtr = StringUtils::GetWideCharBufferPtr();
	WINDOWS_ASSERT(GetModuleFileNameW(nullptr, bufferPtr, StringUtils::STRING_BUFFER_SIZE), "failed to get execute file name...");

	executePath_ = std::wstring(bufferPtr);

	bIsStartup_ = true;
}

void FileManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

	bIsStartup_ = false;
}
