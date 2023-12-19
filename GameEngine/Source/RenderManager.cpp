#include "RenderManager.h"

#include <array>

#include <glad/glad_wgl.h>
#include <glad/glad.h>

#include "Assertion.h"
#include "GLAssertion.h"
#include "Window.h"
#include "WindowsAssertion.h"

/**
 * @brief OpenGL의 버전입니다.
 * 
 * @note 이 값은 4.6으로 고정되어 있습니다.
 */
#define FIX_OPENGL_MAJOR_VERSION 4 // OpenGL 주(4) 버전입니다.
#define FIX_OPENGL_MINOR_VERSION 6 // OpenGL 부(6) 버전입니다.

void RenderManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup render manager...");
	ASSERT(renderTargetWindow_ != nullptr, "haven't set the render target window...");

	deviceContext_ = GetDC(renderTargetWindow_->GetHandle());
	ASSERT(deviceContext_ != nullptr, "failed to get device context handle from window handle...");

	PIXELFORMATDESCRIPTOR pfd = {};
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_GENERIC_ACCELERATED | PFD_DOUBLEBUFFER | PFD_SWAP_EXCHANGE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int32_t pixelFormat = ChoosePixelFormat(deviceContext_, &pfd);
	WINDOWS_ASSERT(pixelFormat != 0, "failed to choose pixel format...");
	WINDOWS_ASSERT(SetPixelFormat(deviceContext_, pixelFormat, &pfd), "failed to set pixel format...");

	HGLRC dummyRenderContext = wglCreateContext(deviceContext_);
	WINDOWS_ASSERT(wglMakeCurrent(deviceContext_, dummyRenderContext), "failed to set opengl context...");

	ASSERT(gladLoadWGLLoader((GLADloadproc)(wglGetProcAddress), deviceContext_), "failed to load Windows OpenGL function...");

	const std::array<int32_t, 9> attributes = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, FIX_OPENGL_MAJOR_VERSION,
		WGL_CONTEXT_MINOR_VERSION_ARB, FIX_OPENGL_MINOR_VERSION,
		WGL_CONTEXT_FLAGS_ARB, 0,
		WGL_CONTEXT_PROFILE_MASK_ARB,
		WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0,
	};

	glRenderContext_ = wglCreateContextAttribsARB(deviceContext_, nullptr, attributes.data());
	WINDOWS_ASSERT(wglMakeCurrent(nullptr, nullptr), "failed to set empty opengl context...");
	WINDOWS_ASSERT(wglDeleteContext(dummyRenderContext), "failed to delete dummy render context...");
	WINDOWS_ASSERT(wglMakeCurrent(deviceContext_, glRenderContext_), "faild to set opengl context...");

	ASSERT(gladLoadGL(), "failed to load OpenGL function...");

	SetVsyncMode(bIsEnableVsync_);
	SetDepthMode(bIsEnableDepth_);
	SetStencilMode(bIsEnableStencil_);

	bIsStartup_ = true;
}

void RenderManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

	WINDOWS_ASSERT(wglMakeCurrent(nullptr, nullptr), "failed to set empty opengl context...");
	WINDOWS_ASSERT(wglDeleteContext(glRenderContext_), "failed to delete render context...");
	WINDOWS_ASSERT(ReleaseDC(renderTargetWindow_->GetHandle(), deviceContext_), "failed to release device context...");
	
	renderTargetWindow_ = nullptr;
	bIsStartup_ = false;
}

void RenderManager::BeginFrame(float red, float green, float blue, float alpha, float depth, uint8_t stencil)
{
	glClearColor(red, green, blue, alpha);
	glClearDepth(depth);
	glClearStencil(stencil);

	GL_ASSERT(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT), "failed to clear back buffer...");
}

void RenderManager::EndFrame()
{
	WINDOWS_ASSERT(SwapBuffers(deviceContext_), "failed to swap back and front buffer...");
}

void RenderManager::SetVsyncMode(bool bIsEnable)
{
	bIsEnableVsync_ = bIsEnable;
	WINDOWS_ASSERT(wglSwapIntervalEXT(static_cast<int32_t>(bIsEnableVsync_)), "failed to set vsync mode...");
}

void RenderManager::SetDepthMode(bool bIsEnable)
{
	bIsEnableDepth_ = bIsEnable;
	if (bIsEnableDepth_)
	{
		GL_ASSERT(glEnable(GL_DEPTH_TEST), "failed to enable depth test mode...");
	}
	else
	{
		GL_ASSERT(glDisable(GL_DEPTH_TEST), "failed to disable depth test mode...");
	}
}

void RenderManager::SetStencilMode(bool bIsEnable)
{
	bIsEnableStencil_ = bIsEnable;
	if (bIsEnableStencil_)
	{
		GL_ASSERT(glEnable(GL_STENCIL_TEST), "failed to enable stencil test mode...");
	}
	else
	{
		GL_ASSERT(glDisable(GL_STENCIL_TEST), "failed to disable stencil test mode...");
	}
}