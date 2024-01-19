#include <windows.h>

#include <cstdarg>
#include <string>

#include "Config.h"

std::string PrintF(const char* format, ...)
{
	static const int32_t MAX_BUFFER_SIZE = 1024;
	static char buffer[MAX_BUFFER_SIZE];

	va_list args;
	va_start(args, format);
	int32_t size = vsnprintf(buffer, MAX_BUFFER_SIZE, format, args);
	va_end(args);

	return std::string(buffer, size);
}

std::string GetBasePath(const std::string& path)
{
	std::size_t lastSlash;

	if ((lastSlash = path.rfind('/')) != std::string::npos)
	{
		return path.substr(0, lastSlash + 1);
	}
	else if ((lastSlash = path.rfind('\\')) != std::string::npos)
	{
		return path.substr(0, lastSlash + 1);
	}
	else
	{
		return "";
	}
}

std::string GetCommnadLine(int32_t argc, char* argv[])
{
	std::string exePath;
	std::string rootPath;

	if (argc == 1)
	{
		rootPath = GetBasePath(argv[0]);
		exePath = rootPath + "Bin\\Client.exe";
	}
	else
	{
		exePath = GetBasePath(argv[0]) + "Client.exe";
		rootPath = argv[1];
	}

	return PrintF("%s rootPath=%s title=%s x=%d y=%d w=%d h=%d resize=%s fullscreen=%s vsync=%s imgui=%s",
		exePath.c_str(),
		rootPath.c_str(),
		WINDOW_TITLE,
		WINDOW_X, WINDOW_Y,
		WINDOW_W, WINDOW_H,
		WINDOW_RESIZE, WINDOW_FULLSCREEN, WINDOW_VSYNC, WINDOW_IMGUI
	);
}

int32_t main(int32_t argc, char* argv[])
{
	std::string commandLine = GetCommnadLine(argc, argv);

	STARTUPINFO startupInfo = {};
	startupInfo.cb = sizeof(STARTUPINFO);

	PROCESS_INFORMATION processInfo = {};
	
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	if (CreateProcessA(nullptr, commandLine.data(),
		nullptr,
		nullptr,
		FALSE,
		0,
		NULL,
		NULL,
		&startupInfo,
		&processInfo)) 
	{
	
	}

	WaitForSingleObject(processInfo.hProcess, INFINITE);
	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);

    return 0;
}