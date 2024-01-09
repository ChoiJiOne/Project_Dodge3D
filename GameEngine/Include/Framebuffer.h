#pragma once

#include <cstdint>

#include "IResource.h"


/**
 * @brief 파이프라인 참조 및 렌더링 가능한 프레임 버퍼입니다.
 */
class Framebuffer : public IResource
{
public:
	/**
	 * @brief 프레임 버퍼의 디폴트 생성자입니다.
	 *
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	Framebuffer() = default;


	/**
	 * @brief 프레임 버퍼의 가상 소멸자입니다.
	 */
	virtual ~Framebuffer();


	/**
	 * @brief 프레임 버퍼의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Framebuffer);


	/**
	 * @brief 프레임 버퍼를 생성합니다.
	 *
	 * @param bufferWidth 프레임 버퍼의 가로 크기입니다.
	 * @param bufferHeight 프레임 버퍼의 세로 크기입니다.
	 */
	void Initialize(int32_t bufferWidth, int32_t bufferHeight);


	/**
	 * @brief 프레임 버퍼 내부의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 프레임 버퍼를 초기화합니다.
	 *
	 * @param red 색상 버퍼의 R 값입니다.
	 * @param green 색상 버퍼의 G 값입니다.
	 * @param blue 색상 버퍼의 B 값입니다.
	 * @param alpha 색상 버퍼의 A 값입니다.
	 * @param depth 깊이 버퍼의 초기화 값입니다.
	 * @param stencil 스텐실 버퍼의 초기화 값입니다.
	 */
	void Clear(float red, float green, float blue, float alpha, float depth = 1.0f, uint8_t stencil = 0);


	/**
	 * @brief 프레임 버퍼를 바인딩합니다.
	 */
	void Bind();


	/**
	 * @brief 프레임 버퍼의 바인딩을 해제합니다.
	 */
	void Unbind();


	/**
	 * @brief 프레임 버퍼의 텍스처를 활성화합니다.
	 *
	 * @param unit 활성화 할 텍스처 유닛입니다.
	 */
	void Active(uint32_t unit);


private:
	/**
	 * @brief 바인딩 되었는지 확인합니다.
	 */
	bool bIsBind_ = false;


	/**
	 * @brief 프레임 버퍼 오브젝트의 ID입니다.
	 */
	uint32_t framebufferID_ = 0;


	/**
	 * @brief 컬러 버퍼 오브젝트의 ID입니다.
	 */
	uint32_t colorBufferID_ = 0;


	/**
	 * @brief 깊이 스텐실 버퍼 오브젝트의 ID입니다.
	 */
	uint32_t depthStencilBufferID_ = 0;
};