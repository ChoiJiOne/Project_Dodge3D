#pragma once

#include "GL/GLError.h"
#include "Utils/Utils.h"

#if defined(DEBUG_MODE) || defined(RELWITHDEBINFO_MODE)
/**
 * 이 매크로는 OpenGL API의 호출 결과 평가식을 검사하고, 평가식을 만족하지 않으면 break를 겁니다.
 * ex)
 * uint32_t shaderID = glCreateShader(...);
 * GL_EXP_CHECK(shaderID != 0);
 */
#ifndef GL_EXP_CHECK 
#define GL_EXP_CHECK(EXP)\
{\
	if (!(bool)(EXP))\
	{\
		GLenum _errorCode = glGetError();\
		DebugPrintF("\nAssertion check point failed!\n> File: %s\n> Line: %d\n> Function: %s\n> Expression: %s\n", __FILE__, __LINE__, __FUNCTION__, #EXP);\
		DebugPrintF("> Code: %d\n> Error: %s\n\n", static_cast<int32_t>(_errorCode), GLError::GetMessage(_errorCode));\
		__debugbreak();\
	}\
}
#endif
/**
 * 이 매크로는 OpenGL API의 API 호출 결과를 검사하고, 평가식을 만족하지 않으면 break를 겁니다.
 * 주로, 반환 값이 없는 API를 대상으로 합니다.
 * ex)
 * GL_API_CHECK(glBindBuffer(...));
 */
#ifndef GL_API_CHECK
#define GL_API_CHECK(EXP)\
{\
	EXP;\
	GLenum _errorCode = glGetError();\
	if (_errorCode != GL_NO_ERROR)\
	{\
		DebugPrintF("\nAssertion check point failed!\n> File: %s\n> Line: %d\n> Function: %s\n> Expression: %s\n", __FILE__, __LINE__, __FUNCTION__, #EXP);\
		DebugPrintF("> Code: %d\n> Error: %s\n\n", static_cast<int32_t>(_errorCode), GLError::GetMessage(_errorCode));\
		__debugbreak();\
	}\
}
#endif
/**
 * 이 매크로는 OpenGL API 호출 결과 평가식을 검사하고, 평가식을 만족하지 않으면 break를 겁니다.
 * ex)
 * uint32_t shaderID = glCreateShader(...);
 * GL_EXP_ASSERT(shaderID != 0, "Failed to create shader");
 */
#ifndef GL_EXP_ASSERT
#define GL_EXP_ASSERT(EXP, ...)\
{\
	if (!(bool)(EXP))\
	{\
		GLenum _errorCode = glGetError(); \
		DebugPrintF("\nAssertion check point failed!\n> File: %s\n> Line: %d\n> Function: %s\n> Expression: %s\n", __FILE__, __LINE__, __FUNCTION__, #EXP); \
		DebugPrintF("> Code: %d\n> Error: %s\n> Description:", static_cast<int32_t>(_errorCode), GLError::GetMessage(_errorCode)); \
		DebugPrintF(__VA_ARGS__);\
		DebugPrintF("\n\n");\
		__debugbreak(); \
	}\
}
#endif
/**
 * 이 매크로는 OpenGL API의 API 호출 결과를 검사하고, 평가식을 만족하지 않으면 break를 겁니다.
 * 주로, 반환 값이 없는 API를 대상으로 합니다.
 * ex)
 * GL_API_ASSERT(glBindBuffer(...), "Failed to bind buffer");
 */
#ifndef GL_API_ASSERT
#define GL_API_ASSERT(EXP, ...)\
{\
	EXP;\
	GLenum _errorCode = glGetError();\
	if (_errorCode != GL_NO_ERROR)\
	{\
		DebugPrintF("\nAssertion check point failed!\n> File: %s\n> Line: %d\n> Function: %s\n> Expression: %s\n", __FILE__, __LINE__, __FUNCTION__, #EXP); \
		DebugPrintF("> Code: %d\n> Error: %s\n> Description:", static_cast<int32_t>(_errorCode), GLError::GetMessage(_errorCode)); \
		DebugPrintF(__VA_ARGS__);\
		DebugPrintF("\n\n");\
		__debugbreak();\
	}\
}
#endif
#else // defined(RELEASE_MODE) || defined(MINSIZEREL_MODE)
#ifndef GL_EXP_CHECK 
#define GL_EXP_CHECK(EXP) (void)(EXP)
#endif
#ifndef GL_API_CHECK
#define GL_API_CHECK(EXP) (void)(EXP)
#endif
#ifndef GL_EXP_ASSERT
#define GL_EXP_ASSERT(EXP, ...) (void)(EXP)
#endif
#ifndef GL_API_ASSERT
#define GL_API_ASSERT(EXP, ...) (void)(EXP)
#endif
#endif