#pragma once

#include <string>
#include <vector>

#include "GL/GLResource.h"

/** OpenGL ���̴� ���α׷� ���ҽ��Դϴ�. */
class Shader : public GLResource
{
public:
	/** �������� ǥ�� ���ڿ��� ��� ���̴��� �ҽ� �ڵ��Դϴ�. �ҽ� ���� ��� �ƴմϴ�. */
	Shader(const std::string& csSource);
	Shader(const std::string& vsSource, const std::string& fsSource);
	Shader(const std::string& vsSource, const std::string& gsSource, const std::string& fsSource);

	virtual ~Shader();

	DISALLOW_COPY_AND_ASSIGN(Shader);

	virtual void Release() override;

	/** ���̴� ���α׷��� ������ ���������ο� ���ε��մϴ�. */
	void Bind();

	/** ���ε��� ���̴� ���α׷��� ���ε� �����մϴ�. */
	void Unbind();

private:
	/** ���̴��� �����Դϴ�. */
	enum class EType : int32_t
	{
		VERTEX     = 0x8B31,
		CONTROL    = 0x8E88,
		EVALUATION = 0x8E87,
		GEOMETRY   = 0x8DD9,
		FRAGMENT   = 0x8B30,
		COMPUTE    = 0x91B9,
	};

	uint32_t CreateShader(const EType& type, const char* sourcePtr);
	uint32_t CreateProgram(const std::vector<uint32_t>& shaderIDs);

private:
	uint32_t programID_ = 0;
};