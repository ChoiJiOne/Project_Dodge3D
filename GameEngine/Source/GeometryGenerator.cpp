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