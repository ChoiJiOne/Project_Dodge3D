#pragma once

#include <string>
#include <vector>

#include "GL/GLResource.h"

/** OpenGL 셰이더 프로그램 리소스입니다. */
class Shader : public GLResource
{
public:
	/** 생성자의 표준 문자열은 모두 셰이더의 소스 코드입니다. 소스 파일 경로 아닙니다. */
	Shader(const std::string& csSource);
	Shader(const std::string& vsSource, const std::string& fsSource);
	Shader(const std::string& vsSource, const std::string& gsSource, const std::string& fsSource);

	virtual ~Shader();

	DISALLOW_COPY_AND_ASSIGN(Shader);

	virtual void Release() override;

	/** 셰이더 프로그램을 렌더링 파이프라인에 바인딩합니다. */
	void Bind();

	/** 바인딩된 셰이더 프로그램을 바인딩 해제합니다. */
	void Unbind();

private:
	/** 셰이더의 종류입니다. */
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