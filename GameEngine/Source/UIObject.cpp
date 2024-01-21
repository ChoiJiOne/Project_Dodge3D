#include "UIObject.h"

#include "Assertion.h"
#include "TTFont.h"
#include "RenderManager.h"

void UIObject::Initialize(const UIConstructParam& uiConstructParam)
{
	ASSERT(!bIsInitialized_, "already initialize ui object...");

	width_ = uiConstructParam.width;
	height_ = uiConstructParam.height;
	center_ = uiConstructParam.center;
	text_ = uiConstructParam.text;
	font_ = uiConstructParam.font;
	outlineColor_ = uiConstructParam.outlineColor;
	backgroundColor_ = uiConstructParam.backgroundColor;
	textColor_ = uiConstructParam.textColor;
	transparent_ = uiConstructParam.transparent;

	bIsInitialized_ = true;
}

void UIObject::Tick(float deltaSeconds)
{
}

void UIObject::Render()
{
	RenderManager& renderManager = RenderManager::Get();

	Vector4f backgroundRGBA = backgroundColor_ * transparent_;
	renderManager.RenderRectangle2D(center_, width_, height_, 0.0f, backgroundRGBA);

	Vector4f outlineRGBA = outlineColor_ * transparent_;
	renderManager.RenderWireframeRectangle2D(center_, width_, height_, 0.0f, outlineRGBA);

	if (font_ && !text_.empty())
	{
		Vector4f textRGBA = textColor_ * transparent_;
		renderManager.RenderText2D(font_, text_, center_, textRGBA);
	}
}

void UIObject::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	bIsInitialized_ = false;
}