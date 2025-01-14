#pragma once

#include <cstdint>

#include "GL/GLResource.h"

/** OpenGL 텍스처 리소스의 인터페이스입니다. */
class ITexture : public GLResource
{
public:
	/** https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexParameter.xhtml */
	enum class EFilter
	{
		NEAREST = 0x2600,
		LINEAR = 0x2601,
	};

public:
	ITexture() = default;
	virtual ~ITexture() {}

	virtual void Release() = 0;

	/** 텍스처를 렌더링 파이프라인에 바인딩하고 활성화합니다. */
	virtual void Active(uint32_t unit) const = 0;

	/** 텍스처의 가로/세로 크기를 얻습니다. */
	virtual int32_t GetWidth() const = 0;
	virtual int32_t GetHeight() const = 0;
};