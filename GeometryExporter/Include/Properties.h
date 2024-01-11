#pragma once

#include "IObject.h"

#include "DirectionalLight.h"

class Material; // 매터리얼을 사용하기 위한 전방선언입니다.


/**
 * @brief 사용자 제어 가능한 속성입니다.
 */
class Properties : public IObject
{
public:
	/**
	 * @brief 제어 가능한 속성의 디폴트 생성자입니다.
	 */
	Properties() = default;


	/**
	 * @brief 제어 가능한 속성의 가상 소멸자입니다.
	 */
	virtual ~Properties();


	/**
	 * @brief 제어 가능한 속성의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Properties);


	/**
	 * @brief 제어 가능한 속성을 초기화합니다.
	 */
	void Initialize();


	/**
	 * @brief 제어 가능한 속성을 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 *
	 * @note 델타 시간 값은 초단위입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 오브젝트 내의 리소스를 할당 해제합니다.
	 *
	 * @note 오브젝트 인터페이스를 상속받는 하위 클래스에서 반드시 구현해야 합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 제어 가능한 속성의 직선광을 얻습니다.
	 * 
	 * @return 제어 가능한 속성의 직선광 객체 상수 참조자를 반환합니다.
	 */
	const DirectionalLight& GetDirectionalLight() const { return directionalLight_; }


private:
	/**
	 * @brief 제어 가능한 직선광입니다.
	 */
	DirectionalLight directionalLight_;


	/**
	 * @brief 직선광의 방향입니다. 범위는 -1.0 ~ 1.0입니다.
	 */
	Vector3f lightDirection_;


	/**
	 * @brief 주변광의 RGB 색상입니다.
	 */
	Vector3f lightAmbientRGB_;


	/**
	 * @brief 분산광의 RGB 색상입니다.
	 */
	Vector3f lightDiffuseRGB_;


	/**
	 * @brief 반사광의 RGB 색상입니다.
	 */
	Vector3f lightSpecularRGB_;
};