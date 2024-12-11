#pragma once

#include "IObject.h"
#include "IShape3D.h"
#include "Material.h"
#include "StaticMesh.h"
#include "Transform.h"


/**
 * @brief 게임 오브젝트입니다.
 */
class GameObject : public IObject
{
public:
	/**
	 * @brief 게임 오브젝트의 디폴트 생성자입니다.
	 */
	GameObject() = default;


	/**
	 * @brief 게임 오브젝트의 가상 소멸자입니다.
	 */
	virtual ~GameObject() {}


	/**
	 * @brief 게임 오브젝트의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(GameObject);


	/**
	 * @brief 게임 오브젝트의 메시를 얻습니다.
	 *
	 * @return 게임 오브젝트의 메시를 반환합니다.
	 */
	StaticMesh* GetMesh() const { return mesh_; }


	/**
	 * @brief 게임 오브젝트의 재질을 얻습니다.
	 *
	 * @return 게임 오브젝트의 재질을 반환합니다.
	 */
	Material* GetMaterial() const { return material_; }


	/**
	 * @brief 게임 오브젝트의 트랜스폼을 얻습니다.
	 *
	 * @return 게임 오브젝트의 트랜스폼을 반환합니다.
	 */
	const Transform& GetTransform() const { return transform_; }


	/**
	 * @brief 게임 오브젝트의 경계 영역을 얻습니다.
	 * 
	 * @return 게임 오브젝트의 경계 영역을 반환합니다.
	 * 
	 * @note 이 메서드는 순수 가상 함수로 하위 메서드에서 반드시 구현해야 합니다.
	 */
	virtual const IShape3D* GetBoundingVolume() const = 0;


	/**
	 * @brief 다른 게임 오브젝트와의 충돌 여부를 확인합니다.
	 * 
	 * @param object 충돌 여부를 검사할 다른 게임 오브젝트입니다.
	 */
	bool IsCollision(const GameObject* object) const;


protected:
	/**
	 * @brief 게임 오브젝트의 메시입니다.
	 */
	StaticMesh* mesh_ = nullptr;


	/**
	 * @brief 게임 오브젝트의 재질(Material)입니다.
	 */
	Material* material_ = nullptr;


	/**
	 * @brief 게임 오브젝트의 트랜스폼입니다.
	 */
	Transform transform_;
};