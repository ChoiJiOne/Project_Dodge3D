#include "UIBoard.h"
#include "Player.h"

#include "RenderManager.h"
#include "ObjectManager.h"
#include "StringUtils.h"
#include "Window.h"

UIBoard::~UIBoard()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void UIBoard::Tick(float deltaSeconds)
{
	int32_t width;
	int32_t height;
	RenderManager::Get().GetRenderTargetWindow()->GetSize(width, height);

	center_ = Vector2f(static_cast<float>(width) / 2.0f, height_);

	Player* player = ObjectManager::Get().GetObject<Player>("Player");

	std::wstring life;
	switch (player->GetLife())
	{
	case 3:
		life = L"O O O";
		break;

	case 2:
		life = L"O O X";
		break;

	case 1:
		life = L"O X X";
		break;

	default:
		life = L"X X X";
		break;
	}
	
	text_ = StringUtils::PrintF(L"TIME : %3d LIEF : %s", static_cast<int32_t>(player->GetPlayTime()), life.c_str());
}