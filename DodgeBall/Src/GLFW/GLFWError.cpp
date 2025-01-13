#include <glfw/glfw3.h>

#include "GLFW/GLFWError.h"

bool GLFWError::bIsDetectError_ = false;
int32_t GLFWError::errorCode_ = 0;
std::string GLFWError::errorDescription_;
std::string GLFWError::errorMessage_;

void GLFWError::SetLastError(int32_t code, const char* description)
{
	bIsDetectError_ = true;
	errorCode_ = code;
	errorDescription_ = description;

	switch (errorCode_)
	{
	case GLFW_NO_ERROR:
		errorMessage_ = "No error has occurred.";
		break;

	case GLFW_NOT_INITIALIZED:
		errorMessage_ = "GLFW has not been initialized.";
		break;

	case GLFW_NO_CURRENT_CONTEXT:
		errorMessage_ = "No context is current for this thread.";
		break;

	case GLFW_INVALID_ENUM:
		errorMessage_ = "One of the arguments to the function was an invalid enum value.";
		break;

	case GLFW_INVALID_VALUE:
		errorMessage_ = "One of the arguments to the function was an invalid value.";
		break;

	case GLFW_OUT_OF_MEMORY:
		errorMessage_ = "A memory allocation failed.";
		break;

	case GLFW_API_UNAVAILABLE:
		errorMessage_ = "GLFW could not find support for the requested API on the system.";
		break;

	case GLFW_VERSION_UNAVAILABLE:
		errorMessage_ = "The requested OpenGL or OpenGL ES version is not available.";
		break;

	case GLFW_PLATFORM_ERROR:
		errorMessage_ = "A platform-specific error occurred that does not match any of the more specific categories.";
		break;

	case GLFW_FORMAT_UNAVAILABLE:
		errorMessage_ = "The requested format is not supported or available.";
		break;

	case GLFW_NO_WINDOW_CONTEXT:
		errorMessage_ = "The specified window does not have an OpenGL or OpenGL ES context.";
		break;

	default:
		errorMessage_ = "Undefined GLFW error.";
		break;
	}
}