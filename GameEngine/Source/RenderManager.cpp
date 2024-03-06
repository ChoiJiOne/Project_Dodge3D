#include <array>

#include <glad/glad_wgl.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_win32.h>

#include "Assertion.h"
#include "Camera3D.h"
#include "CommandLineUtils.h"

#include "GeometryShader2D.h"
#include "GeometryShader3D.h"
#include "GlyphShader2D.h"
#include "LightShader.h"
#include "MathUtils.h"
#include "PostEffectShader.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "Shader.h"
#include "Skybox.h"
#include "StaticMesh.h"
#include "ShadowMap.h"
#include "ShadowShader.h"
#include "StringUtils.h"
#include "Texture2D.h"
#include "TextureShader2D.h"
#include "Window.h"

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
	SetAlphaBlendMode(bIsEnableAlphaBlend_);

	shaderCache_ = std::unordered_map<std::wstring, Shader*>();

	shaderCache_.insert({ L"Geometry2D", ResourceManager::Get().CreateResource<GeometryShader2D>("Geometry2DShader") });
	shaderCache_.insert({ L"Geometry3D", ResourceManager::Get().CreateResource<GeometryShader3D>("Geometry3DShader") });
	shaderCache_.insert({ L"Glyph2D",    ResourceManager::Get().CreateResource<GlyphShader2D>("Glyph2DShader")       });
	shaderCache_.insert({ L"Texture2D",  ResourceManager::Get().CreateResource<TextureShader2D>("Texture2DShader")   });
	shaderCache_.insert({ L"Skybox",     ResourceManager::Get().CreateResource<Shader>("SkyboxShader")               });
	shaderCache_.insert({ L"Light",      ResourceManager::Get().CreateResource<LightShader>("LightShader")           });
	shaderCache_.insert({ L"ShadowMap",  ResourceManager::Get().CreateResource<ShadowShader>("ShadowShader")         });
	for (auto& shader : shaderCache_)
	{
		shader.second->Initialize(
			StringUtils::PrintF(L"%s%s.vert", shaderPath_.c_str(), shader.first.c_str()),
			StringUtils::PrintF(L"%s%s.frag", shaderPath_.c_str(), shader.first.c_str())
		);
	}

	const std::array<std::wstring, 6> postEffects = {
		L"PostEffect",
		L"InversionEffect",
		L"GrayscaleEffect",
		L"BlurEffect",
		L"GaussianBlurEffect",
		L"FadeEffect",
	};

	for (const auto& postEffect : postEffects)
	{
		PostEffectShader* effect = ResourceManager::Get().CreateResource<PostEffectShader>(StringUtils::Convert(postEffect));
		effect->Initialize(StringUtils::PrintF(L"%sPostEffect.vert", shaderPath_.c_str()), StringUtils::PrintF(L"%s%s.frag", shaderPath_.c_str(), postEffect.c_str()));
	}
	
	float farZ = 1.0f;
	float nearZ = -1.0f;
	int32_t screenWidth;
	int32_t screenHeight;
	renderTargetWindow_->GetSize(screenWidth, screenHeight);
	screenOrtho_ = MathUtils::CreateOrtho(0.0f, static_cast<float>(screenWidth), static_cast<float>(screenHeight), 0.0f, nearZ, farZ);
	
	if (bIsEnableImGui_)
	{
		ASSERT(ImGui_ImplWin32_InitForOpenGL(renderTargetWindow_->GetHandle()), "failed to initialize windows for opengl in imgui...");
		ASSERT(ImGui_ImplOpenGL3_Init(), "failed to initialize opengl in imgui...");
	}

	bIsStartup_ = true;
}

void RenderManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

	if (bIsEnableImGui_)
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplWin32_Shutdown();
	}

	WINDOWS_ASSERT(wglMakeCurrent(nullptr, nullptr), "failed to set empty opengl context...");
	WINDOWS_ASSERT(wglDeleteContext(glRenderContext_), "failed to delete render context...");
	WINDOWS_ASSERT(ReleaseDC(renderTargetWindow_->GetHandle(), deviceContext_), "failed to release device context...");
	
	renderTargetWindow_ = nullptr;
	bIsStartup_ = false;
}

void RenderManager::BeginFrame(float red, float green, float blue, float alpha, float depth, uint8_t stencil)
{
	if (bIsEnableImGui_)
	{
		ImGui::Render();
	}

	glClearColor(red, green, blue, alpha);
	glClearDepth(depth);
	glClearStencil(stencil);

	GL_ASSERT(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT), "failed to clear back buffer...");
}

void RenderManager::EndFrame()
{
	if (bIsEnableImGui_)
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	WINDOWS_ASSERT(SwapBuffers(deviceContext_), "failed to swap back and front buffer...");
}

void RenderManager::SetViewport(int32_t x, int32_t y, int32_t width, int32_t height)
{
	glViewport(x, y, width, height);
}

void RenderManager::SetWindowViewport()
{
	int32_t windowWidth;
	int32_t windowHeight;
	renderTargetWindow_->GetSize(windowWidth, windowHeight);

	glViewport(0, 0, windowWidth, windowHeight);
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

void RenderManager::SetAlphaBlendMode(bool bIsEnable)
{
	bIsEnableAlphaBlend_ = bIsEnable;
	if (bIsEnableAlphaBlend_)
	{
		GL_ASSERT(glEnable(GL_BLEND), "failed to enable alpha blend mode...");
		GL_ASSERT(glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO), "failed to separate blend func...");
	}
	else
	{
		GL_ASSERT(glDisable(GL_BLEND), "failed to disable alpha blend mode...");
	}
}

void RenderManager::Resize()
{
	float farZ = 1.0f;
	float nearZ = -1.0f;
	int32_t screenWidth;
	int32_t screenHeight;

	renderTargetWindow_->GetSize(screenWidth, screenHeight);
	screenOrtho_ = MathUtils::CreateOrtho(0.0f, static_cast<float>(screenWidth), static_cast<float>(screenHeight), 0.0f, nearZ, farZ);
}

void RenderManager::RenderPoints2D(const std::vector<Vector2f>& positions, const Vector4f& color, float pointSize)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderCache_.at(L"Geometry2D"));
	shader->DrawPoints2D(screenOrtho_, positions, color, pointSize);
}

void RenderManager::RenderConnectPoints2D(const std::vector<Vector2f>& positions, const Vector4f& color)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderCache_.at(L"Geometry2D"));
	shader->DrawConnectPoints2D(screenOrtho_, positions, color);
}

void RenderManager::RenderLine2D(const Vector2f& fromPosition, const Vector2f& toPosition, const Vector4f& color)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderCache_.at(L"Geometry2D"));
	shader->DrawLine2D(screenOrtho_, fromPosition, toPosition, color);
}

void RenderManager::RenderLine2D(const Vector2f& fromPosition, const Vector4f& fromColor, const Vector2f& toPosition, const Vector4f& toColor)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderCache_.at(L"Geometry2D"));
	shader->DrawLine2D(screenOrtho_, fromPosition, fromColor, toPosition, toColor);
}

void RenderManager::RenderTriangle2D(const Vector2f& fromPosition, const Vector2f& byPosition, const Vector2f& toPosition, const Vector4f& color)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderCache_.at(L"Geometry2D"));
	shader->DrawTriangle2D(screenOrtho_, fromPosition, byPosition, toPosition, color);
}

void RenderManager::RenderTriangle2D(const Vector2f& fromPosition, const Vector4f& fromColor, const Vector2f& byPosition, const Vector4f& byColor, const Vector2f& toPosition, const Vector4f& toColor)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderCache_.at(L"Geometry2D"));
	shader->DrawTriangle2D(screenOrtho_,
		fromPosition, fromColor,
		byPosition, byColor,
		toPosition, toColor
	);
}

void RenderManager::RenderWireframeTriangle2D(const Vector2f& fromPosition, const Vector2f& byPosition, const Vector2f& toPosition, const Vector4f& color)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderCache_.at(L"Geometry2D"));
	shader->DrawWireframeTriangle2D(screenOrtho_, fromPosition, byPosition, toPosition, color);
}

void RenderManager::RenderWireframeTriangle2D(const Vector2f& fromPosition, const Vector4f& fromColor, const Vector2f& byPosition, const Vector4f& byColor, const Vector2f& toPosition, const Vector4f& toColor)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderCache_.at(L"Geometry2D"));
	shader->DrawWireframeTriangle2D(screenOrtho_, fromPosition, fromColor, byPosition, byColor, toPosition, toColor);
}

void RenderManager::RenderRectangle2D(const Vector2f& center, float width, float height, float rotate, const Vector4f& color)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderCache_.at(L"Geometry2D"));
	shader->DrawRectangle2D(screenOrtho_, center, width, height, rotate, color);
}

void RenderManager::RenderWireframeRectangle2D(const Vector2f& center, float width, float height, float rotate, const Vector4f& color)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderCache_.at(L"Geometry2D"));
	shader->DrawWireframeRectangle2D(screenOrtho_, center, width, height, rotate, color);
}

void RenderManager::RenderCircle2D(const Vector2f& center, float radius, const Vector4f& color, int32_t sliceCount)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderCache_.at(L"Geometry2D"));
	shader->DrawCircle2D(screenOrtho_, center, radius, color, sliceCount);
}

void RenderManager::RenderWireframeCircle2D(const Vector2f& center, float radius, const Vector4f& color, int32_t sliceCount)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderCache_.at(L"Geometry2D"));
	shader->DrawWireframeCircle2D(screenOrtho_, center, radius, color, sliceCount);
}

void RenderManager::RenderEllipse2D(const Vector2f& center, float xAxis, float yAxis, const Vector4f& color, int32_t sliceCount)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderCache_.at(L"Geometry2D"));
	shader->DrawEllipse2D(screenOrtho_, center, xAxis, yAxis, color, sliceCount);
}

void RenderManager::RenderWireframeEllipse2D(const Vector2f& center, float xAxis, float yAxis, const Vector4f& color, int32_t sliceCount)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderCache_.at(L"Geometry2D"));
	shader->DrawWireframeEllipse2D(screenOrtho_, center, xAxis, yAxis, color, sliceCount);
}

void RenderManager::RenderTexture2D(const Texture2D* texture, const Vector2f& center, float width, float height, float rotate, float transparent)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	TextureShader2D* shader = reinterpret_cast<TextureShader2D*>(shaderCache_.at(L"Texture2D"));
	shader->DrawTexture2D(screenOrtho_, texture, center, width, height, rotate, transparent);
}

void RenderManager::RenderTexture2D(const Texture2D* texture, float transparent)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	TextureShader2D* shader = reinterpret_cast<TextureShader2D*>(shaderCache_.at(L"Texture2D"));
	shader->DrawTexture2D(texture, transparent);
}

void RenderManager::RenderHorizonScrollTexture2D(const Texture2D* texture, float rate, float transparent)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	TextureShader2D* shader = reinterpret_cast<TextureShader2D*>(shaderCache_.at(L"Texture2D"));
	shader->DrawHorizonScrollTexture2D(texture, rate, transparent);
}

void RenderManager::RenderHorizonScrollTexture2D(const Texture2D* texture, const Vector2f& center, float width, float height, float rotate, float rate, float transparent)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	TextureShader2D* shader = reinterpret_cast<TextureShader2D*>(shaderCache_.at(L"Texture2D"));
	shader->DrawHorizonScrollTexture2D(screenOrtho_, texture, center, width, height, rotate, rate, transparent);
}

void RenderManager::RenderVerticalScrollTexture2D(const Texture2D* texture, float rate, float transparent)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	TextureShader2D* shader = reinterpret_cast<TextureShader2D*>(shaderCache_.at(L"Texture2D"));
	shader->DrawVerticalScrollTexture2D(texture, rate, transparent);
}

void RenderManager::RenderVerticalScrollTexture2D(const Texture2D* texture, const Vector2f& center, float width, float height, float rotate, float rate, float transparent)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	TextureShader2D* shader = reinterpret_cast<TextureShader2D*>(shaderCache_.at(L"Texture2D"));
	shader->DrawVerticalScrollTexture2D(screenOrtho_, texture, center, width, height, rotate, rate, transparent);
}

void RenderManager::RenderOutlineTexture2D(const Texture2D* texture, const Vector2f& center, float width, float height, float rotate, const Vector4f& outline, float transparent)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	TextureShader2D* shader = reinterpret_cast<TextureShader2D*>(shaderCache_.at(L"Texture2D"));
	shader->DrawOutlineTexture2D(screenOrtho_, texture, center, width, height, rotate, outline, transparent);
}

void RenderManager::RenderGrid2D(float minX, float maxX, float strideX, float minY, float maxY, float strideY, const Vector4f& color)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	GeometryShader2D* shader = reinterpret_cast<GeometryShader2D*>(shaderCache_.at(L"Geometry2D"));
	shader->DrawGrid2D(screenOrtho_, minX, maxX, strideX, minY, maxY, strideY, color);
}

void RenderManager::RenderText2D(const TTFont* font, const std::wstring& text, const Vector2f& center, const Vector4f& color)
{
	if (bIsEnableDepth_)
	{
		SetDepthMode(false);
	}

	GlyphShader2D* shader = reinterpret_cast<GlyphShader2D*>(shaderCache_.at(L"Glyph2D"));
	shader->DrawText2D(screenOrtho_, font, text, center, color);
}

void RenderManager::RenderPoints3D(const Camera3D* camera, const std::vector<Vector3f>& positions, const Vector4f& color)
{
	if (!bIsEnableDepth_)
	{
		SetDepthMode(true);
	}

	GeometryShader3D* shader = reinterpret_cast<GeometryShader3D*>(shaderCache_.at(L"Geometry3D"));
	shader->DrawPoints3D(camera->GetViewMatrix(), camera->GetProjectionMatrix(), positions, color);
}

void RenderManager::RenderConnectPoints3D(const Camera3D* camera, const std::vector<Vector3f>& positions, const Vector4f& color)
{
	if (!bIsEnableDepth_)
	{
		SetDepthMode(true);
	}

	GeometryShader3D* shader = reinterpret_cast<GeometryShader3D*>(shaderCache_.at(L"Geometry3D"));
	shader->DrawConnectPoints3D(camera->GetViewMatrix(), camera->GetProjectionMatrix(), positions, color);
}

void RenderManager::RenderLine3D(const Camera3D* camera, const Vector3f& fromPosition, const Vector3f& toPosition, const Vector4f& color)
{
	if (!bIsEnableDepth_)
	{
		SetDepthMode(true);
	}

	GeometryShader3D* shader = reinterpret_cast<GeometryShader3D*>(shaderCache_.at(L"Geometry3D"));
	shader->DrawLine3D(camera->GetViewMatrix(), camera->GetProjectionMatrix(), fromPosition, toPosition, color);
}

void RenderManager::RenderLine3D(const Camera3D* camera, const Vector3f& fromPosition, const Vector4f& fromColor, const Vector3f& toPosition, const Vector4f& toColor)
{
	if (!bIsEnableDepth_)
	{
		SetDepthMode(true);
	}

	GeometryShader3D* shader = reinterpret_cast<GeometryShader3D*>(shaderCache_.at(L"Geometry3D"));
	shader->DrawLine3D(camera->GetViewMatrix(), camera->GetProjectionMatrix(), fromPosition, fromColor, toPosition, toColor);
}

void RenderManager::RenderQuad3D(const Matrix4x4f& world, const Camera3D* camera, float width, float height, const Vector4f& color)
{
	if (!bIsEnableDepth_)
	{
		SetDepthMode(true);
	}
	
	GeometryShader3D* shader = reinterpret_cast<GeometryShader3D*>(shaderCache_.at(L"Geometry3D"));
	shader->DrawQuad3D(world, camera->GetViewMatrix(), camera->GetProjectionMatrix(), width, height, color);
}

void RenderManager::RenderHorizonDividQuad3D(const Matrix4x4f& world, const Camera3D* camera, float width, float height, float rate, const Vector4f& color, const Vector4f& bgColor)
{
	if (!bIsEnableDepth_)
	{
		SetDepthMode(true);
	}

	GeometryShader3D* shader = reinterpret_cast<GeometryShader3D*>(shaderCache_.at(L"Geometry3D"));
	shader->DrawHorizonDividQuad3D(world, camera->GetViewMatrix(), camera->GetProjectionMatrix(), width, height, rate, color, bgColor);
}

void RenderManager::RenderVerticalDividQuad3D(const Matrix4x4f& world, const Camera3D* camera, float width, float height, float rate, const Vector4f& color, const Vector4f& bgColor)
{
	if (!bIsEnableDepth_)
	{
		SetDepthMode(true);
	}

	GeometryShader3D* shader = reinterpret_cast<GeometryShader3D*>(shaderCache_.at(L"Geometry3D"));
	shader->DrawVerticalDividQuad3D(world, camera->GetViewMatrix(), camera->GetProjectionMatrix(), width, height, rate, color, bgColor);
}

void RenderManager::RenderAxisAlignedBoundingBox3D(const Camera3D* camera, const Vector3f& center, const Vector3f& extents, const Vector4f& color)
{
	if (!bIsEnableDepth_)
	{
		SetDepthMode(true);
	}

	GeometryShader3D* shader = reinterpret_cast<GeometryShader3D*>(shaderCache_.at(L"Geometry3D"));
	shader->DrawAxisAlignedBoundingBox3D(camera->GetViewMatrix(), camera->GetProjectionMatrix(), center, extents, color);
}

void RenderManager::RenderWireframeSphere3D(const Camera3D* camera, const Vector3f& center, float radius, const Vector4f& color, int32_t sliceCount)
{
	if (!bIsEnableDepth_)
	{
		SetDepthMode(true);
	}

	GeometryShader3D* shader = reinterpret_cast<GeometryShader3D*>(shaderCache_.at(L"Geometry3D"));
	shader->DrawWireframeSphere3D(camera->GetViewMatrix(), camera->GetProjectionMatrix(), center, radius, color, sliceCount);
}

void RenderManager::RenderGrid3D(const Camera3D* camera, float minX, float maxX, float strideX, float minZ, float maxZ, float strideZ, const Vector4f& color)
{
	if (!bIsEnableDepth_)
	{
		SetDepthMode(true);
	}

	GeometryShader3D* shader = reinterpret_cast<GeometryShader3D*>(shaderCache_.at(L"Geometry3D"));
	shader->DrawGrid3D(camera->GetViewMatrix(), camera->GetProjectionMatrix(), minX, maxX, strideX, minZ, maxZ, strideZ, color);
}

void RenderManager::RenderSkybox3D(const Camera3D* camera, const Skybox* skybox)
{
	if (!bIsEnableDepth_)
	{
		SetDepthMode(true);
	}

	Shader* shader = reinterpret_cast<Shader*>(shaderCache_.at(L"Skybox"));
	shader->Bind();
	GL_ASSERT(glDepthFunc(GL_LEQUAL), "failed to set depth test GL_LEQUAL function...");

	shader->SetUniform("view", camera->GetViewMatrix());
	shader->SetUniform("projection", camera->GetProjectionMatrix());

	skybox->Active(0);

	GL_ASSERT(glBindVertexArray(skybox->GetVertexArrayObject()), "failed to bind skybox vertex array...");
	GL_ASSERT(glDrawArrays(GL_TRIANGLES, 0, skybox->GetVertexCount()), "failed to draw skybox...");
	GL_ASSERT(glBindVertexArray(0), "failed to unbind skybox vertex array...");

	GL_ASSERT(glDepthFunc(GL_LESS), "failed to set depth test GL_LESS function...");
	shader->Unbind();
}