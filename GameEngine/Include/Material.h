#pragma once

#include "IResource.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief 메시의 기본 재질 리소스입니다.
 */
class Material : public IResource
{
public:
	/**
	 * @brief 재질의 디폴트 생성자입니다.
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
	 * @brief 재질 리소스를 생성합니다.
	 * 
	 * @param ambient 재질의 주변(Ambient) 요소입니다.
	 * @param diffuse 재질의 확산(Diffuse) 요소입니다.
	 * @param specular 재질의 반사(Specular) 요소입니다.
	 * @param shininess 재질의 밝기 요소입니다.
	 */
	void Initialize(const Vector3f& ambient, const Vector3f& diffuse, const Vector3f& specular, float shininess);


	/**
	 * @brief 재질 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


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