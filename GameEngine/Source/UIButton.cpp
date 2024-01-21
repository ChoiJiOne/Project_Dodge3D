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
	textColor_ = uiConstructParam.textColor;
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
	EPressState keyPressState = InputManager::Get().GetVirtualKeyPressState(virtualKey_);

	if (DetectMouseCursorInButton())
	{
		if (keyPressState == EPressState::Held || keyPressState == EPressState::Pressed)
		{
			state_ = EState::Pressed;
		}
		else if (keyPressState == EPressState::Released)
		{
			state_ = EState::Released;
		}
		else // keyPressState == EPressState::None
		{
			state_ = EState::Enabled;
		}
	}
	else
	{
		if (keyPressState == EPressState::Held)
		{
			if (state_ == EState::Pressed)
			{
				state_ = EState::Pressed;
			}
			else
			{
				state_ = EState::Disabled;
			}
		}
		else
		{
			state_ = EState::Disabled;
		}
	}

	if (state_ == EState::Released)
	{
		clickEvent_();
	}
}

void UIButton::Render()
{
	RenderManager& renderManager = RenderManager::Get();

	Vector4f backgroundColor;
	switch (state_)
	{
	case EState::Disabled:
		backgroundColor = disableColor_;
		break;

	case EState::Enabled:
		backgroundColor = enableColor_;
		break;

	case EState::Pressed:
		backgroundColor = pressColor_;
		break;

	case EState::Released:
		backgroundColor = releaseColor_;
		break;
	}

	renderManager.RenderRectangle2D(center_, width_, height_, 0.0f, backgroundColor);
	renderManager.RenderWireframeRectangle2D(center_, width_, height_, 0.0f, outlineColor_);
	if (font_ && !text_.empty())
	{
		renderManager.RenderText2D(font_, text_, center_, textColor_);
	}
}

void UIButton::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	bIsInitialized_ = false;
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