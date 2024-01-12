#pragma once

#include <array>

#include "Shader.h"

class Framebuffer; // 프레임 버퍼 리소스를 사용하기 위한 전방 선언입니다.


/**
 * @brief 후처리 효과를 적용하는 셰이더입니다.
 */
class PostEffectShader : public Shader
{
public:
	/**
	 * @brief 후처리 효과 셰이더의 디폴트 생성자입니다.
	 *
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	PostEffectShader() = default;


	/**
	 * @brief 후처리 효과 셰이더의 가상 소멸자입니다.
	 *
	 * @note 후처리 효과 셰이더의 내부에서 할당된 요소를 해제하기 위해서는 반드시 Release를 호출해야 합니다.
	 */
	virtual ~PostEffectShader();


	/**
	 * @brief 후처리 효과 셰이더의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(PostEffectShader);


	/**
	 * @brief GLSL 셰이더 소스 파일을 컴파일하고 셰이더 프로그램을 생성합니다.
	 *
	 * @param vsFile 버텍스 셰이더의 확장자(.vert)를 포함한 경로입니다.
	 * @param fsFile 프레그먼트 셰이더의 확장자(.frag)를 포함한 경로입니다.
	 */
	virtual void Initialize(const std::wstring& vsPath, const std::wstring& fsPath) override;


	/**
	 * @brief 후처리 효과 셰이더의 내부 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 후처리 효과를 적용한 뒤 바인딩된 프레임 버퍼에 전송합니다.
	 * 
	 * @param framebuffer 후처리 효과를 적용할 프레임 버퍼입니다.
	 */
	void BlitEffect(Framebuffer* framebuffer);


protected:
	/**
	 * @brief 후처리 셰이더 내부에서 사용하는 정점입니다.
	 */
	struct VertexPositionTexture
	{
		/**
		 * @brief 위치와 텍스처 정보를 가진 정점의 기본 생성자입니다.
		 */
		VertexPositionTexture() noexcept
			: position_(0.0f, 0.0f, 0.0f)
			, uv_(0.0f, 0.0f) {}


		/**
		 * @brief 위치와 텍스처 정보를 가진 정점의 생성자입니다.
		 *
		 * @param position 정점의 위치입니다.
		 * @param uv 정점의 텍스처 위치입니다.
		 */
		VertexPositionTexture(Vector3f&& position, Vector2f&& uv) noexcept
			: position_(position)
			, uv_(uv) {}


		/**
		 * @brief 위치와 텍스처 정보를 가진 정점의 생성자입니다.
		 *
		 * @param position 정점의 위치입니다.
		 * @param st 정점의 텍스처 위치입니다.
		 */
		VertexPositionTexture(const Vector3f& position, const Vector2f& uv) noexcept
			: position_(position)
			, uv_(uv) {}


		/**
		 * @brief 위치와 텍스처 정보를 가진 정점의 생성자입니다.
		 *
		 * @param x 위치의 X좌표입니다.
		 * @param y 위치의 Y좌표입니다.
		 * @param z 위치의 Z좌표입니다.
		 * @param u 텍스처 위치의 U좌표입니다.
		 * @param v 텍스처 위치의 V좌표입니다.
		 */
		VertexPositionTexture(
			float x, float y, float z,
			float u, float v
		) noexcept
			: position_(x, y, z)
			, uv_(u, v) {}


		/**
		 * @brief 위치와 텍스처 정보를 가진 정점의 생성자입니다.
		 *
		 * @param instance 복사할 정점 인스턴스입니다.
		 */
		VertexPositionTexture(VertexPositionTexture&& instance) noexcept
			: position_(instance.position_)
			, uv_(instance.uv_) {}


		/**
		 * @brief 위치와 텍스처 정보를 가진 정점의 생성자입니다.
		 *
		 * @param instance 복사할 정점 인스턴스입니다.
		 */
		VertexPositionTexture(const VertexPositionTexture& instance) noexcept
			: position_(instance.position_)
			, uv_(instance.uv_) {}


		/**
		 * @brief 위치와 텍스처 정보를 가진 정점의 대입 연산자입니다.
		 *
		 * @param instance 대입할 정점 인스턴스입니다.
		 *
		 * @return 대입한 객체의 참조자를 반환합니다.
		 */
		VertexPositionTexture& operator=(VertexPositionTexture&& instance) noexcept
		{
			if (this == &instance) return *this;

			position_ = instance.position_;
			uv_ = instance.uv_;

			return *this;
		}


		/**
		 * @brief 위치와 텍스처 정보를 가진 정점의 대입 연산자입니다.
		 *
		 * @param instance 대입할 정점 인스턴스입니다.
		 *
		 * @return 대입한 객체의 참조자를 반환합니다.
		 */
		VertexPositionTexture& operator=(const VertexPositionTexture& instance) noexcept
		{
			if (this == &instance) return *this;

			position_ = instance.position_;
			uv_ = instance.uv_;

			return *this;
		}


		/**
		 * @brief 정점의 바이트 보폭 값을 얻습니다.
		 *
		 * @return 정점의 파이트 보폭(Stride) 값을 반환합니다.
		 */
		static uint32_t GetStride()
		{
			return sizeof(VertexPositionTexture);
		}


		/**
		 * @brief 정점의 위치입니다.
		 */
		Vector3f position_;


		/**
		 * @brief 정점의 텍스처 좌표입니다.
		 */
		Vector2f uv_;
	};


protected:
	/**
	 * @brief 프레임 버퍼 정점 목록의 최대 크기입니다.
	 */
	static const int32_t MAX_VERTEX_SIZE = 6;


	/**
	 * @brief 프레임 버퍼의 정점 목록입니다.
	 */
	std::array<VertexPositionTexture, MAX_VERTEX_SIZE> vertices_;


	/**
	 * @brief 정점 버퍼의 오브젝트입니다.
	 */
	uint32_t vertexBufferObject_ = 0;


	/**
	 * @brief 정점 버퍼 목록의 오브젝트입니다.
	 */
	uint32_t vertexArrayObject_ = 0;
};