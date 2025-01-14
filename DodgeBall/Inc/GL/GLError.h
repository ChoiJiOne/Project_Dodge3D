#pragma once

#include <map>
#include <string>

/**
 * OpenGL 에러를 처리하는 클래스입니다.
 * 이때, 이 클래스의 모든 멤버 변수와 메서드는 정적(static) 타입입니다.
 */
class GLError
{
public:
	/** OpenGL 에러 코드에 대응하는 에러 메시지를 C 스타일로 얻습니다. */
	static const char* GetMessage(uint32_t code);

private:
	/** GL 매니저에서 GL 에러 내부에 접근할 수 있도록 설정합니다. */
	friend class GLManager;

private:
	/** OpenGL 에러 코드에 대응하는 에러 메시지입니다. */
	static std::map<uint32_t, std::string> errorMessages_;
};