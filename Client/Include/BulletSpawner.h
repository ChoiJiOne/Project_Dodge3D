#pragma once

#include "IObject.h"
#include "Vector3.h"

class Material;
class StaticMesh;


/**
 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트입니다.
 */
class BulletSpawner : public IObject
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
	 * @param position 플레이어가 피해야 할 총알을 생성하는 오브젝트의 월드 상 위치입니다. 
	 */
	void Initialize(const Vector3f& position);


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트를 업데이트합니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트의 메시를 얻습니다.
	 *
	 * @return 플레이어가 피해야 할 총알을 생성하는 오브젝트의 메시를 반환합니다.
	 */
	StaticMesh* GetMesh() const { return mesh_; }


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트의 재질을 얻습니다.
	 *
	 * @return 플레이어가 피해야 할 총알을 생성하는 오브젝트의 재질을 반환합니다.
	 */
	Material* GetMaterial() const { return material_; }


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트의 현재 위치를 얻습니다.
	 *
	 * @return 플레이어가 피해야 할 총알을 생성하는 오브젝트의 위치를 반환합니다.
	 */
	const Vector3f& GetPosition() const { return position_; }


	/**
	 * @brief 월드에 생성된 총알을 생성하는 오브젝트 수를 얻습니다.
	 * 
	 * @return 월드에 생성된 총알을 생성하는 오브젝트 수를 반환합니다.
	 */
	static uint32_t GetCountOfBulletSpawner() { return countOfBulletSpawner_; }


private:
	/**
	 * @brief 월드에 생성된 총알을 생성하는 오브젝트 수입니다.
	 */
	static uint32_t countOfBulletSpawner_;


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트의 정적 메시입니다.
	 */
	StaticMesh* mesh_ = nullptr;


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트의 재질입니다.
	 */
	Material* material_ = nullptr;


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트의 현재 위치입니다.
	 */
	Vector3f position_;


	/**
	 * @brief 총알의 최대 발사 각도입니다. 단위는 라디안입니다.
	 */
	float maxShotAngle_ = 0.0f;


	/**
	 * @brief 총알의 최소 발사 각도입니다. 단위는 라디안입니다.
	 */
	float minShotAngle_ = 0.0f;
};