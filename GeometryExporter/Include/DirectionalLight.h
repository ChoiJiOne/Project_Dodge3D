#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief 직선광(Directional Light)입니다.
 */
class DirectionalLight
{
public:
	/**
	 * @brief 직선광(Directional Light)의 디폴트 생성자입니다.
	 */
	DirectionalLight() = default;


	/**
	 * @brief 직선광(Directional Light)의 생성자입니다.
	 * 
	 * @param direction 직선광의 방향입니다.
	 * @param ambientRGB 직선광의 Ambient 색상입니다.
	 * @param diffuseRGB 직선광의 Diffuse 색상입니다.
	 * @param specularRGB 직선광의 Specular 색상입니다.
	 */
	DirectionalLight(const Vector3f& direction, const Vector3f& ambientRGB, const Vector3f& diffuseRGB, const Vector3f& specularRGB)
		: direction_(direction)
		, ambientRGB_(ambientRGB)
		, diffuseRGB_(diffuseRGB)
		, specularRGB_(specularRGB) {}


	/**
	 * @brief 직선광(Directional Light)의 복사 생성자입니다.
	 *
	 * @param instance 직선광의 내부 프로퍼티를 복사할 인스턴입니다.
	 */
	DirectionalLight(DirectionalLight&& instance) noexcept
		: direction_(instance.direction_)
		, ambientRGB_(instance.ambientRGB_)
		, diffuseRGB_(instance.diffuseRGB_)
		, specularRGB_(instance.specularRGB_) {}


	/**
	 * @brief 직선광(Directional Light)의 복사 생성자입니다.
	 *
	 * @param instance 직선광의 내부 프로퍼티를 복사할 인스턴입니다.
	 */
	DirectionalLight(const DirectionalLight& instance) noexcept
		: direction_(instance.direction_)
		, ambientRGB_(instance.ambientRGB_)
		, diffuseRGB_(instance.diffuseRGB_)
		, specularRGB_(instance.specularRGB_) {}


	/**
	 * @brief 직선광(Directional Light)의 가상 소멸자입니다.
	 */
	virtual ~DirectionalLight() {}


	/**
	 * @brief 직선광의 대입 연산자입니다.
	 *
	 * @param instance 직선광의 내부 프로퍼티를 복사할 인스턴입니다.
	 *
	 * @return 대입한 직선광의 참조자를 반환합니다.
	 */
	DirectionalLight& operator=(DirectionalLight&& instance) noexcept
	{
		if (this == &instance) return *this;

		direction_ = instance.direction_;
		ambientRGB_ = instance.ambientRGB_;
		diffuseRGB_ = instance.diffuseRGB_;
		specularRGB_ = instance.specularRGB_;

		return *this;
	}


	/**
	 * @brief 직선광의 대입 연산자입니다.
	 *
	 * @param instance 직선광의 내부 프로퍼티를 복사할 인스턴입니다.
	 *
	 * @return 대입한 직선광의 참조자를 반환합니다.
	 */
	DirectionalLight& operator=(const DirectionalLight& instance) noexcept
	{
		if (this == &instance) return *this;

		direction_ = instance.direction_;
		ambientRGB_ = instance.ambientRGB_;
		diffuseRGB_ = instance.diffuseRGB_;
		specularRGB_ = instance.specularRGB_;

		return *this;
	}


	/**
	 * @brief 직선광(Directional Light)의 방향을 얻습니다.
	 *
	 * @return 직선광(Directional Light)의 방향을 반환합니다.
	 */
	Vector3f GetDirection() { return direction_; }


	/**
	 * @brief 직선광(Directional Light)의 방향을 얻습니다.
	 *
	 * @return 직선광(Directional Light)의 방향을 반환합니다.
	 */
	const Vector3f& GetDirection() const { return direction_; }


	/**
	 * @brief 직선광(Directional Light)의 주변(Ambient) 색상을 얻습니다.
	 *
	 * @return 직선광(Directional Light)의 주변 색상을 반환합니다.
	 */
	Vector3f GetAmbientRGB() { return ambientRGB_; }


	/**
	 * @brief 직선광(Directional Light)의 주변(Ambient) 색상을 얻습니다.
	 *
	 * @return 직선광(Directional Light)의 주변 색상을 반환합니다.
	 */
	const Vector3f& GetAmbientRGB() const { return ambientRGB_; }


	/**
	 * @brief 직선광(Directional Light)의 확산(Diffuse) 색상을 얻습니다.
	 *
	 * @return 직선광(Directional Light)의 확산 색상을 반환합니다.
	 */
	Vector3f GetDiffuseRGB() { return diffuseRGB_; }


	/**
	 * @brief 직선광(Directional Light)의 확산(Diffuse) 색상을 얻습니다.
	 *
	 * @return 직선광(Directional Light)의 확산 색상을 반환합니다.
	 */
	const Vector3f& GetDiffuseRGB() const { return diffuseRGB_; }


	/**
	 * @brief 직선광(Directional Light)의 반사(Specular) 색상을 얻습니다.
	 *
	 * @return 직선광(Directional Light)의 반사 색상을 반환합니다.
	 */
	Vector3f GetSpecularRGB() { return specularRGB_; }


	/**
	 * @brief 직선광(Directional Light)의 반사(Specular) 색상을 얻습니다.
	 *
	 * @return 직선광(Directional Light)의 반사 색상을 반환합니다.
	 */
	const Vector3f& GetSpecularRGB() const { return specularRGB_; }

	
	/**
	 * @brief 직선광(Directional Light)의 방향을 설정합니다.
	 *
	 * @param direction 설정할 직선광의 방향입니다.
	 */
	void SetDirection(const Vector3f& direction) { direction_ = direction; }


	/**
	 * @brief 직선광(Directional Light)의 주변(Ambient) 색상을 설정합니다.
	 *
	 * @param ambientRGB 설정할 주변(Ambient) 색상입니다.
	 */
	void SetAmbientRGB(const Vector3f& ambientRGB) { ambientRGB_ = ambientRGB; }


	/**
	 * @brief 직선광(Directional Light)의 확산(Diffuse) 색상을 설정합니다.
	 *
	 * @param diffuseRGB 설정할 확산(Diffuse) 색상입니다.
	 */
	void SetDiffuseRGB(const Vector3f& diffuseRGB) { diffuseRGB_ = diffuseRGB; }


	/**
	 * @brief 직선광(Directional Light)의 반사(Specular) 색상을 설정합니다.
	 *
	 * @param specular 설정할 반사(Specular) 색상입니다.
	 */
	void SetSpecularRGB(const Vector3f& specularRGB) { specularRGB_ = specularRGB; }


private:
	/**
	 * @brief 직선광의 방향입니다.
	 */
	Vector3f direction_;


	/**
	 * @brief 직선광의 Ambient 색상입니다.
	 */
	Vector3f ambientRGB_;


	/**
	 * @brief 직선광의 Diffuse 색상입니다.
	 */
	Vector3f diffuseRGB_;


	/**
	 * @brief 직선광의 Specular 색상입니다.
	 */
	Vector3f specularRGB_;
};