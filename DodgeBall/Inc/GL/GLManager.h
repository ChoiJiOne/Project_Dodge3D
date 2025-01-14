#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <glfw/glfw3.h>

#include "GL/GLResource.h"

#include "Utils/Macro.h"

/**
 * OpenGL ���ؽ�Ʈ ���� �� ������ ���� ó���� �����ϴ� �Ŵ����Դϴ�.
 * �̶�, �� �Ŵ��� Ŭ������ �̱����Դϴ�.
 */
class GLManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(GLManager);

	/** GL �Ŵ����� �̱��� ��ü �����ڸ� ����ϴ�. */
	static GLManager& GetRef();

	/** GL �Ŵ����� �̱��� ��ü �����͸� ����ϴ�. */
	static GLManager* GetPtr();

	/** GL �Ŵ����� �ʱ�ȭ�մϴ�. �̶�, GL �Ŵ����� �ʱ�ȭ �ϱ� ���� �ݵ�� GLFW �Ŵ����� �ʱ�ȭ �ؾ� �մϴ�. */
	void Startup();

	/** GL �Ŵ����� �ʱ�ȭ�� �����մϴ�. */
	void Shutdown();

	/** ������ �������� �����մϴ�. */
	void BeginFrame(float red, float green, float blue, float alpha, float depth = 1.0f, uint8_t stencil = 0);

	/** ������ �������� �����մϴ�. */
	void EndFrame();

	/** Viewport�� �����մϴ�. */
	void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);

	/** OpenGL�� ���� ���� �ӽ� ������ �����մϴ�. */
	void SetVsyncMode(bool bIsEnable);
	void SetDepthMode(bool bIsEnable);
	void SetStencilMode(bool bIsEnable);
	void SetAlphaBlendMode(bool bIsEnable);
	void SetCullFaceMode(bool bIsEnable);

	/** OpenGL ���ҽ��� �����մϴ�. */
	template <typename TResource, typename... Args>
	TResource* Create(Args&&... args)
	{
		int32_t resourceID = -1;
		for (uint32_t index = 0; index < resources_.size(); ++index)
		{
			if (!resources_[index].first && !resources_[index].second)
			{
				resourceID = static_cast<int32_t>(index);
				break;
			}
		}

		if (resourceID == -1)
		{
			resourceID = resources_.size();
			resources_.push_back({ nullptr, true });
			resources_[resourceID].first = std::make_unique<TResource>(args...);
		}
		else
		{
			resources_[resourceID].second = true;
			resources_[resourceID].first = std::make_unique<TResource>(args...);
		}

		return reinterpret_cast<TResource*>(resources_[resourceID].first.get());
	}

	/** ������ OpenGL ���ҽ��� �ı��մϴ�. */
	void Destroy(const GLResource* resource);

	/** ���ҽ��� GL �Ŵ����� ����մϴ�. */
	void Register(const std::string& name, GLResource* resource);

	/** ���ҽ� �̸��� ��� �Ǿ����� Ȯ���մϴ�. */
	bool IsRegistration(const std::string& name);

	/** GL �Ŵ����� ����� �����մϴ�. */
	void Unregister(const std::string& name);

	/** �̸��� �����ϴ� ���ҽ��� ����ϴ�. */
	template <typename TResource>
	TResource* GetByName(const std::string& name)
	{
		auto it = namedResources_.find(name);
		if (it == namedResources_.end())
		{
			return nullptr;
		}

		return reinterpret_cast<TResource*>(it->second);
	}

private:
	/**
	 * GL �Ŵ����� �⺻ �����ڿ� �� ���� �Ҹ����Դϴ�.
	 * �̱������� �����ϱ� ���� private���� ������ϴ�.
	 */
	GLManager() = default;
	virtual ~GLManager() {}

private:
	/** GL �Ŵ����� �̱��� ��ü�Դϴ�. */
	static GLManager singleton_;

	/** ������ ����� �Ǵ� �������Դϴ�. */
	GLFWwindow* renderTargetWindow_ = nullptr;

	/** ������ ����� �Ǵ� �������� ����/���� ũ���Դϴ�. */
	int32_t windowWidth_ = 0;
	int32_t windowHeight_ = 0;

	/** OpenGL ���ҽ��� ���ۿ� �ش� ������ ���� ��뿩���Դϴ�. */
	std::vector<std::pair<std::unique_ptr<GLResource>, bool>> resources_;

	/** �̸��� ���� ���ҽ��Դϴ�. */
	std::map<std::string, GLResource*> namedResources_;
};