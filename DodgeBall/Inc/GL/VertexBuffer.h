#pragma once

#include <cstdint>

#include "GL/GLResource.h"

/** ������ ���������ο� ���ε� ������ ���ؽ� �����Դϴ�. */
class VertexBuffer : public GLResource
{
public:
	/** ���ؽ� ������ ��� �����Դϴ�. */
	enum class EUsage
	{
		NONE    = 0x0000,
		STREAM  = 0x88E0,
		STATIC  = 0x88E4,
		DYNAMIC = 0x88E8,
	};

public:
	/** �� �����ڸ� �̿��ؼ� ���ؽ� ���۸� �����ϸ� ���߿� SetBufferData�� �̿��ؼ� ������ ���� ä�� �־�� �մϴ�. */
	VertexBuffer(uint32_t byteSize, const EUsage& usage);
	VertexBuffer(const void* bufferPtr, uint32_t byteSize, const EUsage& usage);
	virtual ~VertexBuffer();

	DISALLOW_COPY_AND_ASSIGN(VertexBuffer);

	virtual void Release() override;

	/** ���ؽ� ���۸� ���������ο� ���ε��մϴ�. */
	void Bind();

	/** ���ε��� ���ؽ� ���۸� ���ε� �����մϴ�. */
	void Unbind();

	/** ���ؽ� ������ �����͸� �����մϴ�. */
	void SetBufferData(const void* bufferPtr, uint32_t bufferSize);

private:
	uint32_t vertexBufferID_ = 0;
	uint32_t byteSize_ = 0;
	EUsage usage_ = EUsage::NONE;
};