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

void GeometryGenerator::CreateCylinder(float radius, float height, uint32_t tessellation, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices)
{
	ASSERT(tessellation >= 3, "tesselation parameter must be at least 3...");

	outVertices.resize(0);
	outIndices.resize(0);

	height *= 0.5f;

	Vector3f topOffset(0.0f, height, 0.0f);
	uint32_t stride = tessellation + 1;

	for (uint32_t index = 0; index <= tessellation; ++index)
	{
		float angle = TwoPi * static_cast<float>(index) / static_cast<float>(tessellation);
		float dx = MathUtils::Sin(angle);
		float dz = MathUtils::Cos(angle);

		Vector3f normal(dx, 0.0f, dz);
		Vector3f sideOffset(normal.x * radius, normal.y * radius, normal.z * radius);

		Vector2f textureCoordinate(static_cast<float>(index) / static_cast<float>(tessellation), 0.0f);

		outVertices.push_back(Vertex(sideOffset + topOffset, normal, textureCoordinate));
		outVertices.push_back(Vertex(sideOffset - topOffset, normal, textureCoordinate + Vector2f(0.0f, 1.0f)));

		outIndices.push_back((index * 2 + 0));
		outIndices.push_back((index * 2 + 1));
		outIndices.push_back((index * 2 + 2) % (stride * 2));

		outIndices.push_back((index * 2 + 1));
		outIndices.push_back((index * 2 + 3) % (stride * 2));
		outIndices.push_back((index * 2 + 2) % (stride * 2));
	}

	CreateCylinderCap(radius, height, tessellation, true, outVertices, outIndices);
	CreateCylinderCap(radius, height, tessellation, false, outVertices, outIndices);
}

void GeometryGenerator::CreateCone(float radius, float height, uint32_t tessellation, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices)
{
	ASSERT(tessellation >= 3, "tesselation parameter must be at least 3...");

	outVertices.resize(0);
	outIndices.resize(0);

	height *= 0.5f;

	Vector3f topOffset(0.0f, height, 0.0f);
	uint32_t stride = tessellation + 1;

	for (uint32_t index = 0; index <= tessellation; ++index)
	{
		float angle = TwoPi * static_cast<float>(index) / static_cast<float>(tessellation);
		float dx = MathUtils::Sin(angle);
		float dz = MathUtils::Cos(angle);

		float tangle = angle + PiDiv2;
		float tdx = MathUtils::Sin(tangle);
		float tdz = MathUtils::Cos(tangle);

		Vector3f sideOffset(dx * radius, 0.0f, dz * radius);
		Vector2f textureCoordinate(static_cast<float>(index) / static_cast<float>(tessellation), 0.0f);
		Vector3f diff = sideOffset - topOffset;
		Vector3f normal = MathUtils::Normalize(MathUtils::CrossProduct(Vector3f(tdx, 0.0f, tdz), topOffset - diff));

		outVertices.push_back(Vertex(topOffset, normal, Vector2f(0.0f, 0.0f)));
		outVertices.push_back(Vertex(diff, normal, textureCoordinate + Vector2f(0.0f, 1.0f)));

		outIndices.push_back((index * 2 + 0));
		outIndices.push_back((index * 2 + 1) % (stride * 2));
		outIndices.push_back((index * 2 + 3) % (stride * 2));
	}

	CreateCylinderCap(radius, height, tessellation, false, outVertices, outIndices);
}

void GeometryGenerator::CreateCylinderCap(float radius, float height, uint32_t tessellation, bool bIsTop, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices)
{
	for (size_t index = 0; index < tessellation - 2; index++)
	{
		size_t i1 = (index + 1) % tessellation;
		size_t i2 = (index + 2) % tessellation;

		if (bIsTop)
		{
			std::swap(i1, i2);
		}

		const size_t vbase = outVertices.size();
		outIndices.push_back(vbase + 0);
		outIndices.push_back(vbase + i2);
		outIndices.push_back(vbase + i1);
	}

	Vector3f normal(0.0f, 1.0f, 0.0f);
	Vector2f textureScale(-0.5f, -0.5f);

	if (!bIsTop)
	{
		normal = Vector3f(0.0f, -1.0f, 0.0f);
		textureScale = Vector2f(0.5f, -0.5f);
	}

	for (size_t index = 0; index < tessellation; ++index)
	{
		float angle = TwoPi * static_cast<float>(index) / static_cast<float>(tessellation);
		float dx = MathUtils::Sin(angle);
		float dz = MathUtils::Cos(angle);

		Vector3f position = Vector3f(dx * radius, normal.y * height, dz * radius);
		Vector2f textureCoordinate = Vector2f(dx, dz) * textureScale + Vector2f(0.5f, 0.5f);

		outVertices.push_back(Vertex(position, normal, textureCoordinate));
	}
}