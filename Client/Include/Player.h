#pragma once

#include "Sphere3D.h"
#include "IObject.h"
#include "Transform.h"

class Material;
class StaticMesh;


/**
 * @brief 플레이어가 조종 가능한 오브젝트입니다.
 */
class Player : public IObject
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
	 * @brief 플레이어가 조종 가능한 오브젝트의 메시를 얻습니다.
	 *
	 * @return 플레이어가 조종 가능한 오브젝트의 메시를 반환합니다.
	 */
	StaticMesh* GetMesh() const { return mesh_; }


	/**
	 * @brief 플레이어가 조종 가능한 오브젝트의 재질을 얻습니다.
	 *
	 * @return 플레이어가 조종 가능한 오브젝트의 재질을 반환합니다.
	 */
	Material* GetMaterial() const { return material_; }


	/**
	 * @brief 플레이어가 조종 가능한 오브젝트의 트랜스폼을 얻습니다.
	 *
	 * @return 플레이어가 조종 가능한 오브젝트의 트랜스폼을 반환합니다.
	 */
	const Transform& GetTransform() const { return transform_; }


	/**
	 * @brief 플레이어가 조종 가능한 오브젝트의 경계 영역을 얻습니다.
	 *
	 * @return 플레이어가 조종 가능한 오브젝트의 경계 영역을 반환합니다.
	 */
	const Sphere3D& GetBoundingVolume() const { return boundingVolume_; }


private:
	/**
	 * @brief 플레이어가 조종 가능한 오브젝트의 정적 메시입니다.
	 */
	StaticMesh* mesh_ = nullptr;


	/**
	 * @brief 플레이어가 조종 가능한 오브젝트의 재질입니다.
	 */
	Material* material_ = nullptr;


	/**
	 * @brief 플레이어가 조종 가능한 오브젝트의 트랜스폼입니다.
	 */
	Transform transform_;


	/**
	 * @brief 플레이어가 조종 가능한 오브젝트의 경계 영역입니다.
	 */
	Sphere3D boundingVolume_;
};