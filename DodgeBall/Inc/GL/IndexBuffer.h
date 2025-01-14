#pragma once

#include <cstdint>

#include "GL/GLResource.h"

/**
 * ������ ���������ο� ���ε� ������ �ε��� �����Դϴ�.
 * �� �ε��� ������ ��� ������ STATIC �����̰�, �ݵ�� ���ؽ� ���ۿ� �Բ� ����ؾ� �մϴ�.
 */
class IndexBuffer : public GLResource
{
public:
	IndexBuffer(const void* bufferPtr, uint32_t indexCount);
	virtual ~IndexBuffer();

	DISALLOW_COPY_AND_ASSIGN(IndexBuffer);

	virtual void Release() override;

	/** �ε��� ���۸� ���������ο� ���ε��մϴ�. */
	void Bind();

	/** ���ε��� �ε��� ���۸� ���ε� �����մϴ�. */
	void Unbind();

	/** �ε��� ������ ���� ����ϴ�. */
	uint32_t GetIndexCount() const { return indexCount_; }

private:
	uint32_t indexBufferID_ = 0;
	uint32_t indexCount_ = 0;
};