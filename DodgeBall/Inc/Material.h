#pragma once

#include "IResource.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief 메시의 기본 재질(Material)입니다.
 */
class Material : public IResource
{
public:
	/**
	 * @brief 재질의 디폴트 생성자입니다.
	 * 
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	Material() = default;


	/**
	 * @brief 재질의 가상 소멸자입니다.
	 */
	virtual ~Material();


	/**
	 * @brief 재질의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Material);


	/**
	 * @brief 재질(Material) 리소스를 입니다.
	 *
	 * @param ambientRGB 재질의 주변(Ambient) 색상입니다.
	 * @param diffuseRGB 재질의 확산(Diffuse) 색상입니다.
	 * @param specularRGB 재질의 반사(Specular) 색상입니다.
	 * @param shininess 재질의 밝기 요소입니다.
	 */
	void Initialize(const Vector3f& ambientRGB, const Vector3f& diffuseRGB, const Vector3f& specularRGB, float shininess);


	/**
	 * @brief 재질(Material)의 내부 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;

	
	/**
	 * @brief 재질의 주변(Ambient) 색상을 얻습니다.
	 * 
	 * @return 재질의 주변 색상을 반환합니다.
	 */
	Vector3f GetAmbientRGB() { return ambientRGB_; }


	/**
	 * @brief 재질의 주변(Ambient) 색상을 얻습니다.
	 *
	 * @return 재질의 주변 색상을 반환합니다.
	 */
	const Vector3f& GetAmbientRGB() const { return ambientRGB_; }


	/**
	 * @brief 재질의 확산(Diffuse) 색상을 얻습니다.
	 *
	 * @return 재질의 확산 색상을 반환합니다.
	 */
	Vector3f GetDiffuseRGB() { return diffuseRGB_; }


	/**
	 * @brief 재질의 확산(Diffuse) 색상을 얻습니다.
	 *
	 * @return 재질의 확산 색상을 반환합니다.
	 */
	const Vector3f& GetDiffuseRGB() const { return diffuseRGB_; }


	/**
	 * @brief 재질의 반사(Specular) 색상을 얻습니다.
	 *
	 * @return 재질의 반사 색상을 반환합니다.
	 */
	Vector3f GetSpecularRGB() { return specularRGB_; }


	/**
	 * @brief 재질의 반사(Specular) 색상을 얻습니다.
	 *
	 * @return 재질의 반사 색상을 반환합니다.
	 */
	const Vector3f& GetSpecularRGB() const { return specularRGB_; }


	/**
	 * @brief 재질의 밝기 색상을 얻습니다.
	 *
	 * @return 재질의 밝기 색상을 반환합니다.
	 */
	float GetShininess() { return shininess_; }


	/**
	 * @brief 재질의 밝기 색상을 얻습니다.
	 *
	 * @return 재질의 밝기 색상을 반환합니다.
	 */
	const float& GetShininess() const { return shininess_; }


	/**
	 * @brief 재질의 주변(Ambient) 색상을 설정합니다.
	 * 
	 * @param ambientRGB 설정할 주변(Ambient) 요소입니다.
	 */
	void SetAmbientRGB(const Vector3f& ambientRGB) { ambientRGB_ = ambientRGB; }


	/**
	 * @brief 재질의 확산(Diffuse) 색상을 설정합니다.
	 * 
	 * @param diffuseRGB 설정할 확산(Diffuse) 요소입니다.
	 */
	void SetDiffuseRGB(const Vector3f& diffuseRGB) { diffuseRGB_ = diffuseRGB; }


	/**
	 * @brief 재질의 반사(Specular) 색상을 설정합니다.
	 * 
	 * @param specular 설정할 반사(Specular) 요소입니다.
	 */
	void SetSpecularRGB(const Vector3f& specularRGB) { specularRGB_ = specularRGB; }


	/**
	 * @brief 재질의 밝기 색상을 설정합니다.
	 * 
	 * @param shininess 설정할 밝기 요소입니다.
	 */
	void SetShininess(float shininess) { shininess_ = shininess; }


private:
	/**
	 * @brief 재질의 주변(Ambient) 색상입니다.
	 */
	Vector3f ambientRGB_;


	/**
	 * @brief 재질의 확산(Diffuse) 색상입니다.
	 */
	Vector3f diffuseRGB_;


	/**
	 * @brief 재질의 반사(Specular) 색상입니다.
	 */
	Vector3f specularRGB_;


	/**
	 * @brief 재질의 밝기 요소입니다.
	 */
	float shininess_;
};