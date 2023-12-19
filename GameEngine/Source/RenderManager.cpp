#include "RenderManager.h"

#include <glad/glad_wgl.h>
#include <glad/glad.h>

#include "Assertion.h"

std::unique_ptr<RenderManager> RenderManager::renderManager_ = nullptr;

RenderManager& RenderManager::Get()
{
	if (renderManager_ == nullptr)
	{
		renderManager_ = std::make_unique<RenderManager>();
	}

	return *renderManager_.get();
}

RenderManager* RenderManager::GetPtr()
{
	if (renderManager_ == nullptr)
	{
		renderManager_ = std::make_unique<RenderManager>();
	}

	return renderManager_.get();
}

void RenderManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup render manager...");

	bIsStartup_ = true;
}

void RenderManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");
	
	renderManager_.reset();
	renderManager_ = nullptr;
	
	bIsStartup_ = false;
}