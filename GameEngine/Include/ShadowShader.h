#pragma once

#include "Shader.h"

class StaticMesh; // 정적 메시 리소스를 사용하기 위한 전방선언 입니다.
class Light;      // 라이트 오브젝트를 사용하기 위한 전방선언 입니다.


/**
 * @brief 셰도우 효과를 적용하는 셰이더입니다.
 * 
 * @note 이 셰이더는 엔진 내부에서 생성하는 셰이더입니다. 외부에서 초기화하면 안됩니다.
 */
class ShadowShader : public Shader
{
public:
	/**
	 * @brief 셰도우 효과를 적용하는 셰이더의 디폴트 생성자입니다.
	 *
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	ShadowShader() = default;


	/**
	 * @brief 셰도우 효과를 적용하는 셰이더의 가상 소멸자입니다.
	 *
	 * @note 셰이더의 내부에서 할당된 요소를 해제하기 위해서는 반드시 Release를 호출해야 합니다.
	 */
	virtual ~ShadowShader();


	/**
	 * @brief 셰도우 효과를 적용하는 셰이더의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(ShadowShader);


	/**
	 * @brief 셰도우 셰이더의 라이트와 관련된 유니폼 버퍼를 설정합니다.
	 * 
	 * @param light 설정할 라이트의 포인터입니다.
	 */
	void SetLight(const Light* light);


	/**
	 * @brief 깊이 버퍼에 메시의 깊이 값을 렌더링합니다.
	 *
	 * @param world 메시의 월드 행렬입니다.
	 * @param mesh 라이팅 효과를 적용할 메시입니다.
	 */
	void DrawMesh3D(const Matrix4x4f& world, const StaticMesh* mesh);
};