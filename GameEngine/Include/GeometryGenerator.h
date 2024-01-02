#pragma once

#include <vector>

#include "Vertex.h"


/**
 * @brief 3D 기하 도형을 생성합니다.
 * 
 * @note 이 클래스의 멤버 변수와 메서드는 모두 static 입니다.
 */
class GeometryGenerator
{
public:
	/**
	 * @brief 3D 큐브의 정점과 인덱스 목록을 생성합니다.
	 * 
	 * @param size 3D 큐브의 X, Y, Z축 방향으로의 크기입니다.
	 * @param outVertices 생성한 큐브의 정점 목록입니다.
	 * @param outIndices  생성한 큐브의 인덱스 목록입니다.
	 */
	static void CreateCube(const Vector3f& size, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);


	/**
	 * @brief 3D 구의 정점과 인덱스 목록을 생성합니다.
	 * 
	 * @param radius 3D 구의 반지름 길이입니다.
	 * @param tessellation 3D 구의 분할 횟수입니다. 크기는 3이상이여야 합니다.
	 * @param outVertices 생성한 구의 정점 목록입니다.
	 * @param outIndices  생성한 구의 인덱스 목록입니다.
	 */
	static void CreateSphere(float radius, uint32_t tessellation, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);
};