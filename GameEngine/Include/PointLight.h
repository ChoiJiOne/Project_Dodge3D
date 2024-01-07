#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief 점광(Point Light)입니다.
 */
class PointLight
{
public:
	/**
	 * @brief 점광(Point Light)의 디폴트 생성자입니다.
	 */
	PointLight() = default;


	/**
	 * @brief 점광(Point Light)의 생성자입니다.
	 *
	 * @param position 점광의 위치입니다.
	 * @param ambientRGB 점광의 Ambient 색상입니다.
	 * @param diffuseRGB 점광의 Diffuse 색상입니다.
	 * @param specularRGB 점광의 Specular 색상입니다.
	 * @param constant 점광의 감쇠율 계산에 사용할 상수항입니다.
	 * @param linear 점광의 감쇠율 계산에 사용할 일차항입니다.
	 * @param quadratic 점광의 감쇠율 계산에 사용할 이차항입니다.
	 */
	PointLight(
		const Vector3f& position, 
		const Vector3f& ambientRGB, 
		const Vector3f& diffuseRGB, 
		const Vector3f& specularRGB, 
		const float& constant, 
		const float& linear, 
		const float& quadratic
	) : position_(position), 
		ambientRGB_(ambientRGB), 
		diffuseRGB_(diffuseRGB), 
		specularRGB_(specularRGB),
		constant_(constant),
		linear_(linear),
		quadratic_(quadratic) {}


	/**
	 * @brief 점광(Point Light)의 복사 생성자입니다.
	 *
	 * @param instance 점광의 내부 프로퍼티를 복사할 인스턴입니다.
	 */
	PointLight(PointLight&& instance) noexcept
		: position_(instance.position_)
		, ambientRGB_(instance.ambientRGB_)
		, diffuseRGB_(instance.diffuseRGB_)
		, specularRGB_(instance.specularRGB_) 
		, constant_(instance.constant_)
		, linear_(instance.linear_)
		, quadratic_(instance.quadratic_) {}


	/**
	 * @brief 점광(Point Light)의 복사 생성자입니다.
	 *
	 * @param instance 점광의 내부 프로퍼티를 복사할 인스턴입니다.
	 */
	PointLight(const PointLight& instance) noexcept
		: position_(instance.position_)
		, ambientRGB_(instance.ambientRGB_)
		, diffuseRGB_(instance.diffuseRGB_)
		, specularRGB_(instance.specularRGB_)
		, constant_(instance.constant_)
		, linear_(instance.linear_)
		, quadratic_(instance.quadratic_) {}


	/**
	 * @brief 점광(Point Light)의 가상 소멸자입니다.
	 */
	virtual ~PointLight() {}


	/**
	 * @brief 점광의 대입 연산자입니다.
	 *
	 * @param instance 점광의 내부 프로퍼티를 복사할 인스턴입니다.
	 *
	 * @return 대입한 점광의 참조자를 반환합니다.
	 */
	PointLight& operator=(PointLight&& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;
		ambientRGB_ = instance.ambientRGB_;
		diffuseRGB_ = instance.diffuseRGB_;
		specularRGB_ = instance.specularRGB_;
		constant_ = instance.constant_;
		linear_ = instance.linear_;
		quadratic_ = instance.quadratic_;

		return *this;
	}


	/**
	 * @brief 점광의 대입 연산자입니다.
	 *
	 * @param instance 점광의 내부 프로퍼티를 복사할 인스턴입니다.
	 *
	 * @return 대입한 점광의 참조자를 반환합니다.
	 */
	PointLight& operator=(const PointLight& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;
		ambientRGB_ = instance.ambientRGB_;
		diffuseRGB_ = instance.diffuseRGB_;
		specularRGB_ = instance.specularRGB_;
		constant_ = instance.constant_;
		linear_ = instance.linear_;
		quadratic_ = instance.quadratic_;

		return *this;
	}


	/**
	 * @brief 점광(Point Light)의 위치를 얻습니다.
	 *
	 * @return 점광(Point Light)의 위치를 반환합니다.
	 */
	Vector3f GetPosition() { return position_; }


	/**
	 * @brief 점광(Point Light)의 위치를 얻습니다.
	 *
	 * @return 점광(Point Light)의 위치를 반환합니다.
	 */
	const Vector3f& GetPosition() const { return position_; }
	

	/**
	 * @brief 점광(Point Light)의 주변(Ambient) 색상을 얻습니다.
	 *
	 * @return 점광(Point Light)의 주변 색상을 반환합니다.
	 */
	Vector3f GetAmbientRGB() { return ambientRGB_; }


	/**
	 * @brief 점광(Point Light)의 주변(Ambient) 색상을 얻습니다.
	 *
	 * @return 점광(Point Light)의 주변 색상을 반환합니다.
	 */
	const Vector3f& GetAmbientRGB() const { return ambientRGB_; }


	/**
	 * @brief 점광(Point Light)의 확산(Diffuse) 색상을 얻습니다.
	 *
	 * @return 점광(Point Light)의 확산 색상을 반환합니다.
	 */
	Vector3f GetDiffuseRGB() { return diffuseRGB_; }


	/**
	 * @brief 점광(Point Light)의 확산(Diffuse) 색상을 얻습니다.
	 *
	 * @return 점광(Point Light)의 확산 색상을 반환합니다.
	 */
	const Vector3f& GetDiffuseRGB() const { return diffuseRGB_; }


	/**
	 * @brief 점광(Point Light)의 반사(Specular) 색상을 얻습니다.
	 *
	 * @return 점광(Point Light)의 반사 색상을 반환합니다.
	 */
	Vector3f GetSpecularRGB() { return specularRGB_; }


	/**
	 * @brief 점광(Point Light)의 반사(Specular) 색상을 얻습니다.
	 *
	 * @return 점광(Point Light)의 반사 색상을 반환합니다.
	 */
	const Vector3f& GetSpecularRGB() const { return specularRGB_; }


	/**
	 * @brief 점광(Point Light)의 감쇠율 계산에 사용할 상수항을 얻습니다.
	 * 
	 * @return 점광(Point Light)의 감쇠율 계산에 사용할 상수항을 반환합니다.
	 */
	float GetConstant() { return constant_; }


	/**
	 * @brief 점광(Point Light)의 감쇠율 계산에 사용할 상수항을 얻습니다.
	 *
	 * @return 점광(Point Light)의 감쇠율 계산에 사용할 상수항을 반환합니다.
	 */
	const float& GetConstant() const { return constant_; }


	/**
	 * @brief 점광(Point Light)의 감쇠율 계산에 사용할 일차항을 얻습니다.
	 *
	 * @return 점광(Point Light)의 감쇠율 계산에 사용할 일차항을 반환합니다.
	 */
	float GetLinear() { return linear_; }


	/**
	 * @brief 점광(Point Light)의 감쇠율 계산에 사용할 일차항을 얻습니다.
	 *
	 * @return 점광(Point Light)의 감쇠율 계산에 사용할 일차항을 반환합니다.
	 */
	const float& GetLinear() const { return linear_; }


	/**
	 * @brief 점광(Point Light)의 감쇠율 계산에 사용할 이차항을 얻습니다.
	 *
	 * @return 점광(Point Light)의 감쇠율 계산에 사용할 이차항을 반환합니다.
	 */
	float GetQuadratic() { return quadratic_; }


	/**
	 * @brief 점광(Point Light)의 감쇠율 계산에 사용할 이차항을 얻습니다.
	 *
	 * @return 점광(Point Light)의 감쇠율 계산에 사용할 이차항을 반환합니다.
	 */
	const float& GetQuadratic() const { return quadratic_; }


	/**
	 * @brief 점광(Point Light)의 위치를 설정합니다.
	 *
	 * @param position 설정할 점광의 위치입니다.
	 */
	void SetPosition(const Vector3f& position) { position_ = position; }

	
	/**
	 * @brief 점광(Point Light)의 주변(Ambient) 색상을 설정합니다.
	 *
	 * @param ambientRGB 설정할 주변(Ambient) 색상입니다.
	 */
	void SetAmbientRGB(const Vector3f& ambientRGB) { ambientRGB_ = ambientRGB; }


	/**
	 * @brief 점광(Point Light)의 확산(Diffuse) 색상을 설정합니다.
	 *
	 * @param diffuseRGB 설정할 확산(Diffuse) 색상입니다.
	 */
	void SetDiffuseRGB(const Vector3f& diffuseRGB) { diffuseRGB_ = diffuseRGB; }


	/**
	 * @brief 점광(Point Light)의 반사(Specular) 색상을 설정합니다.
	 *
	 * @param specular 설정할 반사(Specular) 색상입니다.
	 */
	void SetSpecularRGB(const Vector3f& specularRGB) { specularRGB_ = specularRGB; }


	/**
	 * @brief 점광(Point Light)의 감쇠율 계산에 사용할 상수항을 설정합니다.
	 * 
	 * @param constant 설정할 상수항 값입니다.
	 */
	void SetConstant(float constant) { constant_ = constant; }


	/**
	 * @brief 점광(Point Light)의 감쇠율 계산에 사용할 일차항을 설정합니다.
	 * 
	 * @param linear 설정할 일차항 값입니다.
	 */
	void SetLinear(float linear) { linear_ = linear; }


	/**
	 * @brief 점광(Point Light)의 감쇠율 계산에 사용할 이차항을 설정합니다.
	 * 
	 * @param quadratic 설정할 이차항 값입니다.
	 */
	void SetQuadratic(float quadratic) { quadratic_ = quadratic; }


private:
	/**
	 * @brief 점광의 위치입니다.
	 */
	Vector3f position_;


	/**
	 * @brief 점광의 Ambient 색상입니다.
	 */
	Vector3f ambientRGB_;


	/**
	 * @brief 점광의 Diffuse 색상입니다.
	 */
	Vector3f diffuseRGB_;


	/**
	 * @brief 점광의 Specular 색상입니다.
	 */
	Vector3f specularRGB_;


	/**
	 * @brief 점광의 감쇠율 계산에 사용할 상수항입니다.
	 * 
	 * @see http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+Light+Attenuation
	 */
	float constant_;


	/**
	 * @brief 점광의 감쇠율 계산에 사용할 선형항입니다.
	 * 
	 * @see http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+Light+Attenuation
	 */
	float linear_;


	/**
	 * @brief 점광의 감쇠율 계산에 사용할 이차항입니다.
	 * 
	 * @see http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+Light+Attenuation
	 */
	float quadratic_;
};