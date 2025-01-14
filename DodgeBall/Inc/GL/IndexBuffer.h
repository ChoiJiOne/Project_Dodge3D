#pragma once

#include <cstdint>

#include "GL/GLResource.h"

/**
 * 렌더링 파이프라인에 바인딩 가능한 인덱스 버퍼입니다.
 * 이 인덱스 버퍼의 사용 형식은 STATIC 형식이고, 반드시 버텍스 버퍼와 함께 사용해야 합니다.
 */
class IndexBuffer : public GLResource
{
public:
	IndexBuffer(const void* bufferPtr, uint32_t indexCount);
	virtual ~IndexBuffer();

	DISALLOW_COPY_AND_ASSIGN(IndexBuffer);

	virtual void Release() override;

	/** 인덱스 버퍼를 파이프라인에 바인딩합니다. */
	void Bind();

	/** 바인딩된 인덱스 버퍼를 바인딩 해제합니다. */
	void Unbind();

	/** 인덱스 버퍼의 수를 얻습니다. */
	uint32_t GetIndexCount() const { return indexCount_; }

private:
	uint32_t indexBufferID_ = 0;
	uint32_t indexCount_ = 0;
};