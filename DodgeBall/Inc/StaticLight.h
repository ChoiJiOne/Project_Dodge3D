#pragma once

#include "Light.h"


/**
 * @brief 정적 라이트입니다.
 */
class StaticLight : public Light
{
public:
	/**
	 * @brief 정적 라이트의 디폴트 생성자입니다.
	 *
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	StaticLight() = default;


	/**
	 * @brief 정적 라이트의 가상 소멸자입니다.
	 *
	 * @note 게임 오브젝트 내부에서 할당된 리소스를 해제하기 위해서는 Release 메서드를 호출해야 합니다.
	 */
	virtual ~StaticLight();


	/**
	 * @brief 정적 라이트의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(StaticLight);


	/**
	 * @brief 정적 라이트를 초기화합니다.
	 */
	void Initialize();


	/**
	 * @brief 정적 라이트를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 정적 라이트 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;
};