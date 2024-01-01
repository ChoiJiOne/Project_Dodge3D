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
		Vertex(Vector3f(-x, -y, -z), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(0.0f, 1.0f)),
		Vertex(Vector3f(-x, +y, -z), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(+x, +y, -z), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(1.0f, 0.0f)),
		Vertex(Vector3f(+x, -y, -z), Vector3f(0.0f, 0.0f, -1.0f), Vector2f(1.0f, 1.0f)),

		Vertex(Vector3f(-x, -y, +z), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(1.0f, 1.0f)),
		Vertex(Vector3f(+x, -y, +z), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(0.0f, 1.0f)),
		Vertex(Vector3f(+x, +y, +z), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(-x, +y, +z), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(1.0f, 0.0f)),

		Vertex(Vector3f(-x, +y, -z), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(0.0f, 1.0f)),
		Vertex(Vector3f(-x, +y, +z), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(+x, +y, +z), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(1.0f, 0.0f)),
		Vertex(Vector3f(+x, +y, -z), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(1.0f, 1.0f)),

		Vertex(Vector3f(-x, -y, -z), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(1.0f, 1.0f)),
		Vertex(Vector3f(+x, -y, -z), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(0.0f, 1.0f)),
		Vertex(Vector3f(+x, -y, +z), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(-x, -y, +z), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(1.0f, 0.0f)),

		Vertex(Vector3f(-x, -y, +z), Vector3f(-1.0f, 0.0f, 0.0f), Vector2f(0.0f, 1.0f)),
		Vertex(Vector3f(-x, +y, +z), Vector3f(-1.0f, 0.0f, 0.0f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(-x, +y, -z), Vector3f(-1.0f, 0.0f, 0.0f), Vector2f(1.0f, 0.0f)),
		Vertex(Vector3f(-x, -y, -z), Vector3f(-1.0f, 0.0f, 0.0f), Vector2f(1.0f, 1.0f)),

		Vertex(Vector3f(+x, -y, -z), Vector3f(1.0f, 0.0f, 0.0f),  Vector2f(0.0f, 1.0f)),
		Vertex(Vector3f(+x, +y, -z), Vector3f(1.0f, 0.0f, 0.0f),  Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(+x, +y, +z), Vector3f(1.0f, 0.0f, 0.0f),  Vector2f(1.0f, 0.0f)),
		Vertex(Vector3f(+x, -y, +z), Vector3f(1.0f, 0.0f, 0.0f),  Vector2f(1.0f, 1.0f)),
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

	ComputeTangent(outVertices, outIndices);
}

void GeometryGenerator::CreateSphere(float radius, uint32_t sliceCount, uint32_t stackCount, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices)
{
	outVertices.resize(0);
	outIndices.resize(0);
	
	outVertices.push_back(Vertex(Vector3f(0.0f, +radius, 0.0f), Vector3f(0.0f, +1.0f, 0.0f), Vector2f(0.0f, 0.0f)));
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

			outVertices.push_back(Vertex(position, normal, texture));
		}
	}
	outVertices.push_back(Vertex(Vector3f(0.0f, -radius, 0.0f), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(0.0f, 1.0f)));
	
	for (uint32_t i = 1; i <= sliceCount; ++i)
	{
		outIndices.push_back(0);
		outIndices.push_back(i + 1);
		outIndices.push_back(i + 0);
	}

	uint32_t ringVertexCount = sliceCount + 1;
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

	ComputeTangent(outVertices, outIndices);
}

void GeometryGenerator::CreateCylinder(float radius, float height, uint32_t sliceCount, uint32_t stackCount, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices)
{
	outVertices.resize(0);
	outIndices.resize(0);

	for (uint32_t stack = 0; stack <= stackCount; ++stack)
	{
		float y = -0.5f * height + height * static_cast<float>(stack) / static_cast<float>(stackCount);
		float theta = TwoPi / sliceCount;

		for (uint32_t slice = 0; slice <= sliceCount; ++slice)
		{
			float c = MathUtils::Cos(static_cast<float>(slice) * theta);
			float s = MathUtils::Sin(static_cast<float>(slice) * theta);
			float u = static_cast<float>(slice) / static_cast<float>(sliceCount);
			float v = static_cast<float>(stack) / static_cast<float>(stackCount);

			Vector3f tangent = (Vector3f(-s, 0.0f, c));
			Vector3f bitangent = MathUtils::Normalize(Vector3f(radius * c, -height, radius * s));
			Vector3f normal = MathUtils::Normalize(MathUtils::CrossProduct(tangent, bitangent));
			
			outVertices.push_back(Vertex(Vector3f(radius * c, y, radius * s), normal, Vector2f(u, v), tangent, bitangent));
		}
	}

	uint32_t ringVertexCount = sliceCount + 1;
	for (uint32_t stack = 0; stack < stackCount; ++stack)
	{
		for (uint32_t slice = 0; slice < sliceCount; ++slice)
		{
			outIndices.push_back((stack + 0) * ringVertexCount + slice + 0);
			outIndices.push_back((stack + 1) * ringVertexCount + slice + 1);
			outIndices.push_back((stack + 1) * ringVertexCount + slice + 0);

			outIndices.push_back((stack + 0) * ringVertexCount + slice + 0);
			outIndices.push_back((stack + 0) * ringVertexCount + slice + 1);
			outIndices.push_back((stack + 1) * ringVertexCount + slice + 1);
		}
	}
}

void GeometryGenerator::CreateXYQuad(float xsize, float ysize, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices)
{
	float x = 0.5f * xsize;
	float y = 0.5f * ysize;

	outVertices = {
		Vertex(Vector3f(-x, -y, 0.0f), Vector3f(0.0f, 0.0f, +1.0f), Vector2f(0.0f, 1.0f)),
		Vertex(Vector3f(+x, -y, 0.0f), Vector3f(0.0f, 0.0f, +1.0f), Vector2f(1.0f, 1.0f)),
		Vertex(Vector3f(+x, +y, 0.0f), Vector3f(0.0f, 0.0f, +1.0f), Vector2f(1.0f, 0.0f)),
		Vertex(Vector3f(-x, +y, 0.0f), Vector3f(0.0f, 0.0f, +1.0f), Vector2f(0.0f, 0.0f)),
	};

	outIndices = {
		0, 1, 2,
		0, 2, 3,
	};

	ComputeTangent(outVertices, outIndices);
}

void GeometryGenerator::CreateYZQuad(float ysize, float zsize, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices)
{
	float y = 0.5f * ysize;
	float z = 0.5f * zsize;

	outVertices = {
		Vertex(Vector3f(0.0f, -y, -z), Vector3f(+1.0f, 0.0f, 0.0f), Vector2f(0.0f, 1.0f)),
		Vertex(Vector3f(0.0f, +y, -z), Vector3f(+1.0f, 0.0f, 0.0f), Vector2f(1.0f, 1.0f)),
		Vertex(Vector3f(0.0f, +y, +z), Vector3f(+1.0f, 0.0f, 0.0f), Vector2f(1.0f, 0.0f)),
		Vertex(Vector3f(0.0f, -y, +z), Vector3f(+1.0f, 0.0f, 0.0f), Vector2f(0.0f, 0.0f)),
	};

	outIndices = {
		0, 1, 2,
		0, 2, 3,
	};

	ComputeTangent(outVertices, outIndices);
}

void GeometryGenerator::CreateXZQuad(float xsize, float zsize, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices)
{
	float x = 0.5f * xsize;
	float z = 0.5f * zsize;

	outVertices = {
		Vertex(Vector3f(-x, 0.0f, -z), Vector3f(0.0f, +1.0f, 0.0f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(-x, 0.0f, +z), Vector3f(0.0f, +1.0f, 0.0f), Vector2f(0.0f, 1.0f)),
		Vertex(Vector3f(+x, 0.0f, +z), Vector3f(0.0f, +1.0f, 0.0f), Vector2f(1.0f, 1.0f)),
		Vertex(Vector3f(+x, 0.0f, -z), Vector3f(0.0f, +1.0f, 0.0f), Vector2f(1.0f, 0.0f)),
	};

	outIndices = {
		0, 1, 2,
		0, 2, 3,
	};

	ComputeTangent(outVertices, outIndices);
}

void GeometryGenerator::ComputeTangent(std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices)
{
	for (std::size_t index = 0; index < outIndices.size(); index += 3)
	{
		const Vertex& v0 = outVertices[outIndices[index + 0]];
		const Vertex& v1 = outVertices[outIndices[index + 1]];
		const Vertex& v2 = outVertices[outIndices[index + 2]];

		Vector3f e0 = v1.position - v0.position;
		Vector3f e1 = v2.position - v0.position;
		Vector2f deltaUV0 = v1.texture - v0.texture;
		Vector2f deltaUV1 = v2.texture - v0.texture;

		float f = 1.0f / MathUtils::CrossProduct(deltaUV0, deltaUV1);

		Vector3f tangent = MathUtils::Normalize(Vector3f(
			f * (deltaUV1.y * e0.x - deltaUV0.y * e1.x), 
			f * (deltaUV1.y * e0.y - deltaUV0.y * e1.y), 
			f * (deltaUV1.y * e0.z - deltaUV0.y * e1.z)
		));
		
		outVertices[outIndices[index + 0]].tangent = tangent;
		outVertices[outIndices[index + 0]].bitangent = MathUtils::Normalize(MathUtils::CrossProduct(v0.normal, tangent));

		outVertices[outIndices[index + 1]].tangent = tangent;
		outVertices[outIndices[index + 1]].bitangent = MathUtils::Normalize(MathUtils::CrossProduct(v1.normal, tangent));

		outVertices[outIndices[index + 2]].tangent = tangent;
		outVertices[outIndices[index + 2]].bitangent = MathUtils::Normalize(MathUtils::CrossProduct(v2.normal, tangent));
	}
}
