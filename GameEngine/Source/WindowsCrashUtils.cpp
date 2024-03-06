#include "WindowsCrashUtils.h"

#include <dbghelp.h>
#include <pathcch.h>
#include <Shlwapi.h>

#include "Assertion.h"
#include "GameTimer.h"
#include "StringUtils.h"

std::wstring crashInfoSavePath;

LPTOP_LEVEL_EXCEPTION_FILTER topLevelExceptionFilter;

/**
 * @brief 크래시 덤프 파일을 생성합니다.
 *
 * @param path 크래시 덤프 파일의 경로입니다.
 * @param exceptionPtr 예외와 컨텍스트 레코드입니다.
 *
 * @return 덤프 파일 생성에 성공했다면 true, 그렇지 않다면 false를 반환합니다.
 */
bool CreateMinidumpFile(const std::wstring& path, EXCEPTION_POINTERS* exceptionPtr)
{
	HANDLE fileHandle = CreateFileW(path.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (fileHandle == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	_MINIDUMP_EXCEPTION_INFORMATION exception;
	exception.ThreadId = GetCurrentThreadId();
	exception.ExceptionPointers = exceptionPtr;
	exception.ClientPointers = FALSE;

	bool bIsSuccessed = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), fileHandle, MiniDumpWithFullMemory, &exception, nullptr, nullptr);

	if (!CloseHandle(fileHandle))
	{
		bIsSuccessed = false;
	}

	return bIsSuccessed;
}

/**
 * @brief 크래시를 감지하고 에러 처리를 수행합니다.
 *
 * @param exceptionPtr 예외와 컨텍스트 레코드입니다.
 *
 * @return EXCEPTION_EXECUTE_HANDLER 값을 반환합니다.
 */
LONG WINAPI DetectApplicationCrash(EXCEPTION_POINTERS* exceptionPtr)
{
	std::wstring systemTime = GameTimer::GetCurrentSystemTime();
	std::wstring minidumpPath = StringUtils::PrintF(L"%sWindows-%s-Minidump.dmp", crashInfoSavePath.c_str(), systemTime.c_str());

	CreateMinidumpFile(minidumpPath, exceptionPtr);

	return EXCEPTION_EXECUTE_HANDLER;
}

void WindowsCrashUtils::RegisterWindowsExceptionFilter()
{
	topLevelExceptionFilter = SetUnhandledExceptionFilter(DetectApplicationCrash);

	wchar_t* bufferPtr = StringUtils::GetWideCharBufferPtr();
	WINDOWS_ASSERT(GetModuleFileNameW(nullptr, bufferPtr, StringUtils::STRING_BUFFER_SIZE), "failed to get execute file name...");
	ASSERT(SUCCEEDED(PathCchRemoveFileSpec(bufferPtr, StringUtils::STRING_BUFFER_SIZE)), "failed to remove execute file name...");

	crashInfoSavePath = StringUtils::PrintF(L"%s\\Crash\\", bufferPtr);
	if (!PathFileExistsW(crashInfoSavePath.c_str()))
	{
		WINDOWS_ASSERT(CreateDirectoryW(crashInfoSavePath.c_str(), nullptr), "failed to create %s directory...", crashInfoSavePath.c_str());
	}
}

void WindowsCrashUtils::UnregisterWindowsExceptionFilter()
{
	SetUnhandledExceptionFilter(topLevelExceptionFilter);
}