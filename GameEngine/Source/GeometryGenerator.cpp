#include "GeometryGenerator.h"

#include "Assertion.h"
#include "MathUtils.h"

void GeometryGenerator::CreateCube(float xsize, float ysize, float zsize, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices)
{
	outVertices.resize(0);
	outIndices.resize(0);

	float x = 0.5f * xsize;
	float y = 0.5f * ysize;
	float z = 0.5f * zsize;

	outVertices = {
		Vertex(Vector3f(-x, -y, -z), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(0.0f, 1.0f), Vector3f(), Vector3f()),
		Vertex(Vector3f(-x, +y, -z), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(0.0f, 0.0f), Vector3f(), Vector3f()),
		Vertex(Vector3f(+x, +y, -z), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(1.0f, 0.0f), Vector3f(), Vector3f()),
		Vertex(Vector3f(+x, -y, -z), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(1.0f, 1.0f), Vector3f(), Vector3f()),

		Vertex(Vector3f(-x, -y, +z), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(1.0f, 1.0f), Vector3f(), Vector3f()),
		Vertex(Vector3f(+x, -y, +z), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(0.0f, 1.0f), Vector3f(), Vector3f()),
		Vertex(Vector3f(+x, +y, +z), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(0.0f, 0.0f), Vector3f(), Vector3f()),
		Vertex(Vector3f(-x, +y, +z), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(1.0f, 0.0f), Vector3f(), Vector3f()),

		Vertex(Vector3f(-x, +y, -z), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(0.0f, 1.0f), Vector3f(), Vector3f()),
		Vertex(Vector3f(-x, +y, +z), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(0.0f, 0.0f), Vector3f(), Vector3f()),
		Vertex(Vector3f(+x, +y, +z), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(1.0f, 0.0f), Vector3f(), Vector3f()),
		Vertex(Vector3f(+x, +y, -z), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(1.0f, 1.0f), Vector3f(), Vector3f()),

		Vertex(Vector3f(-x, -y, -z), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(1.0f, 1.0f), Vector3f(), Vector3f()),
		Vertex(Vector3f(+x, -y, -z), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(0.0f, 1.0f), Vector3f(), Vector3f()),
		Vertex(Vector3f(+x, -y, +z), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(0.0f, 0.0f), Vector3f(), Vector3f()),
		Vertex(Vector3f(-x, -y, +z), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(1.0f, 0.0f), Vector3f(), Vector3f()),

		Vertex(Vector3f(-x, -y, +z), Vector3f(-1.0f, 0.0f, 0.0f), Vector2f(0.0f, 1.0f), Vector3f(), Vector3f()),
		Vertex(Vector3f(-x, +y, +z), Vector3f(-1.0f, 0.0f, 0.0f), Vector2f(0.0f, 0.0f), Vector3f(), Vector3f()),
		Vertex(Vector3f(-x, +y, -z), Vector3f(-1.0f, 0.0f, 0.0f), Vector2f(1.0f, 0.0f), Vector3f(), Vector3f()),
		Vertex(Vector3f(-x, -y, -z), Vector3f(-1.0f, 0.0f, 0.0f), Vector2f(1.0f, 1.0f), Vector3f(), Vector3f()),

		Vertex(Vector3f(+x, -y, -z), Vector3f(1.0f, 0.0f, 0.0f),  Vector2f(0.0f, 1.0f), Vector3f(), Vector3f()),
		Vertex(Vector3f(+x, +y, -z), Vector3f(1.0f, 0.0f, 0.0f),  Vector2f(0.0f, 0.0f), Vector3f(), Vector3f()),
		Vertex(Vector3f(+x, +y, +z), Vector3f(1.0f, 0.0f, 0.0f),  Vector2f(1.0f, 0.0f), Vector3f(), Vector3f()),
		Vertex(Vector3f(+x, -y, +z), Vector3f(1.0f, 0.0f, 0.0f),  Vector2f(1.0f, 1.0f), Vector3f(), Vector3f()),
	};

	outIndices = {
		0, 2, 1,
		0, 3, 2,

		4, 6, 5,
		4, 7, 6,

		8, 10, 9,
		8, 11, 10,

		12, 14, 13,
		12, 15, 14,

		16, 18, 17,
		16, 19, 18,

		20, 22, 21,
		20, 23, 22,
	};
}