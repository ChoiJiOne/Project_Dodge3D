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

void UIPanel::Initialize(float width, float height, const Vector2f& center, const std::wstring& text, TTFont* font, const Vector3f& outlineRGB, const Vector3f& backgroundRGB, const Vector3f& textRGB, float transparent)
{
	ASSERT(!bIsInitialized_, "already initialize ui panel object...");

	width_ = width;
	height_ = height;
	center_ = center;
	text_ = text;
	font_ = font;
	outlineRGB_ = outlineRGB;
	backgroundRGB_ = backgroundRGB;
	textRGB_ = textRGB;
	transparent_ = transparent;

	bIsInitialized_ = true;
}

void UIPanel::Tick(float deltaSeconds)
{
}

void UIPanel::Render()
{
	RenderManager& renderManager = RenderManager::Get();

	Vector4f backgroundRGBA = Vector4f(backgroundRGB_.r, backgroundRGB_.g, backgroundRGB_.b, transparent_);
	Vector4f outlineRGBA = Vector4f(outlineRGB_.r, outlineRGB_.g, outlineRGB_.b, transparent_);
	Vector4f textRGBA = Vector4f(textRGB_.r, textRGB_.g, textRGB_.b, transparent_);

	renderManager.RenderRectangle2D(center_, width_, height_, 0.0f, backgroundRGBA);
	renderManager.RenderWireframeRectangle2D(center_, width_, height_, 0.0f, outlineRGBA);
	renderManager.RenderText2D(font_, text_, center_, textRGBA);
}

void UIPanel::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	bIsInitialized_ = false;
}