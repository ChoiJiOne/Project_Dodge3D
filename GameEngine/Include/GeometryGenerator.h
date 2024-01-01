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


	/**
	 * @brief 3D 구를 생성합니다.
	 * 
	 * @param radius 구의 반지름 길이입니다.
	 * @param sliceCount 구를 Y축과 평행한 방향으로 자를 횟수입니다.
	 * @param stackCount 구를 XZ평면과 평행한 방향으로 자를 횟수입니다.
	 * @param outVertices 생성한 구의 정점 목록입니다.
	 * @param outIndices 생성한 구의 인덱스 목록입니다.	 
	 */
	static void CreateSphere(float radius, uint32_t sliceCount, uint32_t stackCount, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);


	/**
	 * @brief 3D 원기둥을 생성합니다.
	 * 
	 * @param radius 원기둥의 반지름 길입니다.
	 * @param height 원기둥의 높이입니다.
	 * @param sliceCount 원기둥을 Y축과 평행한 방향으로 자를 횟수입니다.
	 * @param stackCount 원기둥을 XZ평면과 평행한 방향으로 자를 횟수입니다.
	 * @param outVertices 생성한 원기둥의 정점 목록입니다.
	 * @param outIndices 생성한 원기둥의 인덱스 목록입니다.
	 */
	static void CreateCylinder(float radius, float height, uint32_t sliceCount, uint32_t stackCount, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);


	/**
	 * @brief XY 평면의 쿼드를 생성합니다.
	 * 
	 * @param xsize 쿼드의 X축 방향으로의 크기입니다.
	 * @param ysize 쿼드의 y축 방향으로의 크기입니다.
	 * @param outVertices 생성한 쿼드의 정점 목록입니다.
	 * @param outIndices 생성한 쿼드의 인덱스 목록입니다.
	 */
	static void CreateXYQuad(float xsize, float ysize, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);


	/**
	 * @brief YZ 평면의 쿼드를 생성합니다.
	 * 
	 * @param ysize 쿼드의 Y축 방향으로의 크기입니다.
	 * @param zsize 쿼드의 Z축 방향으로의 크기입니다.
	 * @param outVertices 생성한 쿼드의 정점 목록입니다.
	 * @param outIndices 생성한 쿼드의 인덱스 목록입니다.
	 */
	static void CreateYZQuad(float ysize, float zsize, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);


	/**
	 * @brief XZ 평면의 쿼드를 생성합니다.
	 * 
	 * @param xsize 쿼드의 X축 방향으로의 크기입니다.
	 * @param zsize 쿼드의 Z축 방향으로의 크기입니다.
	 * @param outVertices 생성한 쿼드의 정점 목록입니다.
	 * @param outIndices 생성한 쿼드의 인덱스 목록입니다.
	 */
	static void CreateXZQuad(float xsize, float zsize, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);


private:
	/**
	 * @brief 정점의 접선 벡터와 쌍벡터를 계산합니다.
	 * 
	 * @param outVertices 접선 벡터와 쌍벡터를 계산할 정점 목록입니다.
	 * @param outIndices 접선 벡터와 쌍벡터를 계산할 인덱스 목록입니다.
	 */
	static void ComputeTangent(std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);
};