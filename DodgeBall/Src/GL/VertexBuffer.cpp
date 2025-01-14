#include <glad/glad.h>

#include "GL/GLAssert.h"
#include "GL/VertexBuffer.h"
#include "Utils/Assertion.h"

VertexBuffer::VertexBuffer(uint32_t byteSize, const EUsage& usage)
	: byteSize_(byteSize)
	, usage_(usage)
{
	GL_API_CHECK(glGenBuffers(1, &vertexBufferID_));
	GL_API_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID_));
	GL_API_CHECK(glBufferData(GL_ARRAY_BUFFER, byteSize_, nullptr, static_cast<GLenum>(usage)));
	GL_API_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

	bIsInitialized_ = true;
}

VertexBuffer::VertexBuffer(const void* bufferPtr, uint32_t byteSize, const EUsage& usage)
	: byteSize_(byteSize)
	, usage_(usage)
{
	GL_API_CHECK(glGenBuffers(1, &vertexBufferID_));
	GL_API_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID_));
	GL_API_CHECK(glBufferData(GL_ARRAY_BUFFER, byteSize_, bufferPtr, static_cast<GLenum>(usage)));
	GL_API_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

	bIsInitialized_ = true;
}

VertexBuffer::~VertexBuffer()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void VertexBuffer::Release()
{
	CHECK(bIsInitialized_);

	GL_API_CHECK(glDeleteBuffers(1, &vertexBufferID_));

	bIsInitialized_ = false;
}

void VertexBuffer::Bind()
{
	GL_API_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID_));
}

void VertexBuffer::Unbind()
{
	GL_API_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::SetBufferData(const void* bufferPtr, uint32_t bufferSize)
{
	CHECK(bufferPtr != nullptr && bufferSize <= byteSize_);

	VertexBuffer::Bind();
	{
		switch (usage_)
		{
		case EUsage::STREAM:
			GL_API_CHECK(glBufferData(GL_ARRAY_BUFFER, bufferSize, bufferPtr, static_cast<GLenum>(usage_)));
			break;

		case EUsage::STATIC:
			GL_API_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, bufferSize, bufferPtr));
			break;

		case EUsage::DYNAMIC:
		{
			void* vertexBufferPtr = nullptr;

			vertexBufferPtr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			GL_EXP_CHECK(vertexBufferPtr != nullptr);

			std::memcpy(vertexBufferPtr, bufferPtr, bufferSize);
			GL_EXP_CHECK(glUnmapBuffer(GL_ARRAY_BUFFER));
		}
		break;

		default:
			ASSERT(false, "Undefined buffer usage type.");
		}
	}
	VertexBuffer::Unbind();
}