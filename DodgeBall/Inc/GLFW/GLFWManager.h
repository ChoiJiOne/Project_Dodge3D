#pragma once

#include <glfw/glfw3.h>

#include "Utils/Macro.h"

/**
 * --------------------------------------
 * | 이전 프레임 | 현재 프레임 | 입력 상태 |
 * --------------------------------------
 * |     0      |     0      | NONE     |
 * |     0      |     1      | PRESSED  |
 * |     1      |     0      | RELEASED |
 * |     1      |     1      | HELD     |
 * --------------------------------------
 */
enum class EPress : int32_t
{
	NONE     = 0x00,
	PRESSED  = 0x01,
	RELEASED = 0x02,
	HELD     = 0x03
};

/**
 * GLFW 관련 처리를 수행하는 매니저입니다.
 * 이때, 이 매니저 클래스는 싱글턴입니다.
 */
class GLFWManager
{
public:
	DISALLOW_COPY_AND_ASSIGN(GLFWManager);

	/** GLFW 매니저의 싱글턴 객체 참조자를 얻습니다. */
	static GLFWManager& GetRef();

	/** GLFW 매니저의 싱글턴 객체 포인터를 얻습니다. */
	static GLFWManager* GetPtr();

private:
	/**
	 * GLFW 매니저의 기본 생성자와 빈 가상 소멸자입니다.
	 * 싱글턴으로 구현하기 위해 private으로 숨겼습니다.
	 */
	GLFWManager() = default;
	virtual ~GLFWManager() {}

private:
	/** GLFW 매니저의 싱글턴 객체입니다. */
	static GLFWManager singleton_;
};