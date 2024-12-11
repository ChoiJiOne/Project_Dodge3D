#include <glad/glad.h>

#include "Assertion.h"
#include "FileUtils.h"
#include "Shader.h"
#include "StringUtils.h"

Shader::~Shader()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Shader::Initialize(const std::wstring& vsPath, const std::wstring& fsPath)
{
	ASSERT(!bIsInitialized_, "already initialize shader resource...");

	uniformLocationCache_ = std::map<std::string, uint32_t>();
	
	std::vector<uint8_t> vsSourceBuffer = FileUtils::ReadBufferFromFile(vsPath);
	std::vector<uint8_t> fsSourceBuffer = FileUtils::ReadBufferFromFile(fsPath);

	std::string vsSource(vsSourceBuffer.begin(), vsSourceBuffer.end());
	std::string fsSource(fsSourceBuffer.begin(), fsSourceBuffer.end());

	uint32_t vsID = CreateAndCompileShader(EType::Vertex, vsSource);
	ASSERT(vsID != 0, L"failed to create and compile %s...", vsPath.c_str());
	
	uint32_t fsID = CreateAndCompileShader(EType::Fragment, fsSource);
	ASSERT(fsID != 0, L"failed to create and compile %s...", fsPath.c_str());

	programID_ = glCreateProgram();
	ASSERT(programID_ != 0, "failed to create shader program...");

	GL_ASSERT(glAttachShader(programID_, vsID), "failed to attach vertex shader in shader program...");
	GL_ASSERT(glAttachShader(programID_, fsID), "failed to attach fragment shader in shader program...");
	GL_ASSERT(glLinkProgram(programID_), "failed to link shader program...");

	int32_t success;
	GL_ASSERT(glGetProgramiv(programID_, GL_LINK_STATUS, &success), "failed to get program link info...");
	if (!success)
	{
		char* buffer = StringUtils::GetCharBufferPtr();

		glGetProgramInfoLog(programID_, StringUtils::STRING_BUFFER_SIZE, nullptr, buffer);
		ASSERT(false, "failed to link shader program : %s", buffer);
	}

	GL_ASSERT(glDeleteShader(vsID), "invalid delete %d shader...", vsID);
	GL_ASSERT(glDeleteShader(fsID), "invalid delete %d shader...", fsID);

	bIsInitialized_ = true;
}

void Shader::Initialize(const std::wstring& vsPath, const std::wstring& gsPath, const std::wstring& fsPath)
{
	ASSERT(!bIsInitialized_, "already initialize shader resource...");

	uniformLocationCache_ = std::map<std::string, uint32_t>();

	std::vector<uint8_t> vsSourceBuffer = FileUtils::ReadBufferFromFile(vsPath);
	std::vector<uint8_t> gsSourceBuffer = FileUtils::ReadBufferFromFile(gsPath);
	std::vector<uint8_t> fsSourceBuffer = FileUtils::ReadBufferFromFile(fsPath);

	std::string vsSource(vsSourceBuffer.begin(), vsSourceBuffer.end());
	std::string gsSource(gsSourceBuffer.begin(), gsSourceBuffer.end());
	std::string fsSource(fsSourceBuffer.begin(), fsSourceBuffer.end());

	uint32_t vsID = CreateAndCompileShader(EType::Vertex, vsSource);
	ASSERT(vsID != 0, L"failed to create and compile %s...", vsPath.c_str());

	uint32_t gsID = CreateAndCompileShader(EType::Geometry, gsSource);
	ASSERT(gsID != 0, L"failed to create and compile %s...", gsPath.c_str());

	uint32_t fsID = CreateAndCompileShader(EType::Fragment, fsSource);
	ASSERT(fsID != 0, L"failed to create and compile %s...", fsPath.c_str());

	programID_ = glCreateProgram();
	ASSERT(programID_ != 0, "failed to create shader program...");

	GL_ASSERT(glAttachShader(programID_, vsID), "failed to attach vertex shader in shader program...");
	GL_ASSERT(glAttachShader(programID_, gsID), "failed to attach geometry shader in shader program...");
	GL_ASSERT(glAttachShader(programID_, fsID), "failed to attach fragment shader in shader program...");
	GL_ASSERT(glLinkProgram(programID_), "failed to link shader program...");

	int32_t success;
	GL_ASSERT(glGetProgramiv(programID_, GL_LINK_STATUS, &success), "failed to get program link info...");
	if (!success)
	{
		char* buffer = StringUtils::GetCharBufferPtr();

		glGetProgramInfoLog(programID_, StringUtils::STRING_BUFFER_SIZE, nullptr, buffer);
		ASSERT(false, "failed to link shader program : %s", buffer);
	}

	GL_ASSERT(glDeleteShader(vsID), "invalid delete %d shader...", vsID);
	GL_ASSERT(glDeleteShader(gsID), "invalid delete %d shader...", gsID);
	GL_ASSERT(glDeleteShader(fsID), "invalid delete %d shader...", fsID);

	bIsInitialized_ = true;
}

void Shader::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	if (programID_ != 0)
	{
		GL_ASSERT(glDeleteProgram(programID_), "failed to delete shader program : %d", programID_);
	}

	bIsInitialized_ = false;
}

void Shader::Bind()
{
	GL_ASSERT(glUseProgram(programID_), "failed to bind shader program...");
}

void Shader::Unbind()
{
	GL_ASSERT(glUseProgram(0), "failed to unbind shader program...");
}

void Shader::SetUniform(const std::string& name, bool value)
{
	int32_t location = -1;
	std::map<std::string, uint32_t>::iterator uniformLocation = uniformLocationCache_.find(name);
	if (uniformLocation == uniformLocationCache_.end())
	{
		location = GetUniformLocation(name);
		uniformLocationCache_.insert({ name, location });
	}
	else
	{
		location = uniformLocation->second;
	}

	GL_ASSERT(glUniform1i(location, static_cast<int32_t>(value)), "failed to set bool type uniform value : %d", static_cast<int32_t>(value));
}

void Shader::SetUniform(const std::string& name, int32_t value)
{
	int32_t location = -1;
	std::map<std::string, uint32_t>::iterator uniformLocation = uniformLocationCache_.find(name);
	if (uniformLocation == uniformLocationCache_.end())
	{
		location = GetUniformLocation(name);
		uniformLocationCache_.insert({ name, location });
	}
	else
	{
		location = uniformLocation->second;
	}

	GL_ASSERT(glUniform1i(location, static_cast<int32_t>(value)), "faild to set int type uniform value : %d", static_cast<int32_t>(value));
}

void Shader::SetUniform(const std::string& name, float value)
{
	int32_t location = -1;
	std::map<std::string, uint32_t>::iterator uniformLocation = uniformLocationCache_.find(name);
	if (uniformLocation == uniformLocationCache_.end())
	{
		location = GetUniformLocation(name);
		uniformLocationCache_.insert({ name, location });
	}
	else
	{
		location = uniformLocation->second;
	}

	GL_ASSERT(glUniform1f(location, value), "failed to set float type uniform value : %f", value);
}

void Shader::SetUniform(const std::string& name, const Vector2f& value)
{
	int32_t location = -1;
	std::map<std::string, uint32_t>::iterator uniformLocation = uniformLocationCache_.find(name);
	if (uniformLocation == uniformLocationCache_.end())
	{
		location = GetUniformLocation(name);
		uniformLocationCache_.insert({ name, location });
	}
	else
	{
		location = uniformLocation->second;
	}

	const float* valuePtr = value.GetPtr();
	GL_ASSERT(glUniform2fv(location, 1, valuePtr), "failed to set Vector2f type uniform value : (%f, %f)", value.x, value.y);
}

void Shader::SetUniform(const std::string& name, float x, float y)
{
	int32_t location = -1;
	std::map<std::string, uint32_t>::iterator uniformLocation = uniformLocationCache_.find(name);
	if (uniformLocation == uniformLocationCache_.end())
	{
		location = GetUniformLocation(name);
		uniformLocationCache_.insert({ name, location });
	}
	else
	{
		location = uniformLocation->second;
	}

	GL_ASSERT(glUniform2f(location, x, y), "failed to set Vector2f type uniform value : (%f, %f)", x, y);
}

void Shader::SetUniform(const std::string& name, const Vector2i& value)
{
	int32_t location = -1;
	std::map<std::string, uint32_t>::iterator uniformLocation = uniformLocationCache_.find(name);
	if (uniformLocation == uniformLocationCache_.end())
	{
		location = GetUniformLocation(name);
		uniformLocationCache_.insert({ name, location });
	}
	else
	{
		location = uniformLocation->second;
	}

	const int32_t* valuePtr = value.GetPtr();
	GL_ASSERT(glUniform2iv(location, 1, valuePtr), "failed to set Vector2i type uniform value : (%d, %d)", value.x, value.y);
}

void Shader::SetUniform(const std::string& name, int32_t x, int32_t y)
{
	int32_t location = -1;
	std::map<std::string, uint32_t>::iterator uniformLocation = uniformLocationCache_.find(name);
	if (uniformLocation == uniformLocationCache_.end())
	{
		location = GetUniformLocation(name);
		uniformLocationCache_.insert({ name, location });
	}
	else
	{
		location = uniformLocation->second;
	}

	GL_ASSERT(glUniform2i(location, x, y), "failed to set Vector2i type uniform value : (%d, %d)", x, y);
}

void Shader::SetUniform(const std::string& name, const Vector3f& value)
{
	int32_t location = -1;
	std::map<std::string, uint32_t>::iterator uniformLocation = uniformLocationCache_.find(name);
	if (uniformLocation == uniformLocationCache_.end())
	{
		location = GetUniformLocation(name);
		uniformLocationCache_.insert({ name, location });
	}
	else
	{
		location = uniformLocation->second;
	}

	const float* valuePtr = value.GetPtr();
	GL_ASSERT(glUniform3fv(location, 1, valuePtr), "failed to set Vector3f type uniform value : (%f, %f, %f)", value.x, value.y, value.z);
}

void Shader::SetUniform(const std::string& name, float x, float y, float z)
{
	int32_t location = -1;
	std::map<std::string, uint32_t>::iterator uniformLocation = uniformLocationCache_.find(name);
	if (uniformLocation == uniformLocationCache_.end())
	{
		location = GetUniformLocation(name);
		uniformLocationCache_.insert({ name, location });
	}
	else
	{
		location = uniformLocation->second;
	}

	GL_ASSERT(glUniform3f(location, x, y, z), "failed to set Vector3f type uniform value : (%f, %f, %f)", x, y, z);
}

void Shader::SetUniform(const std::string& name, const Vector3i& value)
{
	int32_t location = -1;
	std::map<std::string, uint32_t>::iterator uniformLocation = uniformLocationCache_.find(name);
	if (uniformLocation == uniformLocationCache_.end())
	{
		location = GetUniformLocation(name);
		uniformLocationCache_.insert({ name, location });
	}
	else
	{
		location = uniformLocation->second;
	}

	const int32_t* valuePtr = value.GetPtr();
	GL_ASSERT(glUniform3iv(location, 1, valuePtr), "failed to set Vector3i type uniform value : (%d, %d, %d)", value.x, value.y, value.z);
}

void Shader::SetUniform(const std::string& name, int32_t x, int32_t y, int32_t z)
{
	int32_t location = -1;
	std::map<std::string, uint32_t>::iterator uniformLocation = uniformLocationCache_.find(name);
	if (uniformLocation == uniformLocationCache_.end())
	{
		location = GetUniformLocation(name);
		uniformLocationCache_.insert({ name, location });
	}
	else
	{
		location = uniformLocation->second;
	}

	GL_ASSERT(glUniform3i(location, x, y, z), "failed to set Vector3i type uniform value : (%d, %d, %d)", x, y, z);
}

void Shader::SetUniform(const std::string& name, const Vector4f& value)
{
	int32_t location = -1;
	std::map<std::string, uint32_t>::iterator uniformLocation = uniformLocationCache_.find(name);
	if (uniformLocation == uniformLocationCache_.end())
	{
		location = GetUniformLocation(name);
		uniformLocationCache_.insert({ name, location });
	}
	else
	{
		location = uniformLocation->second;
	}

	const float* valuePtr = value.GetPtr();
	GL_ASSERT(glUniform4fv(location, 1, valuePtr), "failed to set Vector4f type uniform value : (%f, %f, %f, %f)", value.x, value.y, value.z, value.w);
}

void Shader::SetUniform(const std::string& name, float x, float y, float z, float w)
{
	int32_t location = -1;
	std::map<std::string, uint32_t>::iterator uniformLocation = uniformLocationCache_.find(name);
	if (uniformLocation == uniformLocationCache_.end())
	{
		location = GetUniformLocation(name);
		uniformLocationCache_.insert({ name, location });
	}
	else
	{
		location = uniformLocation->second;
	}

	GL_ASSERT(glUniform4f(location, x, y, z, w), "failed to set Vector4f type uniform value : (%f, %f, %f, %f)", x, y, z, w);
}

void Shader::SetUniform(const std::string& name, const Vector4i& value)
{
	int32_t location = -1;
	std::map<std::string, uint32_t>::iterator uniformLocation = uniformLocationCache_.find(name);
	if (uniformLocation == uniformLocationCache_.end())
	{
		location = GetUniformLocation(name);
		uniformLocationCache_.insert({ name, location });
	}
	else
	{
		location = uniformLocation->second;
	}

	const int32_t* valuePtr = value.GetPtr();
	GL_ASSERT(glUniform4iv(location, 1, valuePtr), "failed to set Vector4i type uniform value : (%d, %d, %d, %d)", value.x, value.y, value.z, value.w);
}

void Shader::SetUniform(const std::string& name, int32_t x, int32_t y, int32_t z, int32_t w)
{
	int32_t location = -1;
	std::map<std::string, uint32_t>::iterator uniformLocation = uniformLocationCache_.find(name);
	if (uniformLocation == uniformLocationCache_.end())
	{
		location = GetUniformLocation(name);
		uniformLocationCache_.insert({ name, location });
	}
	else
	{
		location = uniformLocation->second;
	}

	GL_ASSERT(glUniform4i(location, x, y, z, w), "failed to set Vector4i type uniform value : (%d, %d, %d, %d)", x, y, z, w);
}

void Shader::SetUniform(const std::string& name, const Matrix2x2f& value)
{
	int32_t location = -1;
	std::map<std::string, uint32_t>::iterator uniformLocation = uniformLocationCache_.find(name);
	if (uniformLocation == uniformLocationCache_.end())
	{
		location = GetUniformLocation(name);
		uniformLocationCache_.insert({ name, location });
	}
	else
	{
		location = uniformLocation->second;
	}

	GL_ASSERT(glUniformMatrix2fv(location, 1, GL_FALSE, value.GetPtr()), "failed to set Matrix2x2f type uniform value...");
}

void Shader::SetUniform(const std::string& name, const Matrix3x3f& value)
{
	int32_t location = -1;
	std::map<std::string, uint32_t>::iterator uniformLocation = uniformLocationCache_.find(name);
	if (uniformLocation == uniformLocationCache_.end())
	{
		location = GetUniformLocation(name);
		uniformLocationCache_.insert({ name, location });
	}
	else
	{
		location = uniformLocation->second;
	}

	GL_ASSERT(glUniformMatrix3fv(location, 1, GL_FALSE, value.GetPtr()), "failed to set Matrix3x3f type uniform value...");
}

void Shader::SetUniform(const std::string& name, const Matrix4x4f& value)
{
	int32_t location = -1;
	std::map<std::string, uint32_t>::iterator uniformLocation = uniformLocationCache_.find(name);
	if (uniformLocation == uniformLocationCache_.end())
	{
		location = GetUniformLocation(name);
		uniformLocationCache_.insert({ name, location });
	}
	else
	{
		location = uniformLocation->second;
	}

	GL_ASSERT(glUniformMatrix4fv(location, 1, GL_FALSE, value.GetPtr()), "failed to set Matrix4x4f type uniform value...");
}

int32_t Shader::GetUniformLocation(const std::string& uniformName)
{
	return glGetUniformLocation(programID_, uniformName.c_str());
}

void Shader::WriteDynamicVertexBuffer(uint32_t vertexBufferID, const void* vertexPtr, uint32_t bufferByteSize)
{
	ASSERT(vertexPtr != nullptr, "invalid vertex buffer pointer...");

	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID), "failed to dynamic vertex buffer...");
	void* bufferPtr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	ASSERT(bufferPtr != nullptr, "failed to map the entire data store of a specified buffer object into the client's address space...");
	
	std::memcpy(bufferPtr, vertexPtr, bufferByteSize);
	GLboolean bSuccssed = glUnmapBuffer(GL_ARRAY_BUFFER);
	ASSERT(bSuccssed, "failed to unmap the entire data store of a specified buffer object into the client's address space...");

	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, 0), "failed to unbind dynamic vertex buffer...");
}

uint32_t Shader::CreateAndCompileShader(const EType& type, const std::string& source)
{
	uint32_t shaderType = 0;
	switch (type)
	{
	case EType::Vertex:
		shaderType = GL_VERTEX_SHADER;
		break;

	case EType::Geometry:
		shaderType = GL_GEOMETRY_SHADER;
		break;

	case EType::Fragment:
		shaderType = GL_FRAGMENT_SHADER;
		break;

	default:
		ASSERT(false, "undefined shader type...");
		break;
	}

	const char* sourcePtr = source.c_str();
	uint32_t shaderID = glCreateShader(shaderType);
	ASSERT(shaderID != 0, "failed to create %s shader", type == EType::Vertex ? "Vertex" : "Fragment");

	GL_ASSERT(glShaderSource(shaderID, 1, &sourcePtr, nullptr), "failed to set source code in shader...");
	GL_ASSERT(glCompileShader(shaderID), "failed to compile %s shader...", type == EType::Vertex ? "Vertex" : "Fragment");

	int32_t success;
	GL_ASSERT(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success), "failed to get shader compile status...");
	if (!success)
	{
		char* buffer = StringUtils::GetCharBufferPtr();

		glGetShaderInfoLog(shaderID, StringUtils::STRING_BUFFER_SIZE, nullptr, buffer);
		ASSERT(false, "failed to compile shader : %s", buffer);
	}

	return shaderID;
}