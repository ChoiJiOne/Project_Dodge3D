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

void GeometryGenerator::CreateSphere(float radius, uint32_t sliceCount, uint32_t stackCount, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices)
{
	outVertices.resize(0);
	outIndices.resize(0);
	
	outVertices.push_back(Vertex(Vector3f(0.0f, +radius, 0.0f), Vector3f(0.0f, +1.0f, 0.0f), Vector2f(0.0f, 0.0f), Vector3f(), Vector3f()));
	for (uint32_t stack = 1; stack <= stackCount - 1; ++stack)
	{
		float phi = Pi * (static_cast<float>(stack) / static_cast<float>(stackCount));

		for (uint32_t slice = 0; slice <= sliceCount; ++slice)
		{
			float theta = TwoPi * (static_cast<float>(slice) / static_cast<float>(sliceCount));

			Vector3f position = Vector3f(
				radius * MathUtils::Sin(phi) * MathUtils::Cos(theta), 
				radius * MathUtils::Cos(phi), 
				radius * MathUtils::Sin(phi) * MathUtils::Sin(theta)
			);
			Vector3 normal = MathUtils::Normalize(position);
			Vector2f texture = Vector2f(theta / TwoPi, 1.0f - phi / Pi);

			outVertices.push_back(Vertex(position, normal, texture, Vector3f(), Vector3f()));
		}
	}
	outVertices.push_back(Vertex(Vector3f(0.0f, -radius, 0.0f), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(0.0f, 1.0f), Vector3f(), Vector3f()));
	
	for (uint32_t i = 1; i <= sliceCount; ++i)
	{
		outIndices.push_back(0);
		outIndices.push_back(i + 1);
		outIndices.push_back(i + 0);
	}

	UINT ringVertexCount = sliceCount + 1;
	for (uint32_t stack = 0; stack < stackCount - 2; ++stack)
	{
		for (uint32_t slice = 0; slice < sliceCount; ++slice)
		{
			outIndices.push_back(1 + (stack + 0) * ringVertexCount + (slice + 0));
			outIndices.push_back(1 + (stack + 1) * ringVertexCount + (slice + 0));
			outIndices.push_back(1 + (stack + 0) * ringVertexCount + (slice + 1));

			outIndices.push_back(1 + (stack + 1) * ringVertexCount + (slice + 0));
			outIndices.push_back(1 + (stack + 1) * ringVertexCount + (slice + 1));
			outIndices.push_back(1 + (stack + 0) * ringVertexCount + (slice + 1));
		}
	}

	uint32_t southPoleIndex = static_cast<uint32_t>(outVertices.size()) - 1;
	uint32_t baseIndex = southPoleIndex - ringVertexCount;
	for (uint32_t slice = 0; slice < sliceCount; ++slice)
	{
		outIndices.push_back(southPoleIndex);
		outIndices.push_back(baseIndex + (slice + 1));
		outIndices.push_back(baseIndex + (slice + 0));
	}
}