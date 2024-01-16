#pragma once

#include "IObject.h"
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