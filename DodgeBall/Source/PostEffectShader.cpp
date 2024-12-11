#include <glad/glad.h>

#include "Assertion.h"
#include "PostEffectShader.h"
#include "Framebuffer.h"

PostEffectShader::~PostEffectShader()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void PostEffectShader::Initialize(const std::wstring& vsPath, const std::wstring& fsPath)
{
	ASSERT(!bIsInitialized_, "already initialize post effect shader resource...");

	Shader::Initialize(vsPath, fsPath);

	vertices_ = {
		VertexPositionTexture(Vector3f(-1.0f, +1.0f, 0.0f), Vector2f(0.0f, 0.0f)),
		VertexPositionTexture(Vector3f(-1.0f, -1.0f, 0.0f), Vector2f(0.0f, 1.0f)),
		VertexPositionTexture(Vector3f(+1.0f, +1.0f, 0.0f), Vector2f(1.0f, 0.0f)),
		VertexPositionTexture(Vector3f(+1.0f, +1.0f, 0.0f), Vector2f(1.0f, 0.0f)),
		VertexPositionTexture(Vector3f(-1.0f, -1.0f, 0.0f), Vector2f(0.0f, 1.0f)),
		VertexPositionTexture(Vector3f(+1.0f, -1.0f, 0.0f), Vector2f(1.0f, 1.0f)),
	};

	GL_ASSERT(glGenVertexArrays(1, &vertexArrayObject_), "failed to generate frame buffer vertex array...");
	GL_ASSERT(glGenBuffers(1, &vertexBufferObject_), "failed to generate frame buffer vertex buffer...");

	GL_ASSERT(glBindVertexArray(vertexArrayObject_), "failed to bind frame buffer vertex array...");
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_), "failed to bind frame buffer vertex buffer...");
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, VertexPositionTexture::GetStride() * vertices_.size(), reinterpret_cast<const void*>(vertices_.data()), GL_STATIC_DRAW),
		"failed to create a new data store for vertex buffer object...");

	GL_ASSERT(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VertexPositionTexture::GetStride(), (void*)(offsetof(VertexPositionTexture, position_))),
		"failed to specify the location and data format of the array of generic vertex attributes at index...");
	GL_ASSERT(glEnableVertexAttribArray(0), "failed to enable vertex attrib array...");

	GL_ASSERT(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VertexPositionTexture::GetStride(), (void*)(offsetof(VertexPositionTexture, uv_))),
		"failed to specify the location and data format of the array of generic vertex attributes at index...");
	GL_ASSERT(glEnableVertexAttribArray(1), "failed to enable vertex attrib array...");

	GL_ASSERT(glBindVertexArray(0), "failed to unbind frame buffer vertex array...");
}

void PostEffectShader::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	Shader::Release();

	GL_ASSERT(glDeleteBuffers(1, &vertexBufferObject_), "failed to delete frame buffer vertex buffer...");
	GL_ASSERT(glDeleteVertexArrays(1, &vertexArrayObject_), "failed to delete frame buffer vertex array object...");
}

void PostEffectShader::BlitEffect(Framebuffer* framebuffer)
{
	framebuffer->Active(0);

	GL_ASSERT(glBindVertexArray(vertexArrayObject_), "failed to bind frame buffer vertex array...");
	GL_ASSERT(glDrawArrays(GL_TRIANGLES, 0, MAX_VERTEX_SIZE), "failed to blit frame buffer...");
	GL_ASSERT(glBindVertexArray(0), "failed to unbind frame buffer vertex array...");
}