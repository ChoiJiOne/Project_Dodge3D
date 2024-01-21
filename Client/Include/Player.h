#pragma once

#include "GameObject.h"
#include "Sphere3D.h"

class Camera3D;


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


	/**
	 * @brief 플레이어의 현재 HP를 얻습니다.
	 * 
	 * @return 플레이어의 현재 HP를 반환합니다.
	 */
	int32_t GetHP() const { return currentHP_; }


	/**
	 * @brief 플레이어의 플레이 시간을 얻습니다.
	 * 
	 * @return 플레이어의 플레이 시간을 반환합니다.
	 */
	float GetPlayTime() const { return playTime_; }


	/**
	 * @brief 플레이어의 HP를 설정합니다.
	 *
	 * @param hp 설정할 플레이어의 HP입니다.
	 */
	void SetHP(int32_t hp);


	/**
	 * @brief 플레이어의 HP를 그립니다.
	 * 
	 * @param camera 3D 카메라입니다.
	 */
	void RenderHP(const Camera3D* camera);
	

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


	/**
	 * @brief 플레이어의 최대 체력입니다.
	 */
	const int32_t maxHP_ = 10;


	/**
	 * @brief 플레이어의 최소 체력입니다.
	 */
	const int32_t minHP_ = 0;


	/**
	 * @brief 플레이어의 HP입니다.
	 * 
	 * @note 이때, 플레이어의 HP는 정해진 범위 값을 벗어날 수 없습니다.
	 */
	int32_t currentHP_ = 0;


	/**
	 * @brief 플레이 타임입니다.
	 */
	float playTime_ = 0.0f;


	/**
	 * @brief 플레이어의 HP를 나타내는 쿼드의 가로 크기입니다.
	 */
	float hpWidth_ = 0.0f;


	/**
	 * @brief 플레이어의 HP를 나타내는 쿼드의 세로 크기입니다.
	 */
	float hpHeight_ = 0.0f;


	/**
	 * @brief 플레이어의 HP 색상입니다.
	 */
	Vector4f hpColor_;


	/**
	 * @brief 플레이어의 HP를 나타내는 쿼드의 백그라운드 색상입니다.
	 */
	Vector4f backgroundColor_;

};