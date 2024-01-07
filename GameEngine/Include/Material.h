#pragma once

#include "IResource.h"
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
	 * @param ambient 재질의 주변(Ambient) 요소입니다.
	 * @param diffuse 재질의 확산(Diffuse) 요소입니다.
	 * @param specular 재질의 반사(Specular) 요소입니다.
	 * @param shininess 재질의 밝기 요소입니다.
	 */
	Material(const Vector3f& ambient, const Vector3f& diffuse, const Vector3f& specular, float shininess) noexcept
		: ambient_(ambient)
		, diffuse_(diffuse)
		, specular_(specular)
		, shininess_(shininess) {}


	/**
	 * @brief 재질(Material)의 복사 생성자입니다.
	 * 
	 * @param instance 재질의 내부 프로퍼티를 복사할 인스턴스입니다.
	 */
	Material(Material&& instance) noexcept
		: ambient_(instance.ambient_)
		, diffuse_(instance.diffuse_)
		, specular_(instance.specular_)
		, shininess_(instance.shininess_) {}


	/**
	 * @brief 재질(Material)의 복사 생성자입니다.
	 *
	 * @param instance 재질의 내부 프로퍼티를 복사할 인스턴스입니다.
	 */
	Material(const Material& instance) noexcept
		: ambient_(instance.ambient_)
		, diffuse_(instance.diffuse_)
		, specular_(instance.specular_)
		, shininess_(instance.shininess_) {}


	/**
	 * @brief 재질의 가상 소멸자입니다.
	 */
	virtual ~Material();


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

		ambient_ = instance.ambient_;
		diffuse_ = instance.diffuse_;
		specular_ = instance.specular_;
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

		ambient_ = instance.ambient_;
		diffuse_ = instance.diffuse_;
		specular_ = instance.specular_;
		shininess_ = instance.shininess_;

		return *this;
	}

	
	/**
	 * @brief 재질의 주변(Ambient) 요소를 얻습니다.
	 * 
	 * @return 재질의 주변 요소를 반환합니다.
	 */
	Vector3f GetAmbient() { return ambient_; }


	/**
	 * @brief 재질의 주변(Ambient) 요소를 얻습니다.
	 *
	 * @return 재질의 주변 요소를 반환합니다.
	 */
	const Vector3f& GetAmbient() const { return ambient_; }


	/**
	 * @brief 재질의 확산(Diffuse) 요소를 얻습니다.
	 *
	 * @return 재질의 확산 요소를 반환합니다.
	 */
	Vector3f GetDiffuse() { return diffuse_; }


	/**
	 * @brief 재질의 확산(Diffuse) 요소를 얻습니다.
	 *
	 * @return 재질의 확산 요소를 반환합니다.
	 */
	const Vector3f& GetDiffuse() const { return diffuse_; }


	/**
	 * @brief 재질의 반사(Specular) 요소를 얻습니다.
	 *
	 * @return 재질의 반사 요소를 반환합니다.
	 */
	Vector3f GetSpecular() { return specular_; }


	/**
	 * @brief 재질의 반사(Specular) 요소를 얻습니다.
	 *
	 * @return 재질의 반사 요소를 반환합니다.
	 */
	const Vector3f& GetSpecular() const { return specular_; }


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
	 * @param ambient 설정할 주변(Ambient) 요소입니다.
	 */
	void SetAmbient(const Vector3f& ambient) { ambient_ = ambient; }


	/**
	 * @brief 재질의 확산(Diffuse) 요소를 설정합니다.
	 * 
	 * @param diffuse 설정할 확산(Diffuse) 요소입니다.
	 */
	void SetDiffuse(const Vector3f& diffuse) { diffuse_ = diffuse; }


	/**
	 * @brief 재질의 반사(Specular) 요소를 설정합니다.
	 * 
	 * @param specular 설정할 반사(Specular) 요소입니다.
	 */
	void SetSpecular(const Vector3f& specular) { specular_ = specular; }


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
	Vector3f ambient_;


	/**
	 * @brief 재질의 확산(Diffuse) 요소입니다.
	 */
	Vector3f diffuse_;


	/**
	 * @brief 재질의 반사(Specular) 요소입니다.
	 */
	Vector3f specular_;


	/**
	 * @brief 재질의 밝기 요소입니다.
	 */
	float shininess_;
};