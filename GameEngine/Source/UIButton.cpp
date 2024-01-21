#include "UIButton.h"

#include "Assertion.h"
#include "TTFont.h"
#include "RenderManager.h"

UIButton::~UIButton()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void UIButton::Initialize(const UIButtonConstructParam& uiConstructParam)
{
	ASSERT(!bIsInitialized_, "already initialize ui button object...");

	width_ = uiConstructParam.width;
	height_ = uiConstructParam.height;
	center_ = uiConstructParam.center;
	text_ = uiConstructParam.text;
	font_ = uiConstructParam.font;
	outlineColor_ = uiConstructParam.outlineColor;
	disableColor_ = uiConstructParam.disableColor;
	enableColor_ = uiConstructParam.enableColor;
	pressColor_ = uiConstructParam.pressColor;
	releaseColor_ = uiConstructParam.releaseColor;
	virtualKey_ = uiConstructParam.virtualKey;
	clickEvent_ = uiConstructParam.clickEvent;
	
	bIsInitialized_ = true;
}

void UIButton::Tick(float deltaSeconds)
{

}

void UIButton::Render()
{
}

void UIButton::Release()
{
}

bool UIButton::DetectMouseCursorInButton()
{
	Vector2i cursorPos = InputManager::Get().GetCurrCursorPosition();

	Vector2f minPosition = center_ - Vector2f(width_, height_) * 0.5f;
	Vector2f maxPosition = center_ + Vector2f(width_, height_) * 0.5f;
	Vector2f currentCursorPosition = Vector2f(static_cast<float>(cursorPos.x), static_cast<float>(cursorPos.y));

	return (minPosition.x <= currentCursorPosition.x && currentCursorPosition.x <= maxPosition.x) 
		&& (minPosition.y <= currentCursorPosition.y && currentCursorPosition.y <= maxPosition.y);
}