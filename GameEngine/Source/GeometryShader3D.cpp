#include "GeometryShader3D.h"

#include "Assertion.h"
#include "GLAssertion.h"
#include "MathUtils.h"

#include <glad/glad.h>

GeometryShader3D::~GeometryShader3D()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void GeometryShader3D::Initialize(const std::wstring& vsPath, const std::wstring& fsPath)
{
	ASSERT(!bIsInitialized_, "already initialize geometry shader 3d resource...");

	Shader::Initialize(vsPath, fsPath);

	GL_ASSERT(glGenVertexArrays(1, &vertexArrayObject_), "failed to generate 3d geometry vertex array...");
	GL_ASSERT(glGenBuffers(1, &vertexBufferObject_), "failed to generate 3d geometry vertex buffer...");

	GL_ASSERT(glBindVertexArray(vertexArrayObject_), "failed to bind 3d geometry vertex array...");
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_), "failed to bind 3d geometry vertex buffer...");
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, VertexPositionColor::GetStride() * vertices_.size(), reinterpret_cast<const void*>(vertices_.data()), GL_DYNAMIC_DRAW),
		"failed to create a new data store for a 3d geometry buffer object...");

	GL_ASSERT(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VertexPositionColor::GetStride(), (void*)(offsetof(VertexPositionColor, position))),
		"failed to specify the location and data format of the array of generic vertex attributes at index...");
	GL_ASSERT(glEnableVertexAttribArray(0), "failed to enable vertex attrib array...");

	GL_ASSERT(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexPositionColor::GetStride(), (void*)(offsetof(VertexPositionColor, color))),
		"failed to specify the location and data format of the array of generic vertex attributes at index...");
	GL_ASSERT(glEnableVertexAttribArray(1), "failed to enable vertex attrib array...");

	GL_ASSERT(glBindVertexArray(0), "failed to unbind 3d geometry vertex array...");
}

void GeometryShader3D::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	Shader::Release();

	GL_ASSERT(glDeleteBuffers(1, &vertexBufferObject_), "failed to delete 3d geomety vertex buffer...");
	GL_ASSERT(glDeleteVertexArrays(1, &vertexArrayObject_), "failed to delete 3d geometry vertex array object...");
}

void GeometryShader3D::DrawPoints3D(const Matrix4x4f& view, const Matrix4x4f& projection, const std::vector<Vector3f>& positions, const Vector4f& color)
{
	ASSERT(positions.size() <= MAX_VERTEX_SIZE, "overflow 3d point count : %d", static_cast<int32_t>(positions.size()));

	for (std::size_t index = 0; index < positions.size(); ++index)
	{
		vertices_[index] = VertexPositionColor(positions[index], color);
	}
	
	DrawGeometry3D(Matrix4x4f::GetIdentity(), view, projection, EDrawType::Points, static_cast<uint32_t>(positions.size()));
}

void GeometryShader3D::DrawConnectPoints3D(const Matrix4x4f& view, const Matrix4x4f& projection, const std::vector<Vector3f>& positions, const Vector4f& color)
{
	ASSERT(positions.size() <= MAX_VERTEX_SIZE, "overflow 3d point count : %d", static_cast<int32_t>(positions.size()));

	for (std::size_t index = 0; index < positions.size(); ++index)
	{
		vertices_[index] = VertexPositionColor(positions[index], color);
	}

	DrawGeometry3D(Matrix4x4f::GetIdentity(), view, projection, EDrawType::LineStrip, static_cast<uint32_t>(positions.size()));
}

void GeometryShader3D::DrawLine3D(const Matrix4x4f& view, const Matrix4x4f& projection, const Vector3f& fromPosition, const Vector3f& toPosition, const Vector4f& color)
{
	uint32_t vertexCount = 0;

	vertices_[vertexCount++] = VertexPositionColor(fromPosition, color);
	vertices_[vertexCount++] = VertexPositionColor(toPosition, color);

	DrawGeometry3D(Matrix4x4f::GetIdentity(), view, projection, EDrawType::LineStrip, vertexCount);
}

void GeometryShader3D::DrawLine3D(const Matrix4x4f& view, const Matrix4x4f& projection, const Vector3f& fromPosition, const Vector4f& fromColor, const Vector3f& toPosition, const Vector4f& toColor)
{
	uint32_t vertexCount = 0;

	vertices_[vertexCount++] = VertexPositionColor(fromPosition, fromColor);
	vertices_[vertexCount++] = VertexPositionColor(toPosition, toColor);

	DrawGeometry3D(Matrix4x4f::GetIdentity(), view, projection, EDrawType::LineStrip, vertexCount);
}

void GeometryShader3D::DrawAxisAlignedBoundingBox3D(const Matrix4x4f& view, const Matrix4x4f& projection, const Vector3f& minPosition, const Vector3f& maxPosition, const Vector4f& color)
{
	uint32_t vertexCount = 0;

	vertices_[vertexCount++] = VertexPositionColor(Vector3f(maxPosition.x, maxPosition.y, maxPosition.z), color);
	vertices_[vertexCount++] = VertexPositionColor(Vector3f(minPosition.x, maxPosition.y, maxPosition.z), color);

	vertices_[vertexCount++] = VertexPositionColor(Vector3f(minPosition.x, maxPosition.y, maxPosition.z), color);
	vertices_[vertexCount++] = VertexPositionColor(Vector3f(minPosition.x, maxPosition.y, minPosition.z), color);

	vertices_[vertexCount++] = VertexPositionColor(Vector3f(minPosition.x, maxPosition.y, minPosition.z), color);
	vertices_[vertexCount++] = VertexPositionColor(Vector3f(maxPosition.x, maxPosition.y, minPosition.z), color);

	vertices_[vertexCount++] = VertexPositionColor(Vector3f(maxPosition.x, maxPosition.y, minPosition.z), color);
	vertices_[vertexCount++] = VertexPositionColor(Vector3f(maxPosition.x, maxPosition.y, maxPosition.z), color);

	vertices_[vertexCount++] = VertexPositionColor(Vector3f(maxPosition.x, minPosition.y, maxPosition.z), color);
	vertices_[vertexCount++] = VertexPositionColor(Vector3f(minPosition.x, minPosition.y, maxPosition.z), color);

	vertices_[vertexCount++] = VertexPositionColor(Vector3f(minPosition.x, minPosition.y, maxPosition.z), color);
	vertices_[vertexCount++] = VertexPositionColor(Vector3f(minPosition.x, minPosition.y, minPosition.z), color);

	vertices_[vertexCount++] = VertexPositionColor(Vector3f(minPosition.x, minPosition.y, minPosition.z), color);
	vertices_[vertexCount++] = VertexPositionColor(Vector3f(maxPosition.x, minPosition.y, minPosition.z), color);

	vertices_[vertexCount++] = VertexPositionColor(Vector3f(maxPosition.x, minPosition.y, minPosition.z), color);
	vertices_[vertexCount++] = VertexPositionColor(Vector3f(maxPosition.x, minPosition.y, maxPosition.z), color);

	vertices_[vertexCount++] = VertexPositionColor(Vector3f(maxPosition.x, maxPosition.y, maxPosition.z), color);
	vertices_[vertexCount++] = VertexPositionColor(Vector3f(maxPosition.x, minPosition.y, maxPosition.z), color);

	vertices_[vertexCount++] = VertexPositionColor(Vector3f(minPosition.x, maxPosition.y, maxPosition.z), color);
	vertices_[vertexCount++] = VertexPositionColor(Vector3f(minPosition.x, minPosition.y, maxPosition.z), color);

	vertices_[vertexCount++] = VertexPositionColor(Vector3f(minPosition.x, maxPosition.y, minPosition.z), color);
	vertices_[vertexCount++] = VertexPositionColor(Vector3f(minPosition.x, minPosition.y, minPosition.z), color);

	vertices_[vertexCount++] = VertexPositionColor(Vector3f(maxPosition.x, maxPosition.y, minPosition.z), color);
	vertices_[vertexCount++] = VertexPositionColor(Vector3f(maxPosition.x, minPosition.y, minPosition.z), color);

	DrawGeometry3D(Matrix4x4f::GetIdentity(), view, projection, EDrawType::Lines, vertexCount);
}

void GeometryShader3D::DrawAxisGrid3D(const Matrix4x4f& view, const Matrix4x4f& projection, const Vector3f& minPosition, const Vector3f& maxPosition, float gap, const Vector4f& color)
{
	static Vector4f xAxisColor = Vector4f(1.0f, 0.0f, 0.0f, 1.0f);
	static Vector4f yAxisColor = Vector4f(0.0f, 1.0f, 0.0f, 1.0f);
	static Vector4f zAxisColor = Vector4f(0.0f, 0.0f, 1.0f, 1.0f);

	int32_t vertexCount = 0;
	Vector4f axisColor;
	for (float x = minPosition.x; x <= maxPosition.x; x += gap)
	{
		axisColor = MathUtils::NearZero(x) ? zAxisColor : color;

		ASSERT((0 <= vertexCount && vertexCount < MAX_VERTEX_SIZE), "overflow axis grid vertex count : %d", vertexCount);
		vertices_[vertexCount++] = VertexPositionColor(Vector3f(x, 0.0f, minPosition.z), axisColor);

		ASSERT((0 <= vertexCount && vertexCount < MAX_VERTEX_SIZE), "overflow axis grid vertex count : %d", vertexCount);
		vertices_[vertexCount++] = VertexPositionColor(Vector3f(x, 0.0f, maxPosition.z), axisColor);
	}

	for (float z = minPosition.z; z <= maxPosition.z; z += gap)
	{
		axisColor = MathUtils::NearZero(z) ? xAxisColor : color;

		ASSERT((0 <= vertexCount && vertexCount < MAX_VERTEX_SIZE), "overflow axis grid vertex count : %d", vertexCount);
		vertices_[vertexCount++] = VertexPositionColor(Vector3f(minPosition.x, 0.0f, z), axisColor);

		ASSERT((0 <= vertexCount && vertexCount < MAX_VERTEX_SIZE), "overflow axis grid vertex count : %d", vertexCount);
		vertices_[vertexCount++] = VertexPositionColor(Vector3f(maxPosition.x, 0.0f, z), axisColor);
	}

	ASSERT((0 <= vertexCount && vertexCount < MAX_VERTEX_SIZE), "overflow axis grid vertex count : %d", vertexCount);
	vertices_[vertexCount++] = VertexPositionColor(Vector3f(0.0f, minPosition.y, 0.0f), yAxisColor);

	ASSERT((0 <= vertexCount && vertexCount < MAX_VERTEX_SIZE), "overflow axis grid vertex count : %d", vertexCount);
	vertices_[vertexCount++] = VertexPositionColor(Vector3f(0.0f, maxPosition.y, 0.0f), yAxisColor);

	DrawGeometry3D(Matrix4x4f::GetIdentity(), view, projection, EDrawType::Lines, static_cast<uint32_t>(vertexCount));
}

void GeometryShader3D::DrawGeometry3D(const Matrix4x4f& world, const Matrix4x4f& view, const Matrix4x4f& projection, const EDrawType& drawType, uint32_t vertexCount)
{
	ASSERT(drawType != EDrawType::None, "invalid draw type...");

	const void* bufferPtr = reinterpret_cast<const void*>(vertices_.data());
	uint32_t bufferByteSize = static_cast<uint32_t>(VertexPositionColor::GetStride() * vertices_.size());
	WriteDynamicVertexBuffer(vertexBufferObject_, bufferPtr, bufferByteSize);

	Shader::Bind();

	Shader::SetMatrix4x4fParameter("world", world);
	Shader::SetMatrix4x4fParameter("view", view);
	Shader::SetMatrix4x4fParameter("projection", projection);

	GL_ASSERT(glBindVertexArray(vertexArrayObject_), "failed to bind 3d geometry vertex array...");
	GL_ASSERT(glDrawArrays(static_cast<GLenum>(drawType), 0, vertexCount), "failed to draw 3d geometry...");
	GL_ASSERT(glBindVertexArray(0), "failed to unbind 3d geometry vertex array...");

	Shader::Unbind();
}