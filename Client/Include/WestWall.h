#pragma once

#include "Box3D.h"
#include "GameObject.h"


/**
 * @brief 서쪽 벽 오브젝트입니다.
 */
class WestWall : public GameObject
{
public:
	/**
	 * @brief 서쪽 벽 오브젝트의 기본 생성자입니다.
	 *
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	WestWall() = default;


	/**
	 * @brief 서쪽 벽 오브젝트의 가상 소멸자입니다.
	 */
	virtual ~WestWall();


	/**
	 * @brief 서쪽 벽 오브젝트의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(WestWall);


	/**
	 * @brief 서쪽 벽 오브젝트를 초기화합니다.
	 */
	void Initialize();


	/**
	 * @brief 서쪽 벽 오브젝트를 업데이트합니다.
	 * 
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 서쪽 벽 오브젝트 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 서쪽 벽 오브젝트의 경계 영역을 얻습니다.
	 *
	 * @return 서쪽 벽 오브젝트의 경계 영역을 반환합니다.
	 */
	virtual const IShape3D* GetBoundingVolume() const override { return &boundingVolume_; }


private:
	/**
	 * @brief 서쪽 벽 오브젝트의 경계 영역입니다.
	 */
	Box3D boundingVolume_;
};