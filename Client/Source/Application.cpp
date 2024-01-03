#include "ClientApplication.h"

int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
	std::unique_ptr<IGameFramework> game = std::make_unique<ClientApplication>();
	game->Setup();
	game->Run();
	game->Shutdown();
	return 0;
}