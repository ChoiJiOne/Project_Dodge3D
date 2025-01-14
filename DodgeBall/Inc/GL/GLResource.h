#pragma once

#include "Utils/Macro.h"

/**
 * OpenGL ���ҽ� �������̽��Դϴ�.
 * �̶�, OpenGL ���ҽ�(���ؽ� ����, �ε��� ����, ���̴�, �ؽ�ó, ������ ���� ���)�� �ݵ�� �� �������̽��� ��ӹ޾ƾ� �մϴ�.
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