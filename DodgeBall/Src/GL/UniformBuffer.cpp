#include <glad/glad.h>

#include "GL/GLAssert.h"
#include "GL/UniformBuffer.h"
#include "Utils/Assertion.h"

UniformBuffer::UniformBuffer(uint32_t byteSize, const EUsage& usage)
	: byteSize_(byteSize)
	, usage_(usage)
{
	GL_API_CHECK(glGenBuffers(1, &uniformBufferID_));
	GL_API_CHECK(glBindBuffer(GL_UNIFORM_BUFFER, uniformBufferID_));
	GL_API_CHECK(glBufferData(GL_UNIFORM_BUFFER, byteSize_, nullptr, static_cast<GLenum>(usage)));
	GL_API_CHECK(glBindBuffer(GL_UNIFORM_BUFFER, 0));

	bIsInitialized_ = true;
}

UniformBuffer::UniformBuffer(const void* bufferPtr, uint32_t byteSize, const EUsage& usage)
	: byteSize_(byteSize)
	, usage_(usage)
{
	GL_API_CHECK(glGenBuffers(1, &uniformBufferID_));
	GL_API_CHECK(glBindBuffer(GL_UNIFORM_BUFFER, uniformBufferID_));
	GL_API_CHECK(glBufferData(GL_UNIFORM_BUFFER, byteSize_, bufferPtr, static_cast<GLenum>(usage)));
	GL_API_CHECK(glBindBuffer(GL_UNIFORM_BUFFER, 0));

	bIsInitialized_ = true;
}

UniformBuffer::~UniformBuffer()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void UniformBuffer::Release()
{
	CHECK(bIsInitialized_);

	GL_API_CHECK(glDeleteBuffers(1, &uniformBufferID_));

	bIsInitialized_ = false;
}

void UniformBuffer::Bind()
{
	GL_API_CHECK(glBindBuffer(GL_UNIFORM_BUFFER, uniformBufferID_));
}

void UniformBuffer::Unbind()
{
	GL_API_CHECK(glBindBuffer(GL_UNIFORM_BUFFER, 0));
}

void UniformBuffer::BindSlot(const uint32_t slot)
{
	GL_API_CHECK(glBindBufferBase(GL_UNIFORM_BUFFER, slot, uniformBufferID_));
}

void UniformBuffer::SetBufferData(const void* bufferPtr, uint32_t bufferSize)
{
	CHECK(bufferPtr != nullptr && bufferSize <= byteSize_);

	UniformBuffer::Bind();
	{
		switch (usage_)
		{
		case EUsage::STREAM:
			GL_API_CHECK(glBufferData(GL_UNIFORM_BUFFER, bufferSize, bufferPtr, static_cast<GLenum>(usage_)));
			break;

		case EUsage::STATIC:
			GL_API_CHECK(glBufferSubData(GL_UNIFORM_BUFFER, 0, bufferSize, bufferPtr));
			break;

		case EUsage::DYNAMIC:
		{
			void* uniformBufferPtr = nullptr;

			uniformBufferPtr = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
			GL_EXP_CHECK(uniformBufferPtr != nullptr);

			std::memcpy(uniformBufferPtr, bufferPtr, bufferSize);
			GL_EXP_CHECK(glUnmapBuffer(GL_UNIFORM_BUFFER));
		}
		break;

		default:
			ASSERT(false, "Undefined buffer usage type.");
		}
	}
	UniformBuffer::Unbind();
}