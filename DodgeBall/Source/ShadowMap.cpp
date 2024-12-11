#include <glad/glad.h>

#include "Assertion.h"
#include "ShadowMap.h"

ShadowMap::~ShadowMap()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void ShadowMap::Initialize(uint32_t shadowWidth, uint32_t shadowHeight)
{
	ASSERT(!bIsInitialized_, "already initialize shadow map...");
	ASSERT((shadowWidth >= 0 && shadowHeight >= 0), "%d, %d is invlid shadow map size...", shadowWidth, shadowHeight);

	float border[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	GL_ASSERT(glGenFramebuffers(1, &shadowMapFBO_), "failed to generate shaodw map framebuffer...");
	GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO_), "failed to bind shadow map framebuffer...");

	GL_ASSERT(glGenTextures(1, &shadowMapID_), "filed to generate shadow map texture...");
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, shadowMapID_), "failed to bind shadow map texture...");
	GL_ASSERT(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr), "failed to allows elements of an image array to be read by shaders...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST), "failed to set texture object min filter...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST), "failed to set texture object mag filter...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER), "failed to set texture object warp s...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER), "failed to set texture object warp t...");
	GL_ASSERT(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border), "failed to set texture border color...");

	GL_ASSERT(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMapID_, 0), "failed to set framebuffer depth buffer..");
	GL_ASSERT(glDrawBuffer(GL_NONE), "failed to no color buffers are written...");
	GL_ASSERT(glReadBuffer(GL_NONE), "failed to select a color buffer source for pixels...");

	GLenum state = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	ASSERT(state == GL_FRAMEBUFFER_COMPLETE, "not complete framebuffer state : %x...", static_cast<int32_t>(state));

	GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, 0), "failed to unbind shadow map framebuffer...");

	bIsInitialized_ = true;
}

void ShadowMap::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	GL_ASSERT(glDeleteTextures(1, &shadowMapID_), "failed to delete shaodw map texture...");
	GL_ASSERT(glDeleteFramebuffers(1, &shadowMapFBO_), "failed to delete shadow map framebuffer...");

	bIsInitialized_ = false;
}

void ShadowMap::Clear()
{
	ASSERT(bIsBind_, "unbind this shadow map...");
	glClear(GL_DEPTH_BUFFER_BIT);
}

void ShadowMap::Bind()
{
	if (!bIsBind_)
	{
		bIsBind_ = true;
		GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO_), "failed to bind shadow map framebuffer...");
	}
}

void ShadowMap::Unbind()
{
	if (bIsBind_)
	{
		bIsBind_ = false;
		GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, 0), "failed to unbind shadow map framebuffer...");
	}
}

void ShadowMap::Active(uint32_t unit) const
{
	GL_ASSERT(glActiveTexture(GL_TEXTURE0 + unit), "failed to active %d texture unit...", (GL_TEXTURE0 + unit));
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, shadowMapID_), "failed to bind shadow map texture...");
}