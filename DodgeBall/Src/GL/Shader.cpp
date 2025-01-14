#include <glad/glad.h>

#include "GL/GLAssert.h"
#include "GL/Shader.h"
#include "Utils/Assertion.h"

static const uint32_t MAX_STRING_BUFFER = 1024;

Shader::Shader(const std::string& csSource)
{
	uint32_t csID = CreateShader(EType::COMPUTE, reinterpret_cast<const char*>(csSource.data()));
	GL_EXP_CHECK(csID != 0);

	std::vector<uint32_t> shaderIDs = { csID };
	programID_ = CreateProgram(shaderIDs);
	GL_EXP_CHECK(programID_ != 0);

	GL_API_CHECK(glDeleteShader(csID));

	bIsInitialized_ = true;
}

Shader::Shader(const std::string& vsSource, const std::string& fsSource)
{
	uint32_t vsID = CreateShader(EType::VERTEX, reinterpret_cast<const char*>(vsSource.data()));
	GL_EXP_CHECK(vsID != 0);

	uint32_t fsID = CreateShader(EType::FRAGMENT, reinterpret_cast<const char*>(fsSource.data()));
	GL_EXP_CHECK(fsID != 0);

	std::vector<uint32_t> shaderIDs = { vsID, fsID };
	programID_ = CreateProgram(shaderIDs);
	GL_EXP_CHECK(programID_ != 0);

	GL_API_CHECK(glDeleteShader(vsID));
	GL_API_CHECK(glDeleteShader(fsID));

	bIsInitialized_ = true;
}

Shader::Shader(const std::string& vsSource, const std::string& gsSource, const std::string& fsSource)
{
	uint32_t vsID = CreateShader(EType::VERTEX, reinterpret_cast<const char*>(vsSource.data()));
	GL_EXP_CHECK(vsID != 0);

	uint32_t gsID = CreateShader(EType::GEOMETRY, reinterpret_cast<const char*>(gsSource.data()));
	GL_EXP_CHECK(gsID != 0);

	uint32_t fsID = CreateShader(EType::FRAGMENT, reinterpret_cast<const char*>(fsSource.data()));
	GL_EXP_CHECK(fsID != 0);

	std::vector<uint32_t> shaderIDs = { vsID, gsID, fsID };
	programID_ = CreateProgram(shaderIDs);
	GL_EXP_CHECK(programID_ != 0);

	GL_API_CHECK(glDeleteShader(vsID));
	GL_API_CHECK(glDeleteShader(gsID));
	GL_API_CHECK(glDeleteShader(fsID));

	bIsInitialized_ = true;
}

Shader::~Shader()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Shader::Release()
{
	CHECK(bIsInitialized_);

	if (programID_) /** 셰이더 프로그램이 할당에 성공했다면 0이 아닌 값이 할당됨. */
	{
		GL_API_CHECK(glDeleteProgram(programID_));
		programID_ = 0;
	}

	bIsInitialized_ = false;
}

void Shader::Bind()
{
	GL_API_CHECK(glUseProgram(programID_));
}

void Shader::Unbind()
{
	GL_API_CHECK(glUseProgram(0));
}

uint32_t Shader::CreateShader(const EType& type, const char* sourcePtr)
{
	uint32_t shaderID = glCreateShader(static_cast<GLenum>(type));
	GL_EXP_CHECK(shaderID != 0);

	GL_API_CHECK(glShaderSource(shaderID, 1, &sourcePtr, nullptr));
	GL_API_CHECK(glCompileShader(shaderID));

	int32_t status;
	GL_API_CHECK(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status));
	if (!status)
	{
		char buffer[MAX_STRING_BUFFER];

		GL_API_CHECK(glGetShaderInfoLog(shaderID, MAX_STRING_BUFFER, nullptr, buffer));
		ASSERT(false, "Failed to compile shader\n%s", buffer);
	}

	return shaderID;
}

uint32_t Shader::CreateProgram(const std::vector<uint32_t>& shaderIDs)
{
	CHECK(shaderIDs.size() > 0);

	uint32_t programID = glCreateProgram();
	GL_EXP_CHECK(programID != 0);

	for (const uint32_t shaderID : shaderIDs)
	{
		GL_API_CHECK(glAttachShader(programID, shaderID));
	}
	GL_API_CHECK(glLinkProgram(programID));

	int32_t status;
	GL_API_CHECK(glGetProgramiv(programID, GL_LINK_STATUS, &status));
	if (!status)
	{
		char buffer[MAX_STRING_BUFFER];

		GL_API_CHECK(glGetProgramInfoLog(programID_, MAX_STRING_BUFFER, nullptr, buffer));
		ASSERT(false, "Failed to link shader program\n%s", buffer);
	}

	return programID;
}