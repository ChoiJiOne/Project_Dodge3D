#pragma once

#include <cstdint>

#include "IResource.h"


/**
 * @brief 파이프라인 참조 및 깊이값 렌더링 가능한 셰도우 맵입니다.
 */
class ShadowMap : public IResource
{
public:
	/**
	 * @brief 셰도우 맵의 디폴트 생성자입니다.
	 * 
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	ShadowMap() = default;


	/**
	 * @brief 셰도우 맵의 가상 소멸자입니다.
	 */
	virtual ~ShadowMap();


	/**
	 * @brief 셰도우 맵의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(ShadowMap);


	/**
	 * @brief 셰도우 맵을 생성합니다.
	 * 
	 * @param shadowWidth 셰도우 맵의 가로 크기입니다.
	 * @param shadowHeight 셰도우 맵의 세로 크기입니다.
	 */
	void Initialize(uint32_t shadowWidth, uint32_t shadowHeight);


	/**
	 * @brief 셰도우 맵 내부의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 셰도우 맵의 깊이 값을 초기화합니다.
	 */
	void Clear();


	/**
	 * @brief 셰도우 맵을 바인딩합니다.
	 */
	void Bind();


	/**
	 * @brief 셰도우 맵의 바인딩을 해제합니다.
	 */
	void Unbind();


	/**
	 * @brief 셰도우 맵의 텍스처를 활성화합니다.
	 *
	 * @param unit 활성화 할 텍스처 유닛입니다.
	 */
	void Active(uint32_t unit) const;


private:
	/**
	 * @brief 셰도우 맵이 바인딩 되었는지 확인합니다.
	 */
	bool bIsBind_ = false;


	/**
	 * @brief 셰도우 맵의 프레임 버퍼 ID값입니다.
	 */
	uint32_t shadowMapFBO_ = 0;


	/**
	 * @brief 셰도우 맵의 깊이값 버퍼 ID값입니다.
	 */
	uint32_t shadowMapID_ = 0;
};