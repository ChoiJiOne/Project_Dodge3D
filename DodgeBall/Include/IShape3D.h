#pragma once

#include <cstdint>


/**
 * @brief 충돌 가능한 3D 형태의 인터페이스입니다.
 */
class IShape3D
{
public:
	/**
	 * @brief 3D 형태의 종류입니다.
	 */
	enum class EType : int32_t
	{
		None = 0x00,
		Box = 0x01,
		Sphere = 0x02,
	};


public:
	/**
	 * @brief 충돌 가능한 3D 형태 인터페이스의 기본 생성자입니다.
	 */
	IShape3D() = default;


	/**
	 * @brief 충돌 가능한 3D 형태 인터페이스의 가상 소멸자입니다.
	 */
	virtual ~IShape3D() {}


	/**
	 * @brief 3D 형태의 종류를 얻습니다.
	 * 
	 * @return 3D 형태의 종류를 반환합니다.
	 * 
	 * @note 하위 클래스에서 반드시 구현해야 하는 순수 가상 함수입니다.
	 */
	virtual EType GetType() const = 0;


	/**
	 * @brief 다른 3D 형태가 검출되는지 확인합니다.
	 * 
	 * @param shape 검출을 확인할 3D 형태 인스턴스입니다.
	 * 
	 * @return 다른 3D 형태가 검출된다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	virtual bool Intersect(const IShape3D* shape) const = 0;
};