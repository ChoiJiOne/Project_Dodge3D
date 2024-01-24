#pragma once

#include "GameObject.h"
#include "Sphere3D.h"
#include "Vector3.h"

class Sound;


/**
 * @brief 플레이어가 피해야 할 총알 오브젝트입니다.
 */
class Bullet : public GameObject
{
public:
	/**
	 * @brief 플레이어가 피해야 할 총알 오브젝트의 기본 생성자입니다.
	 *
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	Bullet() = default;


	/**
	 * @brief 플레이어가 피해야 할 총알 오브젝트의 가상 소멸자입니다.
	 */
	virtual ~Bullet();

	
	/**
	 * @brief 플레이어가 피해야 할 총알 오브젝트의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Bullet);


	/**
	 * @brief 플레이어가 피해야 할 총알 오브젝트를 초기화합니다.
	 *
	 * @param location 총알 오브젝트의 월드 상 위치입니다.
	 * @param direction 총알의 방향입니다.
	 * @param speed 총알의 속력입니다.
	 * @param boundRadius 총알의 경계 구 반지름 길이입니다.
	 */
	void Initialize(const Vector3f& location, const Vector3f& direction, float speed, float boundRadius);


	/**
	 * @brief 플레이어가 피해야 할 총알 오브젝트를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 플레이어가 피해야 할 총알 오브젝트 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 총알 오브젝트의 경계 영역을 얻습니다.
	 * 
	 * @return 총알 오브젝트의 경계 영역을 반환합니다.
	 */
	virtual const IShape3D* GetBoundingVolume() const override { return &boundingVolume_; }


	/**
	 * @brief 총알이 벽과 충돌했는지 확인합니다.
	 * 
	 * @return 총알이 벽과 충돌했다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsCollisionToWall() const { return bIsCollisionToWall_; }


	/**
	 * @brief 총알이 플레이어와 충돌했는지 확인합니다.
	 * 
	 * @return 총알이 플레이어와 충돌했다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsCollisionToPlayer() const { return bIsCollisionToPlayer_; }


private:
	/**
	 * @brief 벽과 충돌하는지 확인합니다.
	 * 
	 * @return 벽과 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool CheckCollisionToWall();


	/**
	 * @brief 플레이어와 충돌하는지 확인합니다.
	 * 
	 * @return 플레이어와 충돌한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool CheckCollisionToPlayer();


private:
	/**
	 * @brief 총알의 방향입니다.
	 */
	Vector3f direction_;


	/**
	 * @brief 총알의 속력입니다.
	 */
	float speed_;


	/**
	 * @brief 총알의 경계 영역입니다.
	 */
	Sphere3D boundingVolume_;


	/**
	 * @brief 총알이 벽과 충돌했는지 확인합니다.
	 */
	bool bIsCollisionToWall_ = false;


	/**
	 * @brief 총알이 플레이어와 충돌했는지 확인합니다.
	 */
	bool bIsCollisionToPlayer_ = false;


	/**
	 * @brief 총알이 충돌했을 때 출력할 사운드입니다.
	 */
	Sound* hitSound_ = nullptr;
};