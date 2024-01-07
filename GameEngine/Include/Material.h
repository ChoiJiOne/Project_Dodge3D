#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief 메시의 기본 재질(Material)입니다.
 */
class Material
{
public:
	/**
	 * @brief 재질의 디폴트 생성자입니다.
	 */
	Material() = default;


	/**
	 * @brief 재질(Material)의 생성자입니다.
	 * 
	 * @param ambientRGB 재질의 주변(Ambient) 요소입니다.
	 * @param diffuseRGB 재질의 확산(Diffuse) 요소입니다.
	 * @param specularRGB 재질의 반사(Specular) 요소입니다.
	 * @param shininess 재질의 밝기 요소입니다.
	 */
	Material(const Vector3f& ambientRGB, const Vector3f& diffuseRGB, const Vector3f& specularRGB, float shininess) noexcept
		: ambientRGB_(ambientRGB)
		, diffuseRGB_(diffuseRGB)
		, specularRGB_(specularRGB)
		, shininess_(shininess) {}


	/**
	 * @brief 재질(Material)의 복사 생성자입니다.
	 * 
	 * @param instance 재질의 내부 프로퍼티를 복사할 인스턴스입니다.
	 */
	Material(Material&& instance) noexcept
		: ambientRGB_(instance.ambientRGB_)
		, diffuseRGB_(instance.diffuseRGB_)
		, specularRGB_(instance.specularRGB_)
		, shininess_(instance.shininess_) {}


	/**
	 * @brief 재질(Material)의 복사 생성자입니다.
	 *
	 * @param instance 재질의 내부 프로퍼티를 복사할 인스턴스입니다.
	 */
	Material(const Material& instance) noexcept
		: ambientRGB_(instance.ambientRGB_)
		, diffuseRGB_(instance.diffuseRGB_)
		, specularRGB_(instance.specularRGB_)
		, shininess_(instance.shininess_) {}


	/**
	 * @brief 재질의 가상 소멸자입니다.
	 */
	virtual ~Material() {}


	/**
	 * @brief 재질의 대입 연산자입니다.
	 * 
	 * @param instance 재질의 내부 프로퍼티를 복사할 인스턴스입니다.
	 * 
	 * @return 대입한 재질의 참조자를 반환합니다.
	 */
	Material& operator=(Material&& instance) noexcept
	{
		if (this == &instance) return *this;

		ambientRGB_ = instance.ambientRGB_;
		diffuseRGB_ = instance.diffuseRGB_;
		specularRGB_ = instance.specularRGB_;
		shininess_ = instance.shininess_;

		return *this;
	}


	/**
	 * @brief 재질의 대입 연산자입니다.
	 *
	 * @param instance 재질의 내부 프로퍼티를 복사할 인스턴스입니다.
	 *
	 * @return 대입한 재질의 참조자를 반환합니다.
	 */
	Material& operator=(const Material& instance) noexcept
	{
		if (this == &instance) return *this;

		ambientRGB_ = instance.ambientRGB_;
		diffuseRGB_ = instance.diffuseRGB_;
		specularRGB_ = instance.specularRGB_;
		shininess_ = instance.shininess_;

		return *this;
	}

	
	/**
	 * @brief 재질의 주변(Ambient) 요소를 얻습니다.
	 * 
	 * @return 재질의 주변 요소를 반환합니다.
	 */
	Vector3f GetAmbientRGB() { return ambientRGB_; }


	/**
	 * @brief 재질의 주변(Ambient) 요소를 얻습니다.
	 *
	 * @return 재질의 주변 요소를 반환합니다.
	 */
	const Vector3f& GetAmbientRGB() const { return ambientRGB_; }


	/**
	 * @brief 재질의 확산(Diffuse) 요소를 얻습니다.
	 *
	 * @return 재질의 확산 요소를 반환합니다.
	 */
	Vector3f GetDiffuseRGB() { return diffuseRGB_; }


	/**
	 * @brief 재질의 확산(Diffuse) 요소를 얻습니다.
	 *
	 * @return 재질의 확산 요소를 반환합니다.
	 */
	const Vector3f& GetDiffuseRGB() const { return diffuseRGB_; }


	/**
	 * @brief 재질의 반사(Specular) 요소를 얻습니다.
	 *
	 * @return 재질의 반사 요소를 반환합니다.
	 */
	Vector3f GetSpecularRGB() { return specularRGB_; }


	/**
	 * @brief 재질의 반사(Specular) 요소를 얻습니다.
	 *
	 * @return 재질의 반사 요소를 반환합니다.
	 */
	const Vector3f& GetSpecularRGB() const { return specularRGB_; }


	/**
	 * @brief 재질의 밝기 요소를 얻습니다.
	 *
	 * @return 재질의 밝기 요소를 반환합니다.
	 */
	float GetShininess() { return shininess_; }


	/**
	 * @brief 재질의 밝기 요소를 얻습니다.
	 *
	 * @return 재질의 밝기 요소를 반환합니다.
	 */
	const float& GetShininess() const { return shininess_; }


	/**
	 * @brief 재질의 주변(Ambient) 요소를 설정합니다.
	 * 
	 * @param ambientRGB 설정할 주변(Ambient) 요소입니다.
	 */
	void SetAmbientRGB(const Vector3f& ambientRGB) { ambientRGB_ = ambientRGB; }


	/**
	 * @brief 재질의 확산(Diffuse) 요소를 설정합니다.
	 * 
	 * @param diffuseRGB 설정할 확산(Diffuse) 요소입니다.
	 */
	void SetDiffuseRGB(const Vector3f& diffuseRGB) { diffuseRGB_ = diffuseRGB; }


	/**
	 * @brief 재질의 반사(Specular) 요소를 설정합니다.
	 * 
	 * @param specular 설정할 반사(Specular) 요소입니다.
	 */
	void SetSpecularRGB(const Vector3f& specularRGB) { specularRGB_ = specularRGB; }


	/**
	 * @brief 재질의 밝기 요소를 설정합니다.
	 * 
	 * @param shininess 설정할 밝기 요소입니다.
	 */
	void SetShininess(float shininess) { shininess_ = shininess; }


private:
	/**
	 * @brief 재질의 주변(Ambient) 요소입니다.
	 */
	Vector3f ambientRGB_;


	/**
	 * @brief 재질의 확산(Diffuse) 요소입니다.
	 */
	Vector3f diffuseRGB_;


	/**
	 * @brief 재질의 반사(Specular) 요소입니다.
	 */
	Vector3f specularRGB_;


	/**
	 * @brief 재질의 밝기 요소입니다.
	 */
	float shininess_;
};