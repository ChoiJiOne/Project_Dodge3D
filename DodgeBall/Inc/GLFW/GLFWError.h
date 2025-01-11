#pragma once

#include <string>

/**
 * GLFW ������ ó���ϴ� Ŭ�����Դϴ�.
 * �̶�, �� Ŭ������ ��� ��� ������ �޼���� ����(static) Ÿ���Դϴ�.
 */
class GLFWError
{
public:
	/** ���� �߻� ���θ� Ȯ���մϴ�. */
	static bool IsDetectError() { return bIsDetectError_; }

	/** GLFW ������ ���� �ڵ� ���� ����ϴ�. */
	static const int32_t GetErrorCode() { return errorCode_; }

	/** GLFW ������ ���� ������ C ��Ÿ�� ���ڿ��� ����ϴ�. */
	static const char* GetErrorDescription() { return errorDescription_.c_str(); }

	/** GLFW ������ ���� �޽����� C ��Ÿ�� ���ڿ��� ����ϴ�. */
	static const char* GetErrorMessage() { return errorMessage_.c_str(); }

private:
	/** GLFW �Ŵ������� GLFW Error�� ���ο� ������ �� �ֵ��� �����մϴ�. */
	friend class GLFWManager;

	/**
	 * �ֱٿ� �߻��� GLFW ������ �����մϴ�.
	 * ��, �� �޼���� GLFW �Ŵ��� ���ο����� ����մϴ�.
	 */
	static void SetLastError(int32_t code, const char* description);

private:
	/** GLFW ���� ���� ���θ� Ȯ���մϴ�. */
	static bool bIsDetectError_;

	/**
	 * GLFW ���� �ڵ��Դϴ�.
	 * ����: https://www.glfw.org/docs/3.3/group__errors.html
	 */
	static int32_t errorCode_;

	/** GLFW ������ ���� �����Դϴ�. */
	static std::string errorDescription_;

	/** GLFW ���� �޽����Դϴ�. */
	static std::string errorMessage_;
};