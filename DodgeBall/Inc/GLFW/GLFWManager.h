#pragma once

#include <glfw/glfw3.h>

#include "Utils/Macro.h"

/**
 * GLFW ���� ó���� �����ϴ� �Ŵ����Դϴ�.
 * �̶�, �� �Ŵ��� Ŭ������ �̱����Դϴ�.
 */
class GLFWManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(GLFWManager);

	/** GLFW �Ŵ����� �̱��� ��ü �����ڸ� ����ϴ�. */
	static GLFWManager& GetRef();

	/** GLFW �Ŵ����� �̱��� ��ü �����͸� ����ϴ�. */
	static GLFWManager* GetPtr();

private:
	/**
	 * GLFW �Ŵ����� �⺻ �����ڿ� �� ���� �Ҹ����Դϴ�.
	 * �̱������� �����ϱ� ���� private���� ������ϴ�.
	 */
	GLFWManager() = default;
	virtual ~GLFWManager() {}

private:
	/** GLFW �Ŵ����� �̱��� ��ü�Դϴ�. */
	static GLFWManager singleton_;
};