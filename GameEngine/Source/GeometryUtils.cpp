#include "GeometryUtils.h"

#include "Assertion.h"
#include "MathUtils.h"

void GeometryUtils::CreateAxisGrid(
	const Vector3f& minPosition, 
	const Vector3f& maxPosition, 
	const float& gap, 
	const Vector4f& color, 
	std::vector<VertexPositionColor>& outVertices, 
	std::vector<uint32_t>& outIndices
)
{
	static Vector4f xAxisColor = Vector4f(1.0f, 0.0f, 0.0f, 1.0f);
	static Vector4f yAxisColor = Vector4f(0.0f, 1.0f, 0.0f, 1.0f);
	static Vector4f zAxisColor = Vector4f(0.0f, 0.0f, 1.0f, 1.0f);

	outVertices.resize(0);
	outIndices.resize(0);

	uint32_t index = 0;
	Vector4f axisColor;
	for (float x = minPosition.x; x <= maxPosition.x; x += gap)
	{
		axisColor = (x == 0.0f) ? zAxisColor : color;

		outVertices.push_back(VertexPositionColor(Vector3f(x, 0.0f, minPosition.z), axisColor));
		outIndices.push_back(index++);

		outVertices.push_back(VertexPositionColor(Vector3f(x, 0.0f, maxPosition.z), axisColor));
		outIndices.push_back(index++);
	}

	for (float z = minPosition.z; z <= maxPosition.z; z += gap)
	{
		Vector4f axisColor = (z == 0.0f) ? xAxisColor : color;

		outVertices.push_back(VertexPositionColor(Vector3f(minPosition.x, 0.0f, z), axisColor));
		outIndices.push_back(index++);

		outVertices.push_back(VertexPositionColor(Vector3f(maxPosition.x, 0.0f, z), axisColor));
		outIndices.push_back(index++);
	}

	outVertices.push_back(VertexPositionColor(Vector3f(0.0f, minPosition.y, 0.0f), yAxisColor));
	outIndices.push_back(index++);

	outVertices.push_back(VertexPositionColor(Vector3f(0.0f, maxPosition.y, 0.0f), yAxisColor));
	outIndices.push_back(index++);
}