#include <glad/glad.h>

#include "Assertion.h"
#include "Framebuffer.h"

Framebuffer::~Framebuffer()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Framebuffer::Initialize(int32_t bufferWidth, int32_t bufferHeight)
{
	ASSERT(!bIsInitialized_, "already initialize framebuffer resource...");
	ASSERT((bufferWidth >= 0 && bufferHeight >= 0), "invalid frame buffer size : %d, %d", bufferWidth, bufferHeight);

	GL_ASSERT(glGenFramebuffers(1, &framebufferID_), "failed to generate framebuffer object...");
	GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, framebufferID_), "failed to bind frame buffer object...");

	GL_ASSERT(glGenTextures(1, &colorBufferID_), "failed to generate color buffer object...");
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, colorBufferID_), "failed to bind color buffer object...");
	GL_ASSERT(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bufferWidth, bufferHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr), "failed to allows elements of an image array to be read by shaders.");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), "failed to set texture object warp s...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), "failed to set texture object warp t...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR), "failed to set texture object min filter...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR), "failed to set texture object mag filter...");
	GL_ASSERT(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBufferID_, 0), "failed to set framebuffer color buffer...");

	GL_ASSERT(glGenRenderbuffers(1, &depthStencilBufferID_), "failed to generate depth stencil buffer object...");
	GL_ASSERT(glBindRenderbuffer(GL_RENDERBUFFER, depthStencilBufferID_), "failed to bind depth stencil buffer object...");
	GL_ASSERT(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, bufferWidth, bufferHeight), "failed to set depth stencil buffer size...");
	GL_ASSERT(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthStencilBufferID_), "failed to set framebuffer depth stencil buffer...");

	GLenum state = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	ASSERT(state == GL_FRAMEBUFFER_COMPLETE, "not complete framebuffer state : %x...", static_cast<int32_t>(state));

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	bIsInitialized_ = true;
}

void Framebuffer::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	GL_ASSERT(glDeleteRenderbuffers(1, &depthStencilBufferID_), "failed to delete depth stencil buffer object...");
	GL_ASSERT(glDeleteTextures(1, &colorBufferID_), "failed to delete color buffer object...");
	GL_ASSERT(glDeleteFramebuffers(1, &framebufferID_), "failed to delete frame buffer object...");

	bIsInitialized_ = false;
}

void Framebuffer::Clear(float red, float green, float blue, float alpha, float depth, uint8_t stencil)
{
	if (!bIsBind_)
	{
		Bind();
	}

	glClearColor(red, green, blue, alpha);
	glClearDepth(depth);
	glClearStencil(stencil);
	GL_ASSERT(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT), "failed to clear framebuffer...");
}

void Framebuffer::Bind()
{
	if (!bIsBind_)
	{
		bIsBind_ = true;
		glBindFramebuffer(GL_FRAMEBUFFER, framebufferID_);
	}
}

void Framebuffer::Unbind()
{
	if (bIsBind_)
	{
		bIsBind_ = false;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}

void Framebuffer::Active(uint32_t unit)
{
	GL_ASSERT(glActiveTexture(GL_TEXTURE0 + unit), "failed to active texture unit : %d", (GL_TEXTURE0 + unit));
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, colorBufferID_), "failed to bind color buffer object...");
}