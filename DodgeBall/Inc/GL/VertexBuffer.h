#pragma once

#include <cstdint>

#include "GL/GLResource.h"

/** 렌더링 파이프라인에 바인딩 가능한 버텍스 버퍼입니다. */
class VertexBuffer : public GLResource
{
public:
	/** 버텍스 버퍼의 사용 형식입니다. */
	enum class EUsage
	{
		NONE    = 0x0000,
		STREAM  = 0x88E0,
		STATIC  = 0x88E4,
		DYNAMIC = 0x88E8,
	};

public:
	/** 이 생성자를 이용해서 버텍스 버퍼를 생성하면 나중에 SetBufferData를 이용해서 적절한 값을 채워 넣어야 합니다. */
	VertexBuffer(uint32_t byteSize, const EUsage& usage);
	VertexBuffer(const void* bufferPtr, uint32_t byteSize, const EUsage& usage);
	virtual ~VertexBuffer();

	DISALLOW_COPY_AND_ASSIGN(VertexBuffer);

	virtual void Release() override;

	/** 버텍스 버퍼를 파이프라인에 바인딩합니다. */
	void Bind();

	/** 바인딩된 버텍스 버퍼를 바인딩 해제합니다. */
	void Unbind();

	/** 버텍스 버퍼의 데이터를 설정합니다. */
	void SetBufferData(const void* bufferPtr, uint32_t bufferSize);

private:
	uint32_t vertexBufferID_ = 0;
	uint32_t byteSize_ = 0;
	EUsage usage_ = EUsage::NONE;
};