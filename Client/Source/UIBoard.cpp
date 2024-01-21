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

	float boardWidth = 200.0f;
	float boardHeight = 50.0f;

	Vector2f center = Vector2f(static_cast<float>(width) / 2.0f, boardHeight);
	TTFont* font = ResourceManager::Get().GetResource<TTFont>("Font32");

	UIPanel::UIPanelConstructParam param {
		boardWidth,
		boardHeight,
		Vector2f(static_cast<float>(width) / 2.0f, boardHeight),
		L"",
		ResourceManager::Get().GetResource<TTFont>("Font32"),
		Vector4f(0.227f, 0.663f, 1.0f, 0.9f),
		Vector4f(0.094f, 0.122f, 0.165f, 0.9f),
		Vector4f(0.227f, 0.663f, 1.0f, 0.9f)
	};
	
	UIPanel::Initialize(param);
}

void UIBoard::Tick(float deltaSeconds)
{
	Player* player = ObjectManager::Get().GetObject<Player>("Player");

	center_ = GetCenterFromWindow();
	text_ = StringUtils::PrintF(L"TIME : %3d", static_cast<int32_t>(player->GetPlayTime()));
}

Vector2f UIBoard::GetCenterFromWindow()
{
	int32_t windowWidth;
	int32_t windowHeight;
	RenderManager::Get().GetRenderTargetWindow()->GetSize(windowWidth, windowHeight);
	
	return Vector2f(static_cast<float>(windowWidth) / 2.0f, height_);
}