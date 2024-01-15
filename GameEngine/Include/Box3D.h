#pragma once

#include "IShape3D.h"
#include "Vector3.h"


/**
 * @brief 경계 축이 정렬된 상자(Box)입니다.
 */
class Box3D : public IShape3D
{
public:
	/**
	 * @brief 경계 축이 정렬된 상자의 기본 생성자입니다.
	 */
	Box3D() = default;


	/**
	 * @brief 경계 축이 정렬된 상자의 생성자입니다.
	 * 
	 * @param center 경계 축이 정렬된 상자의 중심 좌표입니다.
	 * @param extents 경계 축이 정렬된 상자의 X/Y/Z 축 방향으로의 크기입니다.
	 */
	Box3D(const Vector3f& center, const Vector3f& extents)
		: center_(center)
		, extents_(extents) {}


	/**
	 * @brief 경계 축이 정렬된 상자의 복사 생성자입니다.
	 * 
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 */
	Box3D(Box3D&& instance) noexcept
		: center_(instance.center_)
		, extents_(instance.extents_) {}


	/**
	 * @brief 경계 축이 정렬된 상자의 복사 생성자입니다.
	 *
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 */
	Box3D(const Box3D& instance) noexcept
		: center_(instance.center_)
		, extents_(instance.extents_) {}

	
	/**
	 * @brief 경계 축이 정렬된 상자의 가상 소멸자입니다.
	 */
	virtual ~Box3D() {}


	/**
	 * @brief 경계 축이 정렬된 상자의 대입 연산자입니다.
	 * 
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 * 
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	Box3D& operator=(Box3D&& instance) noexcept
	{
		if (this == &instance) return *this;

		center_ = instance.center_;
		extents_ = instance.extents_;

		return *this;
	}


	/**
	 * @brief 경계 축이 정렬된 상자의 대입 연산자입니다.
	 *
	 * @param instance 내부 프로퍼티를 복사할 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	Box3D& operator=(const Box3D& instance) noexcept
	{
		if (this == &instance) return *this;

		center_ = instance.center_;
		extents_ = instance.extents_;

		return *this;
	}


	/**
	 * @brief 경계 축이 정렬된 상자의 중심 좌표를 얻습니다.
	 * 
	 * @return 경계 축이 정렬된 상자의 중심 좌표를 반환합니다.
	 */
	Vector3f GetCenter() { return center_; }


	/**
	 * @brief 경계 축이 정렬된 상자의 중심 좌표를 얻습니다.
	 *
	 * @return 경계 축이 정렬된 상자의 중심 좌표를 반환합니다.
	 */
	const Vector3f& GetCenter() const { return center_; }


	/**
	 * @brief 경계 축이 정렬된 상자의 X/Y/Z 축 방향으로의 크기를 얻습니다.
	 * 
	 * @return 경계 축이 정렬된 상자의 X/Y/Z 축 방향으로의 크기를 반환합니다.
	 */
	Vector3f GetExtents() { return extents_; }


	/**
	 * @brief 경계 축이 정렬된 상자의 X/Y/Z 축 방향으로의 크기를 얻습니다.
	 *
	 * @return 경계 축이 정렬된 상자의 X/Y/Z 축 방향으로의 크기를 반환합니다.
	 */
	const Vector3f& GetExtents() const { return extents_; }


	/**
	 * @brief 경계 영역의 최소값을 얻습니다.
	 * 
	 * @return 경계 영역의 최소값을 반환합니다.
	 */
	Vector3f GetMinPosition() const { return center_ - extents_ * 0.5f; }


	/**
	 * @brief 경계 영역의 최댓값을 얻습니다.
	 * 
	 * @return 경계 영역의 최댓값을 반환합니다.
	 */
	Vector3f GetMaxPosition() const { return center_ + extents_ * 0.5f; }


	/**
	 * @brief 경계 축이 정렬된 상자의 중심 좌표를 설정합니다.
	 * 
	 * @param center 설정할 경계 축이 정렬된 상자의 중심좌표입니다.
	 */
	void SetCenter(const Vector3f& center) { center_ = center; }


	/**
	 * @brief 경계 축이 정렬된 상자의 크기를 설정합니다.
	 * 
	 * @param extents 설정할 경계 축이 정렬된 상자의 크기입니다.
	 */
	void SetExtents(const Vector3f& extents) { extents_ = extents; }


	/**
	 * @brief 경계 축이 정렬된 상자의 형태 열거형 값을 얻습니다.
	 * 
	 * @return 경계 축이 정렬된 상자의 형태 열거형 값을 반환합니다.
	 */
	virtual EType GetType() const override { return EType::Box; }


	/**
	 * @brief 다른 3D 형태가 검출되는지 확인합니다.
	 *
	 * @param shape 검출을 확인할 3D 형태 인스턴스입니다.
	 *
	 * @return 다른 3D 형태가 검출된다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	virtual bool Intersect(const IShape3D* shape) const override;

	
private:
	/**
	 * @brief 다른 경계 축 정렬 상자와 충돌하는지 확인합니다.
	 * 
	 * @param shape 검출을 확인할 3D 형태 인스턴스입니다.
	 * 
	 * @return 다른 경계 축 정렬 상자가 검출된다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IntersectBox3D(const IShape3D* shape) const;


	/**
	 * @brief 다른 구 영역과 충돌하는지 확인합니다.
	 * 
	 * @param shape 검출을 확인할 3D 형태 인스턴스입니다.
	 *
	 * @return 다른 구 영역이 검출된다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IntersectSphere3D(const IShape3D* shape) const;


private:
	/**
	 * @brief 경계 축이 정렬된 상자의 중심 좌표입니다.
	 */
	Vector3f center_;


	/**
	 * @brief 경계 축이 정렬된 상자의 크기입니다.
	 */
	Vector3f extents_;
};