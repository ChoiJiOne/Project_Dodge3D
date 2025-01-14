#pragma once

#include <string>

#include "GL/ITexture.h"

/** 2D 텍스처 리소스입니다. 지원하는 포멧으로는 PNG, JPG, BMP, TGA입니다. */
class Texture2D : public ITexture
{
public:
	Texture2D(const std::string& path, const EFilter& filter);
	virtual ~Texture2D();

	DISALLOW_COPY_AND_ASSIGN(Texture2D);

	virtual void Release() override;

	virtual void Active(uint32_t unit) const override;
	virtual int32_t GetWidth() const override { return width_; }
	virtual int32_t GetHeight() const override { return height_; }

private:
	uint32_t CreateTextureFromImage(const std::string& path, const EFilter& filter);

private:
	int32_t width_ = 0;
	int32_t height_ = 0;
	int32_t channels_ = 0;
	uint32_t textureID_ = 0;
};