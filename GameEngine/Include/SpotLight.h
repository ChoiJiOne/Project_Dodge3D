#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief 점적광(Spot Light)입니다.
 */
class SpotLight
{
public:
	/**
	 * @brief 점적광(Spot Light)의 디폴트 생성자입니다.
	 */
	SpotLight() = default;


	/**
	 * @brief 점적광(Spot Light)의 생성자입니다.
	 *
	 * @param position 점적광의 위치입니다.
	 * @param direction 점적광의 방향입니다.
	 * @param cutOff 점적광의 컷 오프 코사인 값입니다.
	 * @param outerCutOff 점적광의 외부 컷 오프 코사인 값입니다.
	 * @param ambientRGB 점적광의 Ambient 색상입니다.
	 * @param diffuseRGB 점적광의 Diffuse 색상입니다.
	 * @param specularRGB 점적광의 Specular 색상입니다.
	 * @param constant 점적광의 감쇠율 계산에 사용할 상수항입니다.
	 * @param linear 점적광의 감쇠율 계산에 사용할 일차항입니다.
	 * @param quadratic 점적광의 감쇠율 계산에 사용할 이차항입니다.
	 */
	SpotLight(
		const Vector3f& position,
		const Vector3f& direction,
		const float& cutOff,
		const float& outerCutOff,
		const Vector3f& ambientRGB,
		const Vector3f& diffuseRGB,
		const Vector3f& specularRGB,
		const float& constant,
		const float& linear,
		const float& quadratic
	) : position_(position),
		direction_(direction),
		cutOff_(cutOff),
		outerCutOff_(outerCutOff),
		ambientRGB_(ambientRGB),
		diffuseRGB_(diffuseRGB),
		specularRGB_(specularRGB),
		constant_(constant),
		linear_(linear),
		quadratic_(quadratic) {}


	/**
	 * @brief 점적광(Spot Light)의 복사 생성자입니다.
	 *
	 * @param instance 점적광의 내부 프로퍼티를 복사할 인스턴입니다.
	 */
	SpotLight(SpotLight&& instance) noexcept
		: position_(instance.position_)
		, direction_(instance.direction_)
		, cutOff_(instance.cutOff_)
		, outerCutOff_(instance.outerCutOff_)
		, ambientRGB_(instance.ambientRGB_)
		, diffuseRGB_(instance.diffuseRGB_)
		, specularRGB_(instance.specularRGB_)
		, constant_(instance.constant_)
		, linear_(instance.linear_)
		, quadratic_(instance.quadratic_) {}


	/**
	 * @brief 점적광(Spot Light)의 복사 생성자입니다.
	 *
	 * @param instance 점적광의 내부 프로퍼티를 복사할 인스턴입니다.
	 */
	SpotLight(const SpotLight& instance) noexcept
		: position_(instance.position_)
		, direction_(instance.direction_)
		, cutOff_(instance.cutOff_)
		, outerCutOff_(instance.outerCutOff_)
		, ambientRGB_(instance.ambientRGB_)
		, diffuseRGB_(instance.diffuseRGB_)
		, specularRGB_(instance.specularRGB_)
		, constant_(instance.constant_)
		, linear_(instance.linear_)
		, quadratic_(instance.quadratic_) {}


	/**
	 * @brief 점적광(Spot Light)의 가상 소멸자입니다.
	 */
	virtual ~SpotLight() {}


	/**
	 * @brief 점적광의 대입 연산자입니다.
	 *
	 * @param instance 점적광의 내부 프로퍼티를 복사할 인스턴입니다.
	 *
	 * @return 대입한 점적광의 참조자를 반환합니다.
	 */
	SpotLight& operator=(SpotLight&& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;
		direction_ = instance.direction_;
		cutOff_ = instance.cutOff_;
		outerCutOff_ = instance.outerCutOff_;
		ambientRGB_ = instance.ambientRGB_;
		diffuseRGB_ = instance.diffuseRGB_;
		specularRGB_ = instance.specularRGB_;
		constant_ = instance.constant_;
		linear_ = instance.linear_;
		quadratic_ = instance.quadratic_;

		return *this;
	}


	/**
	 * @brief 점적광의 대입 연산자입니다.
	 *
	 * @param instance 점적광의 내부 프로퍼티를 복사할 인스턴입니다.
	 *
	 * @return 대입한 점적광의 참조자를 반환합니다.
	 */
	SpotLight& operator=(const SpotLight& instance) noexcept
	{
		if (this == &instance) return *this;

		position_ = instance.position_;
		direction_ = instance.direction_;
		cutOff_ = instance.cutOff_;
		outerCutOff_ = instance.outerCutOff_;
		ambientRGB_ = instance.ambientRGB_;
		diffuseRGB_ = instance.diffuseRGB_;
		specularRGB_ = instance.specularRGB_;
		constant_ = instance.constant_;
		linear_ = instance.linear_;
		quadratic_ = instance.quadratic_;

		return *this;
	}


	/**
	 * @brief 점적광(Spot Light)의 위치를 얻습니다.
	 *
	 * @return 점적광(Spot Light)의 위치를 반환합니다.
	 */
	Vector3f GetPosition() { return position_; }


	/**
	 * @brief 점적광(Spot Light)의 위치를 얻습니다.
	 *
	 * @return 점적광(Spot Light)의 위치를 반환합니다.
	 */
	const Vector3f& GetPosition() const { return position_; }


	/**
	 * @brief 점적광(Spot Light)의 방향을 얻습니다.
	 *
	 * @return 점적광(Spot Light)의 방향을 반환합니다.
	 */
	Vector3f GetDirection() { return direction_; }


	/**
	 * @brief 점적광(Spot Light)의 방향을 얻습니다.
	 *
	 * @return 점적광(Spot Light)의 방향을 반환합니다.
	 */
	const Vector3f& GetDirection() const { return direction_; }


	/**
	 * @brief 점적광(Spot Light)의 컷 오프 코사인 값을 얻습니다.
	 * 
	 * @return 점적광(Spot Light)의 컷 오프 코사인 값을 반환합니다.
	 */
	float GetCutOff() { return cutOff_; }


	/**
	 * @brief 점적광(Spot Light)의 컷 오프 코사인 값을 얻습니다.
	 *
	 * @return 점적광(Spot Light)의 컷 오프 코사인 값을 반환합니다.
	 */
	const float& GetCutOff() const { return cutOff_; }


	/**
	 * @brief 점적광(Spot Light)의 외부 컷 오프 코사인 값을 얻습니다.
	 *
	 * @return 점적광(Spot Light)의 외부 컷 오프 코사인 값을 반환합니다.
	 */
	float GetOuterCutOff() { return outerCutOff_; }


	/**
	 * @brief 점적광(Spot Light)의 외부 컷 오프 코사인 값을 얻습니다.
	 *
	 * @return 점적광(Spot Light)의 외부 컷 오프 코사인 값을 반환합니다.
	 */
	const float& GetOuterCutOff() const { return outerCutOff_; }
	

	/**
	 * @brief 점적광(Spot Light)의 주변(Ambient) 색상을 얻습니다.
	 *
	 * @return 점적광(Spot Light)의 주변 색상을 반환합니다.
	 */
	Vector3f GetAmbientRGB() { return ambientRGB_; }


	/**
	 * @brief 점적광(Spot Light)의 주변(Ambient) 색상을 얻습니다.
	 *
	 * @return 점적광(Spot Light)의 주변 색상을 반환합니다.
	 */
	const Vector3f& GetAmbientRGB() const { return ambientRGB_; }


	/**
	 * @brief 점적광(Spot Light)의 확산(Diffuse) 색상을 얻습니다.
	 *
	 * @return 점적광(Spot Light)의 확산 색상을 반환합니다.
	 */
	Vector3f GetDiffuseRGB() { return diffuseRGB_; }


	/**
	 * @brief 점적광(Spot Light)의 확산(Diffuse) 색상을 얻습니다.
	 *
	 * @return 점적광(Spot Light)의 확산 색상을 반환합니다.
	 */
	const Vector3f& GetDiffuseRGB() const { return diffuseRGB_; }


	/**
	 * @brief 점적광(Spot Light)의 반사(Specular) 색상을 얻습니다.
	 *
	 * @return 점적광(Spot Light)의 반사 색상을 반환합니다.
	 */
	Vector3f GetSpecularRGB() { return specularRGB_; }


	/**
	 * @brief 점적광(Spot Light)의 반사(Specular) 색상을 얻습니다.
	 *
	 * @return 점적광(Spot Light)의 반사 색상을 반환합니다.
	 */
	const Vector3f& GetSpecularRGB() const { return specularRGB_; }


	/**
	 * @brief 점적광(Spot Light)의 감쇠율 계산에 사용할 상수항을 얻습니다.
	 *
	 * @return 점적광(Spot Light)의 감쇠율 계산에 사용할 상수항을 반환합니다.
	 */
	float GetConstant() { return constant_; }


	/**
	 * @brief 점적광(Spot Light)의 감쇠율 계산에 사용할 상수항을 얻습니다.
	 *
	 * @return 점적광(Spot Light)의 감쇠율 계산에 사용할 상수항을 반환합니다.
	 */
	const float& GetConstant() const { return constant_; }


	/**
	 * @brief 점적광(Spot Light)의 감쇠율 계산에 사용할 일차항을 얻습니다.
	 *
	 * @return 점적광(Spot Light)의 감쇠율 계산에 사용할 일차항을 반환합니다.
	 */
	float GetLinear() { return linear_; }


	/**
	 * @brief 점적광(Spot Light)의 감쇠율 계산에 사용할 일차항을 얻습니다.
	 *
	 * @return 점적광(Spot Light)의 감쇠율 계산에 사용할 일차항을 반환합니다.
	 */
	const float& GetLinear() const { return linear_; }


	/**
	 * @brief 점적광(Spot Light)의 감쇠율 계산에 사용할 이차항을 얻습니다.
	 *
	 * @return 점적광(Spot Light)의 감쇠율 계산에 사용할 이차항을 반환합니다.
	 */
	float GetQuadratic() { return quadratic_; }


	/**
	 * @brief 점적광(Spot Light)의 감쇠율 계산에 사용할 이차항을 얻습니다.
	 *
	 * @return 점적광(Spot Light)의 감쇠율 계산에 사용할 이차항을 반환합니다.
	 */
	const float& GetQuadratic() const { return quadratic_; }


	/**
	 * @brief 점적광(Spot Light)의 위치를 설정합니다.
	 *
	 * @param position 설정할 점적광의 위치입니다.
	 */
	void SetPosition(const Vector3f& position) { position_ = position; }


	/**
	 * @brief 점적광(Spot Light)의 방향을 설정합니다.
	 *
	 * @param direction 설정할 점적광의 방향입니다.
	 */
	void SetDirection(const Vector3f& direction) { direction_ = direction; }


	/**
	 * @brief 점적광(Spot Light)의 컷 오프 코사인 값을 설정합니다.
	 * 
	 * @param cutOff 설정할 컷 오프 코사인 값입니다.
	 */
	void SetCutOff(const float& cutOff) { cutOff_ = cutOff; }


	/**
	 * @brief 점적광(Spot Light)의 외부 컷 오프 코사인 값을 설정합니다.
	 *
	 * @param outerCutOff 설정할 외부 컷 오프 코사인 값입니다.
	 */
	void SetOuterCutOff(const float& outerCutOff) { outerCutOff_ = outerCutOff; }


	/**
	 * @brief 점적광(Spot Light)의 주변(Ambient) 색상을 설정합니다.
	 *
	 * @param ambientRGB 설정할 주변(Ambient) 색상입니다.
	 */
	void SetAmbientRGB(const Vector3f& ambientRGB) { ambientRGB_ = ambientRGB; }


	/**
	 * @brief 점적광(Spot Light)의 확산(Diffuse) 색상을 설정합니다.
	 *
	 * @param diffuseRGB 설정할 확산(Diffuse) 색상입니다.
	 */
	void SetDiffuseRGB(const Vector3f& diffuseRGB) { diffuseRGB_ = diffuseRGB; }


	/**
	 * @brief 점적광(Spot Light)의 반사(Specular) 색상을 설정합니다.
	 *
	 * @param specular 설정할 반사(Specular) 색상입니다.
	 */
	void SetSpecularRGB(const Vector3f& specularRGB) { specularRGB_ = specularRGB; }


	/**
	 * @brief 점적광(Spot Light)의 감쇠율 계산에 사용할 상수항을 설정합니다.
	 *
	 * @param constant 설정할 상수항 값입니다.
	 */
	void SetConstant(float constant) { constant_ = constant; }


	/**
	 * @brief 점적광(Spot Light)의 감쇠율 계산에 사용할 일차항을 설정합니다.
	 *
	 * @param linear 설정할 일차항 값입니다.
	 */
	void SetLinear(float linear) { linear_ = linear; }


	/**
	 * @brief 점적광(Spot Light)의 감쇠율 계산에 사용할 이차항을 설정합니다.
	 *
	 * @param quadratic 설정할 이차항 값입니다.
	 */
	void SetQuadratic(float quadratic) { quadratic_ = quadratic; }


private:
	/**
	 * @brief 점적광의 위치입니다.
	 */
	Vector3f position_;


	/**
	 * @brief 점적광의 방향입니다.
	 */
	Vector3f direction_;


	/**
	 * @brief 점적광의 컷 오프값입니다.
	 *
	 * @note 이 값은 코사인 값입니다.
	 */
	float cutOff_;


	/**
	 * @brief 점적광의 외부 컷 오프값입니다.
	 *
	 * @note 이 값은 코사인 값입니다.
	 */
	float outerCutOff_;


	/**
	 * @brief 점적광의 Ambient 색상입니다.
	 */
	Vector3f ambientRGB_;


	/**
	 * @brief 점적광의 Diffuse 색상입니다.
	 */
	Vector3f diffuseRGB_;


	/**
	 * @brief 점적광의 Specular 색상입니다.
	 */
	Vector3f specularRGB_;
	

	/**
	 * @brief 점적광의 감쇠율 계산에 사용할 상수항입니다.
	 *
	 * @see http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+Light+Attenuation
	 */
	float constant_;


	/**
	 * @brief 점적광의 감쇠율 계산에 사용할 선형항입니다.
	 *
	 * @see http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+Light+Attenuation
	 */
	float linear_;


	/**
	 * @brief 점적광의 감쇠율 계산에 사용할 이차항입니다.
	 *
	 * @see http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+Light+Attenuation
	 */
	float quadratic_;
};