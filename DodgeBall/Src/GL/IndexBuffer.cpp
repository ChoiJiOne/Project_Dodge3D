#include <glad/glad.h>

#include "GL/GLAssert.h"
#include "GL/IndexBuffer.h"
#include "Utils/Assertion.h"

IndexBuffer::IndexBuffer(const void* bufferPtr, uint32_t indexCount)
	: indexCount_(indexCount)
{
	uint32_t indexBufferSize = indexCount_ * sizeof(uint32_t);

	GL_API_CHECK(glGenBuffers(1, &indexBufferID_));
	GL_API_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID_));
	GL_API_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, bufferPtr, GL_STATIC_DRAW));
	GL_API_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

	bIsInitialized_ = true;
}

IndexBuffer::~IndexBuffer()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void IndexBuffer::Release()
{
	CHECK(bIsInitialized_);

	GL_API_CHECK(glDeleteBuffers(1, &indexBufferID_));

	bIsInitialized_ = false;
}

void IndexBuffer::Bind()
{
	GL_API_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID_));
}

void IndexBuffer::Unbind()
{
	GL_API_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}