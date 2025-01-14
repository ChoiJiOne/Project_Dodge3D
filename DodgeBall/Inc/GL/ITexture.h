#pragma once

#include <cstdint>

#include "GL/GLResource.h"

/** OpenGL �ؽ�ó ���ҽ��� �������̽��Դϴ�. */
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

	/** �ؽ�ó�� ������ ���������ο� ���ε��ϰ� Ȱ��ȭ�մϴ�. */
	virtual void Active(uint32_t unit) const = 0;

	/** �ؽ�ó�� ����/���� ũ�⸦ ����ϴ�. */
	virtual int32_t GetWidth() const = 0;
	virtual int32_t GetHeight() const = 0;
};