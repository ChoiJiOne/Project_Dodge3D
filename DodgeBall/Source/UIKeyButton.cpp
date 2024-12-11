#include "UIKeyButton.h"

#include "Assertion.h"
#include "TTFont.h"
#include "RenderManager.h"

UIKeyButton::~UIKeyButton()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void UIKeyButton::Initialize(const UIButtonConstructParam& uiConstructParam)
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
	pressColor_ = uiConstructParam.pressColor;
	releaseColor_ = uiConstructParam.releaseColor;
	virtualKey_ = uiConstructParam.key;
	keyClickEvent_ = uiConstructParam.keyClickEvent;

	bIsInitialized_ = true;
}

void UIKeyButton::Tick(float deltaSeconds)
{
	if (InputManager::Get().GetVirtualKeyPressState(virtualKey_) == EPressState::Released)
	{
		keyClickEvent_();
	}
}

void UIKeyButton::Render()
{
	RenderManager& renderManager = RenderManager::Get();
	EPressState keyPressState = InputManager::Get().GetVirtualKeyPressState(virtualKey_);

	Vector4f backgroundColor;
	switch (keyPressState)
	{
	case EPressState::Held:
	case EPressState::Pressed:
		backgroundColor = pressColor_;
		break;

	case EPressState::None:
		backgroundColor = disableColor_;
		break;
	
	case EPressState::Released:
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

void UIKeyButton::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	bIsInitialized_ = false;
}