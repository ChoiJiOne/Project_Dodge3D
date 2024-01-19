#pragma once

#include <functional>

#include "GameObject.h"

class Camera3D;


/**
 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트입니다.
 */
class BulletSpawner : public GameObject
{
public:
	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트의 기본 생성자입니다.
	 *
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	BulletSpawner() = default;


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트의 가상 소멸자입니다.
	 */
	virtual ~BulletSpawner();


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(BulletSpawner);


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트를 초기화합니다.
	 * 
	 * @param location 플레이어가 피해야 할 총알을 생성하는 오브젝트의 월드 상 위치입니다. 
	 * @param respawnTime 총알을 생성하는 시간 주기입니다.
	 * @param respawnTrigger 총알 생성 이벤트입니다.
	 */
	void Initialize(const Vector3f& location, float respawnTime, const std::function<void()>& respawnTrigger);


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트를 업데이트합니다.
	 * 
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 오브젝트의 경계 영역을 얻습니다.
	 *
	 * @return 오브젝트의 경계 영역을 반환합니다.
	 */
	virtual const IShape3D* GetBoundingVolume() const override { return nullptr; }


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트의 리스폰 시간을 그립니다.
	 * 
	 * @param camera 3D 카메라입니다.
	 */
	void RenderRespawnTime(const Camera3D* camera);


private:
	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트의 누적 시간입니다.
	 */
	float stepTime_ = 0.0f;


	/**
	 * @brief 총알을 생성하는 시간 주기입니다.
	 */
	float respawnTime_ = 0.0f;


	/**
	 * @brief 총알을 생성하는 쿼드의 가로 크기입니다.
	 */
	float width_ = 0.0f;


	/**
	 * @brief 총알을 생성하는 쿼드의 세로 크기입니다.
	 */
	float height_ = 0.0f;


	/**
	 * @brief 총알을 생성하는 쿼드의 매인 색상입니다.
	 */
	Vector4f mainColor_;


	/**
	 * @brief 총알을 생성하는 쿼드의 서브 색상입니다.
	 */
	Vector4f subColor_;


	/**
	 * @brief 총알 생성 이벤트입니다.
	 */
	std::function<void()> respawnTrigger_ = nullptr;
};