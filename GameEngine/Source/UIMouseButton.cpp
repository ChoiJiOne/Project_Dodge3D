#include "UIMouseButton.h"

#include "Assertion.h"
#include "TTFont.h"
#include "RenderManager.h"

UIMouseButton::~UIMouseButton()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void UIMouseButton::Initialize(const UIButtonConstructParam& uiConstructParam)
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
	type_ = uiConstructParam.type;
	clickEvent_ = uiConstructParam.clickEvent;
	
	bIsInitialized_ = true;
}

void UIMouseButton::Tick(float deltaSeconds)
{
	EPressState keyPressState = InputManager::Get().GetVirtualKeyPressState(static_cast<EVirtualKey>(type_));

	state_ = GetMouseButtonState(keyPressState, state_);
	if (state_ == EState::Released)
	{
		clickEvent_();
	}
}

void UIMouseButton::Render()
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

void UIMouseButton::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	bIsInitialized_ = false;
}

UIMouseButton::EState UIMouseButton::GetMouseButtonState(const EPressState& keyPressState, const EState& state)
{
	if (DetectMouseCursorInButton())
	{
		if (state == EState::Disabled)
		{
			if (keyPressState == EPressState::Held || keyPressState == EPressState::Pressed)
			{
				return EState::Disabled;
			}
			else // keyPressState == EPressState::None || keyPressState == EPressState::Released
			{
				return EState::Enabled;
			}
		}
		else if (state == EState::Enabled)
		{
			if (keyPressState == EPressState::Held || keyPressState == EPressState::Pressed)
			{
				return EState::Pressed;
			}
			else
			{
				return EState::Enabled;
			}
		}
		else if (state == EState::Pressed)
		{
			if (keyPressState == EPressState::Released)
			{
				return EState::Released;
			}
			else if (keyPressState == EPressState::Held || keyPressState == EPressState::Pressed)
			{
				return EState::Pressed;
			}
			else // keyPressState == EPressState::None
			{
				return EState::Enabled;
			}
		}
		else // state == EState::Released
		{
			if (keyPressState == EPressState::None || keyPressState == EPressState::Released)
			{
				return EState::Enabled;
			}
			else // keyPressState == EPressState::Held || keyPressState == EPressState::Pressed
			{
				return EState::Pressed;
			}
		}
	}
	else
	{
		if (state == EState::Pressed && keyPressState == EPressState::Held)
		{
			return EState::Pressed;
		}
		else
		{
			return EState::Disabled;
		}
	}

	return EState::Disabled;
}

bool UIMouseButton::DetectMouseCursorInButton()
{
	Vector2i cursorPos = InputManager::Get().GetCurrCursorPosition();

	Vector2f minPosition = center_ - Vector2f(width_, height_) * 0.5f;
	Vector2f maxPosition = center_ + Vector2f(width_, height_) * 0.5f;
	Vector2f currentCursorPosition = Vector2f(static_cast<float>(cursorPos.x), static_cast<float>(cursorPos.y));

	return (minPosition.x <= currentCursorPosition.x && currentCursorPosition.x <= maxPosition.x) 
		&& (minPosition.y <= currentCursorPosition.y && currentCursorPosition.y <= maxPosition.y);
}