#include "WindowsCrashUtils.h"

#include "StringUtils.h"
#include "WindowsAssertion.h"

#include <dbghelp.h>
#include <pathcch.h>

std::wstring WindowsCrashUtils::crashInfoSavePath_;

LPTOP_LEVEL_EXCEPTION_FILTER topLevelExceptionFilter;

void WindowsCrashUtils::RegisterExceptionFilter()
{
	topLevelExceptionFilter = SetUnhandledExceptionFilter(DetectApplicationCrash);

	wchar_t* bufferPtr = StringUtils::GetWideCharBufferPtr();
	WINDOWS_ASSERT(GetModuleFileNameW(nullptr, bufferPtr, StringUtils::STRING_BUFFER_SIZE), "failed to get execute file name...");
	ASSERT(SUCCEEDED(PathCchRemoveFileSpec(bufferPtr, StringUtils::STRING_BUFFER_SIZE)), "failed to remove execute file name...");

	crashInfoSavePath_ = StringUtils::PrintF(L"%s\\Crash\\", bufferPtr);
}

void WindowsCrashUtils::UnregisterExceptionFilter()
{
	SetUnhandledExceptionFilter(topLevelExceptionFilter);
}

LONG WINAPI WindowsCrashUtils::DetectApplicationCrash(EXCEPTION_POINTERS* exceptionPtr)
{
	std::wstring systemTime = GetCrashSystemTime();
	std::wstring minidump = StringUtils::PrintF(L"%sWindows-%s-Minidump.dmp", crashInfoSavePath_.c_str(), systemTime.c_str());

	HANDLE dumpFileHandle = CreateFileW(minidump.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (dumpFileHandle == INVALID_HANDLE_VALUE)
	{
		return EXCEPTION_EXECUTE_HANDLER;
	}

	_MINIDUMP_EXCEPTION_INFORMATION exception;
	exception.ThreadId = GetCurrentThreadId();
	exception.ExceptionPointers = exceptionPtr;
	exception.ClientPointers = FALSE;

	MiniDumpWriteDump(
		GetCurrentProcess(),
		GetCurrentProcessId(),
		dumpFileHandle,
		MiniDumpWithFullMemory,
		&exception,
		nullptr,
		nullptr
	);

	CloseHandle(dumpFileHandle);
	return EXCEPTION_EXECUTE_HANDLER;
}

std::wstring WindowsCrashUtils::GetCrashSystemTime()
{
	SYSTEMTIME currentSystemTime;
	GetLocalTime(&currentSystemTime);

	return StringUtils::PrintF(
		L"%4d-%02d-%02d-%02d-%02d-%02d",
		static_cast<int32_t>(currentSystemTime.wYear),
		static_cast<int32_t>(currentSystemTime.wMonth),
		static_cast<int32_t>(currentSystemTime.wDay),
		static_cast<int32_t>(currentSystemTime.wHour),
		static_cast<int32_t>(currentSystemTime.wMinute),
		static_cast<int32_t>(currentSystemTime.wSecond)
	);
}