#pragma once

#include "Matrix4x4.h"
#include "Vector3.h"


/**
 * @brief 월드 내 게임 오브젝트의 위치, 회전, 스케일(크기)를 변경합니다.
 * 
 * @see 
 * - https://docs.unrealengine.com/4.27/ko/Basics/Actors/Transform/
 * - https://learnopengl.com/Guest-Articles/2021/Scene/Scene-Graph
 */
class Transform
{
public:
	/**
	 * @brief 오브젝트 트랜스폼의 기본 생성자입니다.
	 */
	Transform() = default;


	/**
	 * @brief 오브젝트 트랜스폼의 생성자입니다.
	 * 
	 * @param location 오브젝트의 위치입니다.
	 * @param rotate 오브젝트의 회전 각도입니다. 단위는 라디안입니다.
	 * @param scale 오브젝트의 크기입니다.
	 */
	Transform(const Vector3f& location, const Vector3f& rotate, const Vector3f& scale) 
		: location_(location)
		, rotate_(rotate)
		, scale_(scale)
	{
		ComputeWorldMatrix();
	}
	
	
	/**
	 * @brief 오브젝트 트랜스폼의 복사 생성자입니다.
	 * 
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 */
	Transform(Transform&& instance) noexcept
		: location_(instance.location_)
		, rotate_(instance.rotate_)
		, scale_(instance.scale_)
		, worldMatrix_(instance.worldMatrix_) {}


	/**
	 * @brief 오브젝트 트랜스폼의 복사 생성자입니다.
	 *
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 */
	Transform(const Transform& instance) noexcept
		: location_(instance.location_)
		, rotate_(instance.rotate_)
		, scale_(instance.scale_)
		, worldMatrix_(instance.worldMatrix_) {}


	/**
	 * 오브젝트 트랜스폼의 가상 소멸자입니다.
	 */
	virtual ~Transform() {}


	/**
	 * @brief 오브젝트 트랜스폼의 대입 연산자입니다.
	 * 
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 * 
	 * @return 복사한 객체의 참조자를 반환합니다.
	 */
	Transform& operator=(Transform&& instance) noexcept
	{
		if (this == &instance) return *this;

		location_ = instance.location_;
		rotate_ = instance.rotate_;
		scale_ = instance.scale_;
		worldMatrix_ = instance.worldMatrix_;

		return *this;
	}


	/**
	 * @brief 오브젝트 트랜스폼의 대입 연산자입니다.
	 *
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 *
	 * @return 복사한 객체의 참조자를 반환합니다.
	 */
	Transform& operator=(const Transform& instance) noexcept
	{
		if (this == &instance) return *this;

		location_ = instance.location_;
		rotate_ = instance.rotate_;
		scale_ = instance.scale_;
		worldMatrix_ = instance.worldMatrix_;

		return *this;
	}


	/**
	 * @brief 오브젝트의 위치를 얻습니다.
	 * 
	 * @return 오브젝트의 위치값을 반환합니다.
	 */
	Vector3f GetLocation() { return location_; }


	/**
	 * @brief 오브젝트의 위치를 얻습니다.
	 *
	 * @return 오브젝트의 위치값을 반환합니다.
	 */
	const Vector3f& GetLocation() const { return location_; }


	/**
	 * @brief 오브젝트의 회전 각을 얻습니다.
	 * 
	 * @return 오브젝트의 회전 각을 반환합니다.
	 */
	Vector3f GetRotate() { return rotate_; }


	/**
	 * @brief 오브젝트의 회전 각을 얻습니다.
	 *
	 * @return 오브젝트의 회전 각을 반환합니다.
	 */
	const Vector3f& GetRotate() const { return rotate_; }


	/**
	 * @brief 오브젝트의 크기 값을 얻습니다.
	 * 
	 * @return 오브젝트의 크기 값을 반환합니다.
	 */
	Vector3f GetScale() { return scale_; }


	/**
	 * @brief 오브젝트의 크기 값을 얻습니다.
	 *
	 * @return 오브젝트의 크기 값을 반환합니다.
	 */
	const Vector3f& GetScale() const { return scale_; }


	/**
	 * @brief 오브젝트의 월드 행렬 값을 얻습니다.
	 * 
	 * @return 오브젝트의 월드 행렬 값을 반환합니다.
	 */
	Matrix4x4f GetWorldMatrix() { return worldMatrix_; }


	/**
	 * @brief 오브젝트의 월드 행렬 값을 얻습니다.
	 *
	 * @return 오브젝트의 월드 행렬 값을 반환합니다.
	 */
	const Matrix4x4f& GetWorldMatrix() const { return worldMatrix_; }


	/**
	 * @brief 오브젝트의 위치를 설정합니다.
	 * 
	 * @param location 설정할 오브젝트의 위치 값입니다.
	 */
	void SetLocation(const Vector3f& location);


	/**
	 * @brief 오브젝트의 회전 각을 설정합니다.
	 * 
	 * @param rotate 설정할 오브젝트의 회전 각입니다.
	 */
	void SetRotate(const Vector3f& rotate);


	/**
	 * @brief 오브젝트의 스케일 값을 설정합니다.
	 * 
	 * @param scale 설정할 오브젝트의 스케일 값입니다.
	 */
	void SetScale(const Vector3f& scale);


	/**
	 * @brief 오브젝트의 위치, 회전, 크기 값을 설정합니다.
	 * 
	 * @param location 오브젝트의 위치입니다.
	 * @param rotate 오브젝트의 회전 각도입니다. 단위는 라디안입니다.
	 * @param scale 오브젝트의 크기입니다.
	 */
	void SetProperties(const Vector3f& location, const Vector3f& rotate, const Vector3f& scale);


private:
	/**
	 * @brief 월드 행렬을 계산합니다.
	 */
	void ComputeWorldMatrix();


private:
	/**
	 * @brief 오브젝트의 위치입니다.
	 */
	Vector3f location_;


	/**
	 * @brief 오브젝트의 회전 각도입니다. 단위는 라디안입니다.
	 */
	Vector3f rotate_;


	/**
	 * @brief 오브젝트의 크기입니다.
	 */
	Vector3f scale_;


	/**
	 * @brief 오브젝트의 위치*회전*크기 값이 적용된 월드 행렬입니다.
	 */
	Matrix4x4f worldMatrix_;
};