#include "UIBoard.h"
#include "Player.h"

#include "RenderManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "StringUtils.h"
#include "TTFont.h"
#include "Window.h"

UIBoard::~UIBoard()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void UIBoard::Initialize()
{
	int32_t width;
	int32_t height;
	RenderManager::Get().GetRenderTargetWindow()->GetSize(width, height);

	float boardWidth = 400.0f;
	float boardHeight = 50.0f;

	Vector2f center = Vector2f(static_cast<float>(width) / 2.0f, boardHeight);
	TTFont* font = ResourceManager::Get().GetResource<TTFont>("Font32");
	
	UIPanel::Initialize(boardWidth, boardHeight, center, L"", font, Vector3f(0.227f, 0.663f, 1.0f), Vector3f(0.094f, 0.122f, 0.165f), Vector3f(0.227f, 0.663f, 1.0f), 0.9f);
}

void UIBoard::Tick(float deltaSeconds)
{
	Player* player = ObjectManager::Get().GetObject<Player>("Player");

	center_ = GetCenterFromWindow();
	std::wstring life = GetPlayerLife(player);

	text_ = StringUtils::PrintF(L"TIME : %3d  LIEF : %s", static_cast<int32_t>(player->GetPlayTime()), life.c_str());
}

Vector2f UIBoard::GetCenterFromWindow()
{
	int32_t windowWidth;
	int32_t windowHeight;
	RenderManager::Get().GetRenderTargetWindow()->GetSize(windowWidth, windowHeight);
	
	return Vector2f(static_cast<float>(windowHeight) / 2.0f, height_);
}

std::wstring UIBoard::GetPlayerLife(const Player* player)
{
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

	return life;
}