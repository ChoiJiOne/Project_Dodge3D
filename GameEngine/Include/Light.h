#pragma once

#include "IObject.h"
#include "Matrix4x4.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief 라이트 오브젝트입니다.
 */
class Light : public IObject
{
public:
	/**
	 * @brief 라이트 오브젝트의 디폴트 생성자입니다.
	 *
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	Light() = default;


	/**
	 * @brief 라이트 오브젝트의 가상 소멸자입니다.
	 *
	 * @note 게임 오브젝트 내부에서 할당된 리소스를 해제하기 위해서는 Release 메서드를 호출해야 합니다.
	 */
	virtual ~Light();


	/**
	 * @brief 라이트 오브젝트의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Light);


	/**
	 * @brief 라이트 오브젝트를 초기화합니다.
	 * 
	 * @param position
	 * @param direction
	 * @param ambientRGB
	 * @param diffuseRGB
	 * @param specularRGB
	 * @param worldUp
	 * @param projection
	 */
	void Initialize(
		const Vector3f& position,
		const Vector3f& direction,
		const Vector3f& ambientRGB,
		const Vector3f& diffuseRGB,
		const Vector3f& specularRGB,
		const Vector3f& worldUp,
		const Matrix4x4f projection
	);


	/**
	 * @brief 라이트 오브젝트를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 *
	 * @note
	 * - 라이트 오브젝트를 상속받는 하위 클래스에서 반드시 구현해야 합니다.
	 * - 델타 시간 값은 초단위입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 오브젝트 내의 리소스를 할당 해제합니다.
	 *
	 * @note 라이트 오브젝트를 상속받는 하위 클래스에서 반드시 구현해야 합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 라이트의 위치를 얻습니다.
	 *
	 * @return 라이트의 위치를 반환합니다.
	 */
	Vector3f GetPosition() { return position_; }


	/**
	 * @brief 라이트의 위치를 얻습니다.
	 *
	 * @return 라이트의 위치를 반환합니다.
	 */
	const Vector3f& GetPosition() const { return position_; }


	/**
	 * @brief 라이트의 방향을 얻습니다.
	 *
	 * @return 라이트의 방향을 반환합니다.
	 */
	Vector3f GetDirection() { return direction_; }


	/**
	 * @brief 라이트의 방향을 얻습니다.
	 *
	 * @return 라이트의 방향을 반환합니다.
	 */
	const Vector3f& GetDirection() const { return direction_; }


	/**
	 * @brief 라이트의 주변(Ambient) 색상을 얻습니다.
	 *
	 * @return 라이트의 주변 색상을 반환합니다.
	 */
	Vector3f GetAmbientRGB() { return ambientRGB_; }


	/**
	 * @brief 라이트의 주변(Ambient) 색상을 얻습니다.
	 *
	 * @return 라이트의 주변 색상을 반환합니다.
	 */
	const Vector3f& GetAmbientRGB() const { return ambientRGB_; }


	/**
	 * @brief 라이트의 확산(Diffuse) 색상을 얻습니다.
	 *
	 * @return 라이트의 확산 색상을 반환합니다.
	 */
	Vector3f GetDiffuseRGB() { return diffuseRGB_; }


	/**
	 * @brief 라이트의 확산(Diffuse) 색상을 얻습니다.
	 *
	 * @return 라이트의 확산 색상을 반환합니다.
	 */
	const Vector3f& GetDiffuseRGB() const { return diffuseRGB_; }


	/**
	 * @brief 라이트의 반사(Specular) 색상을 얻습니다.
	 *
	 * @return 라이트의 반사 색상을 반환합니다.
	 */
	Vector3f GetSpecularRGB() { return specularRGB_; }


	/**
	 * @brief 라이트의 반사(Specular) 색상을 얻습니다.
	 *
	 * @return 라이트의 반사 색상을 반환합니다.
	 */
	const Vector3f& GetSpecularRGB() const { return specularRGB_; }


	/**
	 * @brief 라이트의 시야 행렬을 얻습니다.
	 * 
	 * @return 라이트의 시야 행렬을 반환합니다.
	 */
	Matrix4x4f GetViewMatrix() { return view_; }


	/**
	 * @brief 라이트의 시야 행렬을 얻습니다.
	 *
	 * @return 라이트의 시야 행렬을 반환합니다.
	 */
	const Matrix4x4f& GetViewMatrix() const { return view_; }


	/**
	 * @brief 라이트의 투영 행렬을 얻습니다.
	 * 
	 * @return 라이트의 투영 행렬을 반환합니다.
	 */
	Matrix4x4f GetProjectionMatrix() { return projection_; }


	/**
	 * @brief 라이트의 투영 행렬을 얻습니다.
	 *
	 * @return 라이트의 투영 행렬을 반환합니다.
	 */
	const Matrix4x4f& GetProjectionMatrix() const { return projection_; }
	

protected:
	/**
	 * @brief 라이트의 위치입니다.
	 *
	 * @note 그림자 계산 시 사용합니다.
	 */
	Vector3f position_;


	/**
	 * @brief 라이트의 방향입니다.
	 */
	Vector3f direction_;


	/**
	 * @brief 라이트의 Ambient 색상입니다.
	 */
	Vector3f ambientRGB_;


	/**
	 * @brief 라이트의 Diffuse 색상입니다.
	 */
	Vector3f diffuseRGB_;


	/**
	 * @brief 라이트의 Specular 색상입니다.
	 */
	Vector3f specularRGB_;


	/**
	 * @brief 라이트 시점의 시야 행렬입니다.
	 */
	Matrix4x4f view_;


	/**
	 * @brief 라이트 시점의 투영 행렬입니다.
	 */
	Matrix4x4f projection_;
};