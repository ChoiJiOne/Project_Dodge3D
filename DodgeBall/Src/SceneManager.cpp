#include "SceneManager.h"

#include "Assertion.h"

void SceneManager::Startup()
{
	ASSERT(!bIsStartup_, "already startup scene manager...");

	scenes_ = std::unordered_map<std::string, std::unique_ptr<IScene>>();

	bIsStartup_ = true;
}

void SceneManager::Shutdown()
{
	ASSERT(bIsStartup_, "not startup before or has already been shutdowned...");

	for (auto& scene : scenes_)
	{
		scene.second.reset();
	}

	bIsStartup_ = false;
}

void SceneManager::DestroyScene(const std::string& signature)
{
	if (IsValidSceneKey(signature))
	{
		scenes_.erase(signature);
	}
}

bool SceneManager::IsValidSceneKey(const std::string& signature)
{
	return scenes_.find(signature) != scenes_.end();
}
