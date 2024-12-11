#pragma once

#include "Camera3D.h"


/**
 * @brief 플레이어에 따라 움직이는 카메라입니다.
 */
class MovableCamera : public Camera3D
{
public:
	/**
	 * @brief 플레이어에 따라 움직이는 카메라 오브젝트의 디폴트 생성자입니다.
	 *
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	MovableCamera() = default;


	/**
	 * @brief 플레이어에 따라 움직이는 카메라 오브젝트의 가상 소멸자입니다.
	 *
	 * @note 플레이어에 따라 움직이는 카메라 오브젝트의 내부 리소스를 할당 해제하기 위해서는 Release 메서드를 호출해야 합니다.
	 */
	virtual ~MovableCamera();


	/**
	 * @brief 플레이어에 따라 움직이는 카메라 오브젝트의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(MovableCamera);


	/**
	 * @brief 플레이어에 따라 움직이는 카메라를 초기화합니다.
	 */
	void Initialize();


	/**
	 * @brief 플레이어에 따라 움직이는 카메라 오브젝트를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 플레이어에 따라 움직이는 카메라 오브젝트 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief 플레이어의 위치로부터 카메라의 상대적 위치입니다.
	 */
	Vector3f relativePosition_;
};