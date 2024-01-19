#pragma once

#include "GameObject.h"
#include "Sphere3D.h"


/**
 * @brief 플레이어가 조종 가능한 오브젝트입니다.
 */
class Player : public GameObject
{
public:
	/**
	 * @brief 플레이어가 조종 가능한 오브젝트의 기본 생성자입니다.
	 *
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	Player() = default;


	/**
	 * @brief 플레이어가 조종 가능한 오브젝트의 가상 소멸자입니다.
	 */
	virtual ~Player();


	/**
	 * @brief 플레이어가 조종 가능한 오브젝트의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Player);


	/**
	 * @brief 플레이어가 조종 가능한 오브젝트를 초기화합니다.
	 */
	void Initialize();


	/**
	 * @brief 플레이어가 조종 가능한 오브젝트를 업데이트합니다.
	 * 
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 플레이어가 조종 가능한 오브젝트 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 플레이어가 조종 가능한 오브젝트의 경계 영역을 얻습니다.
	 *
	 * @return 플레이어가 조종 가능한 오브젝트의 경계 영역을 반환합니다.
	 */
	virtual const IShape3D* GetBoundingVolume() const override { return &boundingVolume_; }


private:
	/**
	 * @brief 벽과 충돌하는지 확인합니다.
	 *
	 * @return 벽과 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool CheckCollisionToWall();


private:
	/**
	 * @brief 플레이어가 조종 가능한 오브젝트의 경계 영역입니다.
	 */
	Sphere3D boundingVolume_;
};