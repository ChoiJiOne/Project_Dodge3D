#include <cstdint>
#include <Windows.h>

#if defined(DEBUG_MODE) || defined(RELEASE_MODE) || defined(RELWITHDEBINFO_MODE)
#include <crtdbg.h>
#endif

#include <glad/glad.h>

#include "GL/GLManager.h"
#include "GLFW/GLFWManager.h"

int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
	GLFWManager::GetRef().Startup(1000, 800, "DodgeBall", true);
	GLManager::GetRef().Startup();

	bool bIsDone = false;
	GLFWManager::GetRef().AddWindowEventAction(EWindowEvent::CLOSE_WINDOW, [&]() { bIsDone = true; }, true);

	while (!bIsDone)
	{
		GLFWManager::GetRef().Tick();

		GLManager::GetRef().BeginFrame(1.0f, 0.0f, 0.0f, 1.0f);
		GLManager::GetRef().EndFrame();
	}
	
	GLManager::GetRef().Shutdown();
	GLFWManager::GetRef().Shutdown();
	return 0;
}