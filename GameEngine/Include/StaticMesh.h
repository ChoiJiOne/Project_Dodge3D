#pragma once

#include <vector>

#include "IResource.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief OpenGL 파이프라인에 바인딩 가능한 정적 메시 리소스입니다.
 */
class StaticMesh : public IResource
{
public:
	/**
	 * @brief 정점(Vertex)입니다.
	 */
	struct Vertex
	{
		/**
		 * @brief 위치 정보를 가진 정점의 기본 생성자입니다.
		 */
		Vertex() noexcept
			: position(0.0f, 0.0f, 0.0f)
			, normal(0.0f, 0.0f, 0.0f)
			, texture(0.0f, 0.0f) {}


		/**
		 * @brief 위치 정보를 가진 정점의 생성자입니다.
		 *
		 * @param p 정점의 위치입니다.
		 * @param n 정점의 법선 벡터입니다.
		 * @param uv 정점의 텍셀입니다.
		 */
		Vertex(Vector3f&& p, Vector3f&& n, Vector2f&& uv) noexcept
			: position(p)
			, normal(n)
			, texture(uv) {}

		
		/**
		 * @brief 위치 정보를 가진 정점의 생성자입니다.
		 *
		 * @param p 정점의 위치입니다.
		 * @param n 정점의 법선 벡터입니다.
		 * @param uv 정점의 텍셀입니다.
		 */
		Vertex(const Vector3f& p, const Vector3f& n, const Vector2f& uv) noexcept
			: position(p)
			, normal(n)
			, texture(uv) {}
		

		/**
		 * @brief 위치 정보를 가진 정점의 생성자입니다.
		 *
		 * @param instance 복사할 정점 인스턴스입니다.
		 */
		Vertex(Vertex&& instance) noexcept
			: position(instance.position)
			, normal(instance.normal)
			, texture(instance.texture) {}


		/**
		 * @brief 위치 정보를 가진 정점의 생성자입니다.
		 *
		 * @param instance 복사할 정점 인스턴스입니다.
		 */
		Vertex(const Vertex& instance) noexcept
			: position(instance.position)
			, normal(instance.normal)
			, texture(instance.texture) {}


		/**
		 * @brief 위치 정보를 가진 정점의 대입 연산자입니다.
		 *
		 * @param instance 대입할 정점 인스턴스입니다.
		 *
		 * @return 대입한 객체의 참조자를 반환합니다.
		 */
		Vertex& operator=(Vertex&& instance) noexcept
		{
			if (this == &instance) return *this;

			position = instance.position;
			normal = instance.normal;
			texture = instance.texture;

			return *this;
		}


		/**
		 * @brief 위치 정보를 가진 정점의 대입 연산자입니다.
		 *
		 * @param instance 대입할 정점 인스턴스입니다.
		 *
		 * @return 대입한 객체의 참조자를 반환합니다.
		 */
		Vertex& operator=(const Vertex& instance) noexcept
		{
			if (this == &instance) return *this;

			position = instance.position;
			normal = instance.normal;
			texture = instance.texture;

			return *this;
		}


		/**
		 * @brief 정점의 바이트 보폭 값을 얻습니다.
		 *
		 * @return 정점의 파이트 보폭(Stride) 값을 반환합니다.
		 */
		static uint32_t GetStride()
		{
			return sizeof(Vertex);
		}


		/**
		 * @brief 정점의 위치입니다.
		 */
		Vector3f position;


		/**
		 * @brief 정점의 법선 벡터입니다.
		 */
		Vector3f normal;


		/**
		 * @brief 정점의 텍셀입니다.
		 */
		Vector2f texture;
	};


public:
	/**
	 * @brief 메시의 디폴트 생성자입니다.
	 * 
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	StaticMesh() = default;


	/**
	 * @brief 메시의 가상 소멸자입니다.
	 * 
	 * @note 메시 내부에서 할당된 요소를 해제하기 위해서는 반드시 Release를 호출해야 합니다.
	 */
	virtual ~StaticMesh();


	/**
	 * @brief 메시의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(StaticMesh);


	/**
	 * @brief 메시 리소스를 생성합니다.
	 * 
	 * @param vertices 메시의 정점 목록입니다.
	 * @param indices 메시의 인덱스 목록입니다.
	 */
	void Initialize(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);


	/**
	 * @brief 메시의 내부 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;

	
	/**
	 * @brief 메시의 인덱스 수를 얻습니다.
	 * 
	 * @return 메시의 인덱스 수를 반환합니다.
	 */
	uint32_t GetIndexCount() const { return indexCount_; }


	/**
	 * @brief 메시의 정점 배열 오브젝트를 얻습니다.
	 * 
	 * @return 메시의 정점 배열 오브젝트를 반환합니다.
	 */
	uint32_t GetVertexArrayObject() const { return vertexArrayObject_; }


private:
	/**
	 * @brief 메시 리소스를 초기화합니다.
	 * 
	 * @param vertexBufferPtr 정점 버퍼의 포인터입니다.
	 * @param vertexBufferSize 정점 버퍼의 크기입니다.
	 * @param indexBufferPtr 인덱스 버퍼의 포인터입니다.
	 * @param indexBufferSize 인덱스 버퍼의 크기입니다.
	 */
	void SetupMesh(const void* vertexBufferPtr, uint32_t vertexBufferSize, const void* indexBufferPtr, uint32_t indexBufferSize);


private:
	/**
	 * @brief 인덱스 버퍼의 수입니다.
	 */
	uint32_t indexCount_ = 0;


	/**
	 * @brief 정점 데이터를 제공하는 데 필요한 모든 상태입니다.
	 * 
	 * @see 
	 * - https://www.khronos.org/opengl/wiki/Vertex_Specification#:~:text=has%20the%20details.-,Vertex%20Array%20Object,-Vertex%20Array%20Object
	 * - https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenVertexArrays.xhtml
	 */
	uint32_t vertexArrayObject_ = 0;


	/**
	 * @brief GPU 상의 정점 버퍼 오브젝트입니다.
	 */
	uint32_t vertexBufferObject_ = 0;


	/**
	 * @brief GPU 상의 인덱스 버퍼 오브젝트입니다.
	 */
	uint32_t indexBufferObject_ = 0;
};