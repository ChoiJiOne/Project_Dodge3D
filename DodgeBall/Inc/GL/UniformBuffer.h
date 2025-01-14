#pragma once

#include <cstdint>

#include "GL/GLResource.h"

/** ������ ���������ο� ���ε� ������ ������ �����Դϴ�. */
class UniformBuffer : public GLResource
{
public:
	/** ������ ������ ��� �����Դϴ�. */
	enum class EUsage
	{
		NONE = 0x0000,
		STREAM = 0x88E0,
		STATIC = 0x88E4,
		DYNAMIC = 0x88E8,
	};

public:
	/** �� �����ڸ� �̿��ؼ� ������ ���۸� �����ϸ� ���߿� SetBufferData�� �̿��ؼ� ������ ���� ä�� �־�� �մϴ�. */
	UniformBuffer(uint32_t byteSize, const EUsage& usage);
	UniformBuffer(const void* bufferPtr, uint32_t byteSize, const EUsage& usage);
	virtual ~UniformBuffer();

	DISALLOW_COPY_AND_ASSIGN(UniformBuffer);

	virtual void Release() override;

	/** ������ ���۸� ���������ο� ���ε��մϴ�. */
	void Bind();

	/** ���ε��� ������ ���۸� ���ε� �����մϴ�. */
	void Unbind();

	/**
	 * ���̴����� ������ ���۸� ������ �� �ֵ��� ���̴��� �����ϴ� ������ ������ ������ �����մϴ�.
	 * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindBufferBase.xhtml
	 */
	void BindSlot(const uint32_t slot);

	/** ������ ������ �����͸� �����մϴ�. */
	void SetBufferData(const void* bufferPtr, uint32_t bufferSize);

private:
	uint32_t uniformBufferID_ = 0;
	uint32_t byteSize_ = 0;
	EUsage usage_ = EUsage::NONE;
};