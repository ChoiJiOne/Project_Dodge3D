#pragma once

#include <string>

/**
 * GLFW 에러를 처리하는 클래스입니다.
 * 이때, 이 클래스의 모든 멤버 변수와 메서드는 정적(static) 타입입니다.
 */
class GLFWError
{
public:
	/** 에러 발생 여부를 확인합니다. */
	static bool IsDetectError() { return bIsDetectError_; }

	/** GLFW 에러에 대한 코드 값을 얻습니다. */
	static const int32_t GetErrorCode() { return errorCode_; }

	/** GLFW 에러에 대한 설명을 C 스타일 문자열로 얻습니다. */
	static const char* GetErrorDescription() { return errorDescription_.c_str(); }

	/** GLFW 에러에 대한 메시지를 C 스타일 문자열로 얻습니다. */
	static const char* GetErrorMessage() { return errorMessage_.c_str(); }

private:
	/** GLFW 매니저에서 GLFW Error의 내부에 접근할 수 있도록 설정합니다. */
	friend class GLFWManager;

	/**
	 * 최근에 발생한 GLFW 에러를 설정합니다.
	 * 단, 이 메서드는 GLFW 매니저 내부에서만 사용합니다.
	 */
	static void SetLastError(int32_t code, const char* description);

private:
	/** GLFW 에러 감지 여부를 확인합니다. */
	static bool bIsDetectError_;

	/**
	 * GLFW 에러 코드입니다.
	 * 참조: https://www.glfw.org/docs/3.3/group__errors.html
	 */
	static int32_t errorCode_;

	/** GLFW 에러에 대한 설명입니다. */
	static std::string errorDescription_;

	/** GLFW 에러 메시지입니다. */
	static std::string errorMessage_;
};