#pragma once

#include <vector>

#include "Vertex.h"



/**
 * @brief 3D 기하 도형을 생성합니다.
 * 
 * @note 이 클래스의 모든 멤버 변수와 메서드는 static입니다.
 */
class GeometryGenerator
{
public:
	/**
	 * @brief 3D 큐브를 생성합니다.
	 * 
	 * @param xsize X축 방향으로의 크기입니다.
	 * @param ysize Y축 방향으로의 크기입니다.
	 * @param zsize Z축 방향으로의 크기입니다.
	 * @param outVertices 생성한 큐브의 정점 목록입니다.
	 * @param outIndices 생성한 큐브의 인덱스 목록입니다.
	 */
	static void CreateCube(float xsize, float ysize, float zsize, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);
};