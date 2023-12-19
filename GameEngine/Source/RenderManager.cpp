#include "RenderManager.h"

#include <glad/glad_wgl.h>
#include <glad/glad.h>

#include "Assertion.h"
#include "Window.h"
#include "WindowsAssertion.h"

void RenderManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup render manager...");
	ASSERT(renderTargetWindow_ != nullptr, "haven't set the render target window...");

	bIsStartup_ = true;
}

void RenderManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");
	
	renderTargetWindow_ = nullptr;
	bIsStartup_ = false;
}