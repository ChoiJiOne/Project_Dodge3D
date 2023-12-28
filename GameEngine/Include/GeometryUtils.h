#pragma once

#include <vector>

#include "Vertex.h"


/**
 * @brief 기하 도형 관련 확장 기능을 제공합니다.
 * 
 * @note 
 * - 이 클래스의 모든 멤버 변수와 메서드는 모두 static입니다.
 * - 기하 도형은 Cube/Sphere/Icosphere/Geosphere/Torus/Cone/Cylinder/Grid 입니다.
 */
class GeometryUtils
{
public:
	/**
	 * @brief 좌표 공간 격자를 생성합니다.
	 * 
	 * @param minPosition 좌표 공간 격자의 최소값입니다.
	 * @param maxPosition 좌표 공간 격자의 최댓값입니다.
	 * @param gap 격자의 간격입니다.
	 * @param color 격자의 색상입니다.
	 * @param outVertices 생성된 좌표 공간 격자의 정점 버퍼입니다.
	 * @param outIndices 생성된 좌표 공간의 인덱스 버퍼입니다.
	 * 
	 * @note 
	 * - X축의 색상은 RED, Y축의 색상은 GREEN, Z축의 색상은 BLUE입니다.
	 * - 렌더링 시 GL_LINES 옵션으로 설정 후 렌더링해야 합니다.
	 */
	static void CreateAxisGrid(
		const Vector3f& minPosition, 
		const Vector3f& maxPosition,
		const float& gap, 
		const Vector4f& color, 
		std::vector<VertexPositionColor>& outVertices,
		std::vector<uint32_t>& outIndices
	);
};