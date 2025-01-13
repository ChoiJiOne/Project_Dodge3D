#pragma once

#include "GLFW/GLFWError.h"
#include "Utils/Utils.h"

#if defined(DEBUG_MODE) || defined(RELWITHDEBINFO_MODE)
/**
 * �� ��ũ�δ� GLFW API�� ȣ�� ��� �򰡽��� �˻��մϴ�.
 * ex)
 * GLFWwindow* window = glfwCreateWindow(...);
 * GLFW_EXP_CHECK(window != nullptr);
 */
#ifndef GLFW_EXP_CHECK
#define GLFW_EXP_CHECK(EXP)\
{\
	if (!(bool)(EXP))\
	{\
		DebugPrintF("\nAssertion check point failed!\n> File: %s\n> Line: %d\n> Function: %s\n> Expression: %s\n", __FILE__, __LINE__, __FUNCTION__, #EXP);\
		DebugPrintF("> Code: %d\n> Error: %s\n> Description: %s\n\n", GLFWError::GetErrorCode(),  GLFWError::GetErrorMessage(),  GLFWError::GetErrorDescription());\
		__debugbreak();\
	}\
}
#endif
/**
 * �� ��ũ�δ� GLFW API�� API ȣ�� ����� �˻��մϴ�. �ַ�, ��ȯ ���� ���� API�� ������� �մϴ�.
 * ex)
 * GLFW_API_CHECK(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_MAJOR_VERSION));
 */
#ifndef GLFW_API_CHECK
#define GLFW_API_CHECK(EXP)\
{\
	EXP;\
	if (GLFWError::IsDetectError())\
	{\
		DebugPrintF("\nAssertion check point failed!\n> File: %s\n> Line: %d\n> Function: %s\n> Expression: %s\n", __FILE__, __LINE__, __FUNCTION__, #EXP);\
		DebugPrintF("> Code: %d\n> Error: %s\n> Description: %s\n\n", GLFWError::GetErrorCode(),  GLFWError::GetErrorMessage(),  GLFWError::GetErrorDescription());\
		__debugbreak();\
	}\
}
#endif
#else // defined(RELEASE_MODE) || defined(MINSIZEREL_MODE)
#ifndef GLFW_EXP_CHECK
#define GLFW_EXP_CHECK(EXP) (void)(EXP)
#endif
#ifndef GLFW_API_CHECK
#define GLFW_API_CHECK(EXP) (void)(EXP)
#endif
#endif