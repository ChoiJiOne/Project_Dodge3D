#include <glad/glad.h>

#include "GL/GLError.h"

std::map<uint32_t, std::string> GLError::errorMessages_ =
{
	{ GL_NO_ERROR,                      "No error has been recorded. (GL_NO_ERROR)"                                                                              },
	{ GL_INVALID_ENUM,                  "An unacceptable value is specified for an enumerated argument. (GL_INVALID_ENUM)"                                       },
	{ GL_INVALID_VALUE,                 "A numeric argument is out of range. (GL_INVALID_VALUE)"                                                                 },
	{ GL_INVALID_OPERATION,             "The specified operation is not allowed in the current state. (GL_INVALID_OPERATION)"                                    },
	{ GL_INVALID_FRAMEBUFFER_OPERATION, "The framebuffer object is not complete. (GL_INVALID_FRAMEBUFFER_OPERATION)"                                             },
	{ GL_OUT_OF_MEMORY,                 "There is not enough memory left to execute the command. (GL_OUT_OF_MEMORY)"                                             },
	{ GL_STACK_UNDERFLOW,               "An attempt has been made to perform an operation that would cause an internal stack to underflow. (GL_STACK_UNDERFLOW)" },
	{ GL_STACK_OVERFLOW,                "An attempt has been made to perform an operation that would cause an internal stack to overflow. (GL_STACK_OVERFLOW)"   },
	{ GL_CONTEXT_LOST,                  "This occurs when the OpenGL context becomes lost due to a graphics card reset. (GL_CONTEXT_LOST)"                       },
	{ GL_NONE,                          "Undefined error message."                                                                                               },
};

const char* GLError::GetMessage(uint32_t code)
{
	return errorMessages_.at(code).c_str();
}
