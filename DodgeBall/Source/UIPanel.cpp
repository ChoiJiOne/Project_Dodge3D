#include "UIPanel.h"

#include "Assertion.h"
#include "TTFont.h"
#include "RenderManager.h"

UIPanel::~UIPanel()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void UIPanel::Initialize(const UIPanelConstructParam& uiConstructParam)
{
	ASSERT(!bIsInitialized_, "already initialize ui panel object...");

	width_ = uiConstructParam.width;
	height_ = uiConstructParam.height;
	center_ = uiConstructParam.center;
	text_ = uiConstructParam.text;
	font_ = uiConstructParam.font;
	outlineColor_ = uiConstructParam.outlineColor;
	backgroundColor_ = uiConstructParam.backgroundColor;
	textColor_ = uiConstructParam.textColor;

	bIsInitialized_ = true;
}

void UIPanel::Tick(float deltaSeconds)
{
}

void UIPanel::Render()
{
	RenderManager& renderManager = RenderManager::Get();

	renderManager.RenderRectangle2D(center_, width_, height_, 0.0f, backgroundColor_);
	renderManager.RenderWireframeRectangle2D(center_, width_, height_, 0.0f, outlineColor_);

	if (font_ && !text_.empty())
	{
		renderManager.RenderText2D(font_, text_, center_, textColor_);
	}
}

void UIPanel::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	bIsInitialized_ = false;
}