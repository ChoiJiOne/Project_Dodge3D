#include "GeometryGenerator.h"

#include "Assertion.h"
#include "MathUtils.h"

void GeometryGenerator::CreateCube(const Vector3f& size, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices)
{
	outVertices.resize(0);
	outIndices.resize(0);

	static const uint32_t faceCount = 6;
	static const Vector3f faceNormals[faceCount] = {
		Vector3f(+0.0f, +0.0f, +1.0f),
		Vector3f(+0.0f, +0.0f, -1.0f),
		Vector3f(+1.0f, +0.0f, +0.0f),
		Vector3f(-1.0f, +0.0f, +0.0f),
		Vector3f(+0.0f, +1.0f, +0.0f),
		Vector3f(+0.0f, -1.0f, +0.0f),
	};

	static const Vector2f textureCoordinates[4] = {
		Vector2f(1.0f, 0.0f),
		Vector2f(1.0f, 1.0f),
		Vector2f(0.0f, 1.0f),
		Vector2f(0.0f, 0.0f),
	};

	Vector3f tsize = Vector3f(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f);

	for (uint32_t face = 0; face < faceCount; ++face)
	{
		const Vector3f& normal = faceNormals[face];
		Vector3f basis = (face >= 4) ? Vector3f(0.0f, 0.0f, 1.0f) : Vector3f(0.0f, 1.0f, 0.0f);

		Vector3f side1 = MathUtils::CrossProduct(normal, basis);
		Vector3f side2 = MathUtils::CrossProduct(normal, side1);

		const size_t vbase = outVertices.size();
		outIndices.push_back(vbase + 0);
		outIndices.push_back(vbase + 2);
		outIndices.push_back(vbase + 1);

		outIndices.push_back(vbase + 0);
		outIndices.push_back(vbase + 3);
		outIndices.push_back(vbase + 2);

		outVertices.push_back(Vertex(((normal - side1 - side2) * tsize), normal, textureCoordinates[0]));
		outVertices.push_back(Vertex(((normal - side1 + side2) * tsize), normal, textureCoordinates[1]));
		outVertices.push_back(Vertex(((normal + side1 + side2) * tsize), normal, textureCoordinates[2]));
		outVertices.push_back(Vertex(((normal + side1 - side2) * tsize), normal, textureCoordinates[3]));
	}
}

void GeometryGenerator::CreateSphere(float radius, uint32_t tessellation, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices)
{
	ASSERT(tessellation >= 3, "tesselation parameter must be at least 3...");

	outVertices.resize(0);
	outIndices.resize(0);

	const uint32_t verticalSegments = tessellation;
	const uint32_t horizontalSegments = tessellation * 2;

	for (uint32_t vertical = 0; vertical <= verticalSegments; ++vertical)
	{
		float v = 1.0f - static_cast<float>(vertical) / static_cast<float>(verticalSegments);
		float latitude = Pi * (static_cast<float>(vertical) / static_cast<float>(verticalSegments)) - PiDiv2;
		float dy = MathUtils::Sin(latitude);
		float dxz = MathUtils::Cos(latitude);

		for (uint32_t horizon = 0; horizon <= horizontalSegments; ++horizon)
		{
			float u = static_cast<float>(horizon) / static_cast<float>(horizontalSegments);
			float longitude = TwoPi * static_cast<float>(horizon) / static_cast<float>(horizontalSegments);
			float dx = dxz * MathUtils::Sin(longitude);
			float dz = dxz * MathUtils::Cos(longitude);

			Vector3f position(radius * dx, radius * dy, radius * dz);
			Vector3f normal(dx, dy, dz);
			Vector2f texture(u, v);

			outVertices.push_back(Vertex(position, normal, texture));
		}
	}

	uint32_t stride = horizontalSegments + 1;
	for (uint32_t vertical = 0; vertical < verticalSegments; ++vertical)
	{
		for (uint32_t horizon = 0; horizon <= horizontalSegments; ++horizon)
		{
			outIndices.push_back((vertical + 0) * stride + (horizon + 0) % stride);
			outIndices.push_back((vertical + 0) * stride + (horizon + 1) % stride);
			outIndices.push_back((vertical + 1) * stride + (horizon + 0) % stride);

			outIndices.push_back((vertical + 0) * stride + (horizon + 1) % stride);
			outIndices.push_back((vertical + 1) * stride + (horizon + 1) % stride);
			outIndices.push_back((vertical + 1) * stride + (horizon + 0) % stride);
		}
	}
}