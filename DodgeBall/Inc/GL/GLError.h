#pragma once

#include <map>
#include <string>

/**
 * OpenGL ������ ó���ϴ� Ŭ�����Դϴ�.
 * �̶�, �� Ŭ������ ��� ��� ������ �޼���� ����(static) Ÿ���Դϴ�.
 */
class GLError
{
public:
	/** OpenGL ���� �ڵ忡 �����ϴ� ���� �޽����� C ��Ÿ�Ϸ� ����ϴ�. */
	static const char* GetMessage(uint32_t code);

private:
	/** GL �Ŵ������� GL ���� ���ο� ������ �� �ֵ��� �����մϴ�. */
	friend class GLManager;

private:
	/** OpenGL ���� �ڵ忡 �����ϴ� ���� �޽����Դϴ�. */
	static std::map<uint32_t, std::string> errorMessages_;
};