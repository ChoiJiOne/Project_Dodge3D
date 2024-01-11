#pragma once

#include <vector>

#include "Shader.h"

#include "DirectionalLight.h"

class Camera3D;   // 카메라 오브젝트를 사용하기 위한 전방선언 입니다.
class Material;   // 메터리얼 리소스를 사용하기 위한 전방선언 입니다.
class StaticMesh; // 정적 메시 리소스를 사용하기 위한 전방선언 입니다.


/**
 * @brief 직선광(Directional Light) 효과를 적용하는 셰이더입니다.
 */
class DirectionalLightShader : public Shader
{
public:
	/**
	 * @briref 직선광(Directional Light)의 최대 라이트 수입니다.
	 */
	static const uint32_t MAX_LIGHTS = 5;


public:
	/**
	 * @brief 직선광(Directional Light) 효과를 적용하는 셰이더의 디폴트 생성자입니다.
	 * 
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	DirectionalLightShader() = default;


	/**
	 * @brief 직선광(Directional Light) 효과를 적용하는 셰이더의 가상 소멸자입니다.
	 */
	virtual ~DirectionalLightShader();


	/**
	 * @brief 직선광(Directional Light) 효과를 적용하는 셰이더의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(DirectionalLightShader);


	/**
	 * @brief 직선광(Directional Light) 셰이더에서 카메라와 관련된 유니폼 버퍼를 설정합니다.
	 *
	 * @param camera 설정할 카메라의 포인터입니다.
	 */
	void SetCamera(const Camera3D* camera);


	/**
	 * @brief 직선광(Directional Light) 셰이더의 매터리얼과 관련된 유니폼 버퍼를 설정합니다.
	 *
	 * @param material 설정할 매터리얼의 포인터입니다.
	 */
	void SetMaterial(const Material* material);


	/**
	 * @brief 직선광(Directional Light) 셰이더의 유니폼 버퍼를 설정합니다.
	 * 
	 * @param directionalLight 설정할 직선광(Directional Light)입니다.
	 */
	void SetDirectionalLight(const DirectionalLight& directionalLight);


	/**
	 * @brief 메시에 라이팅 효과를 적용합니다.
	 *
	 * @param world 메시의 월드 행렬입니다.
	 * @param mesh 라이팅 효과를 적용할 메시입니다.
	 * @param shadowMap 셰도우 맵입니다.
	 */
	void DrawMesh3D(const Matrix4x4f& world, const StaticMesh* mesh);
};