#pragma once

#include "Utils/Macro.h"

/**
 * OpenGL 리소스 인터페이스입니다.
 * 이때, OpenGL 리소스(버텍스 버퍼, 인덱스 버퍼, 셰이더, 텍스처, 프레임 버퍼 등등)는 반드시 이 인터페이스를 상속받아야 합니다.
 */
class GLResource
{
public:
	GLResource();
	virtual ~GLResource();

	DISALLOW_COPY_AND_ASSIGN(GLResource);

	virtual void Release() = 0;

	bool IsInitialized() const { return bIsInitialized_; }

protected:
	bool bIsInitialized_ = false;
};