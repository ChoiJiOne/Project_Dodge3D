#pragma once

#include "Macro.h"


/**
 * @brief 씬 인터페이스입니다.
 * 
 * @note 게임 내의 씬은 모두 이 인터페이스를 상속받아야 합니다.
 */
class IScene
{
public:
	/**
	 * @brief 씬의 디폴트 생성자입니다.
	 */
	IScene() = default;


	/**
	 * @brief 씬의 가상 소멸자입니다.
	 */
	virtual ~IScene() {}


	/**
	 * @brief 씬의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(IScene);


	/**
	 * @brief 씬의 한 프레임을 진행합니다.
	 *
	 * @param deltaSeconds 델타 시간값입니다.
	 */
	virtual void Tick(float deltaSeconds) = 0;
};