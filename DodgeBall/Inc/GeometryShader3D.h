#pragma once

#include <array>
#include <vector>

#include "Shader.h"


/**
 * @brief 3D 기본 도형을 렌더링하는 셰이더입니다.
 */
class GeometryShader3D : public Shader
{
public:
	/**
	 * @brief 3D 기본 도형을 렌더링하는 셰이더의 디폴트 생성자입니다.
	 *
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	GeometryShader3D() = default;


	/**
	 * @brief 3D 기본 도형을 렌더링하는 셰이더의 가상 소멸자입니다.
	 *
	 * @note 셰이더의 내부에서 할당된 요소를 해제하기 위해서는 반드시 Release를 호출해야 합니다.
	 */
	virtual ~GeometryShader3D();


	/**
	 * @brief 3D 기본 도형을 렌더링하는 셰이더의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(GeometryShader3D);


	/**
	 * @brief GLSL 셰이더 소스 파일을 컴파일하고 셰이더 프로그램을 생성합니다.
	 *
	 * @param vsFile 버텍스 셰이더의 확장자(.vert)를 포함한 경로입니다.
	 * @param fsFile 프레그먼트 셰이더의 확장자(.frag)를 포함한 경로입니다.
	 */
	virtual void Initialize(const std::wstring & vsPath, const std::wstring & fsPath) override;


	/**
	 * @brief 셰이더의 내부 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 화면에 3D 점들을 그립니다.
	 * 
	 * @param view 시야 행렬입니다.
	 * @param projection 투영 행렬입니다.
	 * @param positions 화면 상의 3D 점들입니다.
	 * @param color 점들의 색상입니다.
	 * 
	 * @note 3D 점들의 개수는 MAX_VERTEX_SIZE(10000)의 크기를 넘을 수 없습니다.
	 */
	void DrawPoints3D(const Matrix4x4f& view, const Matrix4x4f& projection, const std::vector<Vector3f>& positions, const Vector4f& color);


	/**
	 * @brief 화면에 점들을 연결한 3D 선을 그립니다.
	 *
	 * @param view 시야 행렬입니다.
	 * @param projection 투영 행렬입니다.
	 * @param positions 화면 상의 3D 점들입니다.
	 * @param color 점들의 색상입니다.
	 *
	 * @note 2D 점들의 개수는 MAX_VERTEX_SIZE(10000)의 크기를 넘을 수 없습니다.
	 */
	void DrawConnectPoints3D(const Matrix4x4f& view, const Matrix4x4f& projection, const std::vector<Vector3f>& positions, const Vector4f& color);


	/**
	 * @brief 화면에 3D 선을 그립니다.
	 * 
	 * @param view 시야 행렬입니다.
	 * @param projection 투영 행렬입니다.
	 * @param fromPosition 선의 시작점입니다.
	 * @param toPosition 선의 끝점입니다.
	 * @param color 선의 색상입니다.
	 */
	void DrawLine3D(const Matrix4x4f& view, const Matrix4x4f& projection, const Vector3f& fromPosition, const Vector3f& toPosition, const Vector4f& color);


	/**
	 * @brief 화면에 3D 선을 그립니다.
	 *
	 * @param view 시야 행렬입니다.
	 * @param projection 투영 행렬입니다.
	 * @param fromPosition 선의 시작점입니다.
	 * @param fromColor 선의 시작점 색상입니다.
	 * @param toPosition 선의 끝점입니다.
	 * @param toColor 선의 끝점 색상입니다.
	 */
	void DrawLine3D(const Matrix4x4f& view, const Matrix4x4f& projection, const Vector3f& fromPosition, const Vector4f& fromColor, const Vector3f& toPosition, const Vector4f& toColor);


	/**
	 * @brief 화면에 3D 쿼드를 그립니다.
	 * 
	 * @param world 월드 행렬입니다.
	 * @param view 시야 행렬입니다.
	 * @param projection 투영 행렬입니다.
	 * @param width 쿼드의 가로 크기입니다.
	 * @param height 쿼드의 세로 크기입니다.
	 * @param color 쿼드의 색상입니다.
	 * 
	 * @note 3D 쿼드는 XY 평면 기준입니다.
	 */
	void DrawQuad3D(const Matrix4x4f& world, const Matrix4x4f& view, const Matrix4x4f& projection, float width, float height, const Vector4f& color);


	/**
	 * @brief 화면에 분할된 3D 쿼드를 그립니다.
	 * 
	 * @param world 월드 행렬입니다.
	 * @param view 시야 행렬입니다.
	 * @param projection 투영 행렬입니다.
	 * @param width 쿼드의 가로 크기입니다.
	 * @param height 쿼드의 세로 크기입니다.
	 * @param rate 쿼드의 분할 비율입니다. 값의 범위는 0.0f ~ 1.0f입니다.
	 * @param color 쿼드의 rate 비율 부분의 색상입니다.
	 * @param bgColor 쿼드의 1.0f - rate 비율 부분의 색상입니다.
	 *
	 * @note 
	 * - 3D 쿼드는 XY 평면 기준입니다.
	 * - 분할 기준입니다.
	 * ┌────────────┬──────────────────┐
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * │    rate    │   1.0f - rate    │
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * └────────────┴──────────────────┘
	 */
	void DrawHorizonDividQuad3D(const Matrix4x4f& world, const Matrix4x4f& view, const Matrix4x4f& projection, float width, float height, float rate, const Vector4f& color, const Vector4f& bgColor);


	/**
	 * @brief 화면에 분할된 3D 쿼드를 그립니다.
	 *
	 * @param world 월드 행렬입니다.
	 * @param view 시야 행렬입니다.
	 * @param projection 투영 행렬입니다.
	 * @param width 쿼드의 가로 크기입니다.
	 * @param height 쿼드의 세로 크기입니다.
	 * @param rate 쿼드의 분할 비율입니다. 값의 범위는 0.0f ~ 1.0f입니다.
	 * @param color 쿼드의 rate 비율 부분의 색상입니다.
	 * @param bgColor 쿼드의 1.0f - rate 비율 부분의 색상입니다.
	 *
	 * @note
	 * - 3D 쿼드는 XY 평면 기준입니다.
	 * - 분할 기준입니다.
	 * ┌─────────────────────────────┐
	 * │                             │
	 * │                             │
	 * │         1.0f - rate         │
	 * │                             │
	 * ├─────────────────────────────┤
	 * │                             │
	 * │            rate             │
	 * │                             │
	 * └─────────────────────────────┘
	 */
	void DrawVerticalDividQuad3D(const Matrix4x4f& world, const Matrix4x4f& view, const Matrix4x4f& projection, float width, float height, float rate, const Vector4f& color, const Vector4f& bgColor);


	/**
	 * @brief 3D 축 정렬 경계 상자(Axis Aligned Bounding Box, AABB)를 화면에 그립니다.
	 *
	 * @param view 시야 행렬입니다.
	 * @param projection 투영 행렬입니다.
	 * @param center 축 경계 상자의 중심 좌표입니다.
	 * @param extents 축 경계 상자의 X/Y/Z 축 방향으로의 크기입니다.
	 * @param color 경계 상자의 색상입니다.
	 */
	void DrawAxisAlignedBoundingBox3D(const Matrix4x4f& view, const Matrix4x4f& projection, const Vector3f& center, const Vector3f& extents, const Vector4f& color);


	/**
	 * @brief 3D 와이어 프레임 구(Sphere)를 화면에 그립니다.
	 * 
	 * @param view 시야 행렬입니다.
	 * @param projection 투영 행렬입니다.
	 * @param center 구의 중심 좌표입니다.
	 * @param radius 구의 반지름 길이입니다.
	 * @param color 구의 색상입니다.
	 * @param sliceCount 각 평면에 평행하는 원의 둘레 절단 횟수입니다. 기본 값은 300입니다.
	 */
	void DrawWireframeSphere3D(const Matrix4x4f& view, const Matrix4x4f& projection, const Vector3f& center, float radius, const Vector4f& color, int32_t sliceCount = 300);


	/**
	 * @brief 화면에 XZ 평면의 격자를 그립니다.
	 * 
	 * @param view 시야 행렬입니다.
	 * @param projection 투영 행렬입니다.
	 * @param minX X좌표의 최소값입니다.
	 * @param maxX X좌표의 최댓값입니다.
	 * @param strideX X축 방향으로의 간격입니다.
	 * @param minZ Z좌표의 최소값입니다.
	 * @param maxZ Z좌표의 최댓값입니다.
	 * @param strideZ Z축 방향으로의 간격입니다.
	 * @param color 격자의 색상입니다.
	 */
	void DrawGrid3D(const Matrix4x4f& view, const Matrix4x4f& projection, float minX, float maxX, float strideX, float minZ, float maxZ, float strideZ, const Vector4f& color);

	
private:
	/**
	 * @brief 3D 기본 도형 그리기를 수행하는 셰이더 내부에서 사용하는 정점입니다.
	 */
	struct VertexPositionColor
	{
		/**
		 * @brief 위치와 색상 정보를 가진 정점의 기본 생성자입니다.
		 */
		VertexPositionColor() noexcept
			: position(0.0f, 0.0f, 0.0f)
			, color(0.0f, 0.0f, 0.0f, 0.0f) {}


		/**
		 * @brief 위치와 색상 정보를 가진 정점의 생성자입니다.
		 *
		 * @param position 정점의 위치입니다.
		 * @param color 정점의 색상입니다.
		 */
		VertexPositionColor(Vector3f&& position, Vector4f&& color) noexcept
			: position(position)
			, color(color) {}


		/**
		 * @brief 위치와 색상 정보를 가진 정점의 생성자입니다.
		 *
		 * @param position 정점의 위치입니다.
		 * @param color 정점의 색상입니다.
		 */
		VertexPositionColor(const Vector3f& position, const Vector4f& color) noexcept
			: position(position)
			, color(color) {}


		/**
		 * @brief 위치와 색상 정보를 가진 정점의 생성자입니다.
		 *
		 * @param x 위치의 X좌표입니다.
		 * @param y 위치의 Y좌표입니다.
		 * @param z 위치의 Z좌표입니다.
		 * @param r 정점 색상의 R입니다.
		 * @param g 정점 색상의 G입니다.
		 * @param b 정점 색상의 B입니다.
		 * @param a 정점 색상의 A입니다.
		 */
		VertexPositionColor(
			float x, float y, float z,
			float r, float g, float b, float a
		) noexcept
			: position(x, y, z)
			, color(r, g, b, a) {}


		/**
		 * @brief 위치와 색상 정보를 가진 정점의 생성자입니다.
		 *
		 * @param instance 복사할 정점 인스턴스입니다.
		 */
		VertexPositionColor(VertexPositionColor&& instance) noexcept
			: position(instance.position)
			, color(instance.color) {}


		/**
		 * @brief 위치와 색상 정보를 가진 정점의 생성자입니다.
		 *
		 * @param instance 복사할 정점 인스턴스입니다.
		 */
		VertexPositionColor(const VertexPositionColor& instance) noexcept
			: position(instance.position)
			, color(instance.color) {}


		/**
		 * @brief 위치와 색상 정보를 가진 정점의 대입 연산자입니다.
		 *
		 * @param instance 대입할 정점 인스턴스입니다.
		 *
		 * @return 대입한 객체의 참조자를 반환합니다.
		 */
		VertexPositionColor& operator=(VertexPositionColor&& instance) noexcept
		{
			if (this == &instance) return *this;

			position = instance.position;
			color = instance.color;

			return *this;
		}


		/**
		 * @brief 위치와 색상 정보를 가진 정점의 대입 연산자입니다.
		 *
		 * @param instance 대입할 정점 인스턴스입니다.
		 *
		 * @return 대입한 객체의 참조자를 반환합니다.
		 */
		VertexPositionColor& operator=(const VertexPositionColor& instance) noexcept
		{
			if (this == &instance) return *this;

			position = instance.position;
			color = instance.color;

			return *this;
		}


		/**
		 * @brief 정점의 바이트 보폭 값을 얻습니다.
		 *
		 * @return 정점의 파이트 보폭(Stride) 값을 반환합니다.
		 */
		static uint32_t GetStride()
		{
			return sizeof(VertexPositionColor);
		}


		/**
		 * @brief 정점의 위치입니다.
		 */
		Vector3f position;


		/**
		 * @brief 정점의 색상입니다.
		 */
		Vector4f color;
	};


	/**
	 * @brief 기본 도형의 그리기 타입입니다.
	 */
	enum class EDrawType : int32_t
	{
		Points = 0x0000,
		Lines = 0x0001,
		LineStrip = 0x0003,
		Triangles = 0x0004,
		TriangleFan = 0x0006,
		None = 0xFFFF,
	};


	/**
	 * @brief 3D 기본 도형 그리기를 수행합니다.
	 *
	 * @param world 월드 행렬입니다.
	 * @param view 시야 행렬입니다.
	 * @param projection 투영 행렬입니다.
	 * @param drawType 그리기 타입입니다.
	 * @param vertexCount 정점 수입니다.
	 */
	void DrawGeometry3D(const Matrix4x4f& world, const Matrix4x4f& view, const Matrix4x4f& projection, const EDrawType& drawType, uint32_t vertexCount);


private:
	/**
	 * @brief 도형 정점 목록의 최대 크기입니다.
	 */
	static const int32_t MAX_VERTEX_SIZE = 10000;


	/**
	 * @brief 도형의 정점 목록입니다.
	 */
	std::array<VertexPositionColor, MAX_VERTEX_SIZE> vertices_;


	/**
	 * @brief 정점 버퍼의 오브젝트입니다.
	 */
	uint32_t vertexBufferObject_ = 0;


	/**
	 * @brief 정점 버퍼 목록의 오브젝트입니다.
	 */
	uint32_t vertexArrayObject_ = 0;
};