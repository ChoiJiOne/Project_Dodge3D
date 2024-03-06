#include <glad/glad.h>

#include "Assertion.h"
#include "GeometryShader2D.h"
#include "MathUtils.h"

GeometryShader2D::~GeometryShader2D()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void GeometryShader2D::Initialize(const std::wstring& vsPath, const std::wstring& fsPath)
{
	ASSERT(!bIsInitialized_, "already initialize geometry shader 2d resource...");

	Shader::Initialize(vsPath, fsPath);

	GL_ASSERT(glGenVertexArrays(1, &vertexArrayObject_), "failed to generate 2d geometry vertex array...");
	GL_ASSERT(glGenBuffers(1, &vertexBufferObject_), "failed to generate 2d geometry vertex buffer...");

	GL_ASSERT(glBindVertexArray(vertexArrayObject_), "failed to bind 2d geometry vertex array...");
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_), "failed to bind 2d geometry vertex buffer...");
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, VertexPositionColor::GetStride() * vertices_.size(), reinterpret_cast<const void*>(vertices_.data()), GL_DYNAMIC_DRAW),
		"failed to create a new data store for a 2d geometry buffer object...");

	GL_ASSERT(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VertexPositionColor::GetStride(), (void*)(offsetof(VertexPositionColor, position))),
		"failed to specify the location and data format of the array of generic vertex attributes at index...");
	GL_ASSERT(glEnableVertexAttribArray(0), "failed to enable vertex attrib array...");

	GL_ASSERT(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexPositionColor::GetStride(), (void*)(offsetof(VertexPositionColor, color))),
		"failed to specify the location and data format of the array of generic vertex attributes at index...");
	GL_ASSERT(glEnableVertexAttribArray(1), "failed to enable vertex attrib array...");

	GL_ASSERT(glBindVertexArray(0), "failed to unbind 2d geometry vertex array...");
}

void GeometryShader2D::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	Shader::Release();

	GL_ASSERT(glDeleteBuffers(1, &vertexBufferObject_), "failed to delete 2d geomety vertex buffer...");
	GL_ASSERT(glDeleteVertexArrays(1, &vertexArrayObject_), "failed to delete 2d geometry vertex array object...");
}

void GeometryShader2D::DrawPoints2D(const Matrix4x4f& ortho, const std::vector<Vector2f>& positions, const Vector4f& color, float pointSize)
{
	ASSERT(positions.size() <= MAX_VERTEX_SIZE, "overflow 2d point count : %d", static_cast<int32_t>(positions.size()));
	ASSERT(pointSize >= 0.0f, "invalid 2d point size : %d", pointSize);

	for (std::size_t index = 0; index < positions.size(); ++index)
	{
		vertices_[index] = VertexPositionColor(Vector3f(positions[index].x + 0.5f, positions[index].y + 0.5f, 0.0f), color);
	}

	pointSize_ = pointSize;
	DrawGeometry2D(Matrix4x4f::GetIdentity(), ortho, EDrawType::Points, static_cast<uint32_t>(positions.size()));
}

void GeometryShader2D::DrawConnectPoints2D(const Matrix4x4f& ortho, const std::vector<Vector2f>& positions, const Vector4f& color)
{
	ASSERT(positions.size() <= MAX_VERTEX_SIZE, "overflow 2d point count : %d", static_cast<int32_t>(positions.size()));

	for (std::size_t index = 0; index < positions.size(); ++index)
	{
		vertices_[index] = VertexPositionColor(Vector3f(positions[index].x + 0.5f, positions[index].y + 0.5f, 0.0f), color);
	}

	DrawGeometry2D(Matrix4x4f::GetIdentity(), ortho, EDrawType::LineStrip, static_cast<uint32_t>(positions.size()));
}

void GeometryShader2D::DrawLine2D(const Matrix4x4f& ortho, const Vector2f& fromPosition, const Vector2f& toPosition, const Vector4f& color)
{
	vertices_[0] = VertexPositionColor(Vector3f(fromPosition.x + 0.5f, fromPosition.y + 0.5f, 0.0f), color);
	vertices_[1] = VertexPositionColor(Vector3f(   toPosition.x + 0.5f,  toPosition.y + 0.5f, 0.0f), color);

	DrawGeometry2D(Matrix4x4f::GetIdentity(), ortho, EDrawType::LineStrip, 2);
}

void GeometryShader2D::DrawLine2D(const Matrix4x4f& ortho, const Vector2f& fromPosition, const Vector4f& fromColor, const Vector2f& toPosition, const Vector4f& toColor)
{
	vertices_[0] = VertexPositionColor(Vector3f(fromPosition.x + 0.5f, fromPosition.y + 0.5f, 0.0f), fromColor);
	vertices_[1] = VertexPositionColor(Vector3f(  toPosition.x + 0.5f,   toPosition.y + 0.5f, 0.0f),   toColor);

	DrawGeometry2D(Matrix4x4f::GetIdentity(), ortho, EDrawType::LineStrip, 2);
}

void GeometryShader2D::DrawTriangle2D(const Matrix4x4f& ortho, const Vector2f& fromPosition, const Vector2f& byPosition, const Vector2f& toPosition, const Vector4f& color)
{
	vertices_[0] = VertexPositionColor(Vector3f(fromPosition.x + 0.5f, fromPosition.y + 0.5f, 0.0f), color);
	vertices_[1] = VertexPositionColor(Vector3f(  byPosition.x + 0.5f,   byPosition.y + 0.5f, 0.0f), color);
	vertices_[2] = VertexPositionColor(Vector3f(  toPosition.x + 0.5f,   toPosition.y + 0.5f, 0.0f), color);

	DrawGeometry2D(Matrix4x4f::GetIdentity(), ortho, EDrawType::Triangles, 3);
}

void GeometryShader2D::DrawTriangle2D(const Matrix4x4f& ortho, const Vector2f& fromPosition, const Vector4f& fromColor, const Vector2f& byPosition, const Vector4f& byColor, const Vector2f& toPosition, const Vector4f& toColor)
{
	vertices_[0] = VertexPositionColor(Vector3f(fromPosition.x + 0.5f, fromPosition.y + 0.5f, 0.0f), fromColor);
	vertices_[1] = VertexPositionColor(Vector3f(  byPosition.x + 0.5f,   byPosition.y + 0.5f, 0.0f),   byColor);
	vertices_[2] = VertexPositionColor(Vector3f(  toPosition.x + 0.5f,   toPosition.y + 0.5f, 0.0f),   toColor);

	DrawGeometry2D(Matrix4x4f::GetIdentity(), ortho, EDrawType::Triangles, 3);
}

void GeometryShader2D::DrawWireframeTriangle2D(const Matrix4x4f& ortho, const Vector2f& fromPosition, const Vector2f& byPosition, const Vector2f& toPosition, const Vector4f& color)
{
	vertices_[0] = VertexPositionColor(Vector3f(fromPosition.x + 0.5f, fromPosition.y + 0.5f, 0.0f), color);
	vertices_[1] = VertexPositionColor(Vector3f(  byPosition.x + 0.5f,   byPosition.y + 0.5f, 0.0f), color);
	vertices_[2] = VertexPositionColor(Vector3f(  toPosition.x + 0.5f,   toPosition.y + 0.5f, 0.0f), color);
	vertices_[3] = VertexPositionColor(Vector3f(fromPosition.x + 0.5f, fromPosition.y + 0.5f, 0.0f), color);

	DrawGeometry2D(Matrix4x4f::GetIdentity(), ortho, EDrawType::LineStrip, 4);
}

void GeometryShader2D::DrawWireframeTriangle2D(const Matrix4x4f& ortho, const Vector2f& fromPosition, const Vector4f& fromColor, const Vector2f& byPosition, const Vector4f& byColor, const Vector2f& toPosition, const Vector4f& toColor)
{
	vertices_[0] = VertexPositionColor(Vector3f(fromPosition.x + 0.5f, fromPosition.y + 0.5f, 0.0f), fromColor);
	vertices_[1] = VertexPositionColor(Vector3f(  byPosition.x + 0.5f,   byPosition.y + 0.5f, 0.0f),   byColor);
	vertices_[2] = VertexPositionColor(Vector3f(  toPosition.x + 0.5f,   toPosition.y + 0.5f, 0.0f),   toColor);
	vertices_[3] = VertexPositionColor(Vector3f(fromPosition.x + 0.5f, fromPosition.y + 0.5f, 0.0f), fromColor);

	DrawGeometry2D(Matrix4x4f::GetIdentity(), ortho, EDrawType::LineStrip, 4);
}

void GeometryShader2D::DrawRectangle2D(const Matrix4x4f& ortho, const Vector2f& center, float width, float height, float rotate, const Vector4f& color)
{
	vertices_[0] = VertexPositionColor(Vector3f(center.x - width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f, 0.0f), color);
	vertices_[1] = VertexPositionColor(Vector3f(center.x - width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f, 0.0f), color);
	vertices_[2] = VertexPositionColor(Vector3f(center.x + width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f, 0.0f), color);

	vertices_[3] = VertexPositionColor(Vector3f(center.x + width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f, 0.0f), color);
	vertices_[4] = VertexPositionColor(Vector3f(center.x - width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f, 0.0f), color);
	vertices_[5] = VertexPositionColor(Vector3f(center.x + width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f, 0.0f), color);

	Matrix4x4f transform = MathUtils::CreateTranslation(Vector3f(-center.x, -center.y, 0.0f))
		* MathUtils::CreateRotateZ(rotate)
		* MathUtils::CreateTranslation(Vector3f(+center.x, +center.y, 0.0f));

	DrawGeometry2D(transform, ortho, EDrawType::Triangles, 6);
}

void GeometryShader2D::DrawWireframeRectangle2D(const Matrix4x4f& ortho, const Vector2f& center, float width, float height, float rotate, const Vector4f& color)
{
	vertices_[0] = VertexPositionColor(Vector3f(center.x - width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f, 0.0f), color);
	vertices_[1] = VertexPositionColor(Vector3f(center.x - width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f, 0.0f), color);
	vertices_[2] = VertexPositionColor(Vector3f(center.x + width / 2.0f + 0.5f, center.y + height / 2.0f + 0.5f, 0.0f), color);
	vertices_[3] = VertexPositionColor(Vector3f(center.x + width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f, 0.0f), color);
	vertices_[4] = VertexPositionColor(Vector3f(center.x - width / 2.0f + 0.5f, center.y - height / 2.0f + 0.5f, 0.0f), color);

	Matrix4x4f transform = MathUtils::CreateTranslation(Vector3f(-center.x, -center.y, 0.0f))
		* MathUtils::CreateRotateZ(rotate)
		* MathUtils::CreateTranslation(Vector3f(+center.x, +center.y, 0.0f));

	DrawGeometry2D(transform, ortho, EDrawType::LineStrip, 5);
}

void GeometryShader2D::DrawCircle2D(const Matrix4x4f& ortho, const Vector2f& center, float radius, const Vector4f& color, int32_t sliceCount)
{
	ASSERT(radius >= 0.0f, "invalid circle radius : %f", radius);
	ASSERT(sliceCount <= MAX_VERTEX_SIZE - 2, "overflow circle slice count : %d", sliceCount);

	for (int32_t slice = 1; slice <= sliceCount; ++slice)
	{
		float radian = (static_cast<float>(slice - 1) * TwoPi) / static_cast<float>(sliceCount);
		float x = radius * MathUtils::Cos(radian);
		float y = radius * MathUtils::Sin(radian);

		vertices_[slice] = VertexPositionColor(Vector3f(center.x + x + 0.5f, center.y + y + 0.5f, 0.0f), color);
	}

	vertices_[0] = VertexPositionColor(Vector3f(center.x + 0.5f, center.y + 0.5f, 0.0f), color);
	vertices_[sliceCount + 1] = vertices_[1];
	uint32_t vertexCount = static_cast<uint32_t>(sliceCount + 2);

	DrawGeometry2D(Matrix4x4f::GetIdentity(), ortho, EDrawType::TriangleFan, vertexCount);
}

void GeometryShader2D::DrawWireframeCircle2D(const Matrix4x4f& ortho, const Vector2f& center, float radius, const Vector4f& color, int32_t sliceCount)
{
	ASSERT(radius >= 0.0f, "invalid circle radius : %f", radius);
	ASSERT(sliceCount <= MAX_VERTEX_SIZE, "overflow circle slice count : %d", sliceCount);

	for (int32_t index = 0; index < sliceCount; ++index)
	{
		float radian = (static_cast<float>(index) * TwoPi) / static_cast<float>(sliceCount);
		float x = radius * MathUtils::Cos(radian);
		float y = radius * MathUtils::Sin(radian);

		vertices_[index] = VertexPositionColor(Vector3f(center.x + x + 0.5f, center.y + y + 0.5f, 0.0f), color);
	}

	vertices_[sliceCount] = vertices_[0];
	uint32_t vertexCount = static_cast<uint32_t>(sliceCount + 1);

	DrawGeometry2D(Matrix4x4f::GetIdentity(), ortho, EDrawType::LineStrip, vertexCount);
}

void GeometryShader2D::DrawEllipse2D(const Matrix4x4f& ortho, const Vector2f& center, float xAxis, float yAxis, const Vector4f& color, int32_t sliceCount)
{
	ASSERT(xAxis >= 0.0f, "invalid ellipse x axis : %f", xAxis);
	ASSERT(yAxis >= 0.0f, "invalid ellipse y axis : %f", yAxis);
	ASSERT(sliceCount <= MAX_VERTEX_SIZE - 2, "overflow circle slice count : %d", sliceCount);

	float halfXAxis = xAxis / 2.0f;
	float haflYAxis = yAxis / 2.0f;

	for (int32_t slice = 1; slice <= sliceCount; ++slice)
	{
		float radian = (static_cast<float>(slice - 1) * TwoPi) / static_cast<float>(sliceCount);
		float x = halfXAxis * MathUtils::Cos(radian);
		float y = haflYAxis * MathUtils::Sin(radian);

		vertices_[slice] = VertexPositionColor(Vector3f(center.x + x + 0.5f, center.y + y + 0.5f, 0.0f), color);
	}

	vertices_[0] = VertexPositionColor(Vector3f(center.x + 0.5f, center.y + 0.5f, 0.0f), color);
	vertices_[sliceCount + 1] = vertices_[1];
	uint32_t vertexCount = static_cast<uint32_t>(sliceCount + 2);

	DrawGeometry2D(Matrix4x4f::GetIdentity(), ortho, EDrawType::TriangleFan, vertexCount);
}

void GeometryShader2D::DrawWireframeEllipse2D(const Matrix4x4f& ortho, const Vector2f& center, float xAxis, float yAxis, const Vector4f& color, int32_t sliceCount)
{
	ASSERT(xAxis >= 0.0f, "invalid ellipse x axis : %f", xAxis);
	ASSERT(yAxis >= 0.0f, "invalid ellipse y axis : %f", yAxis);
	ASSERT(sliceCount <= MAX_VERTEX_SIZE, "overflow circle slice count : %d", sliceCount);

	float halfXAxis = xAxis / 2.0f;
	float haflYAxis = yAxis / 2.0f;

	for (int32_t index = 0; index < sliceCount; ++index)
	{
		float radian = (static_cast<float>(index) * TwoPi) / static_cast<float>(sliceCount);
		float x = halfXAxis * MathUtils::Cos(radian);
		float y = haflYAxis * MathUtils::Sin(radian);

		vertices_[index] = VertexPositionColor(Vector3f(center.x + x + 0.5f, center.y + y + 0.5f, 0.0f), color);
	}

	vertices_[sliceCount] = vertices_[0];
	uint32_t vertexCount = static_cast<uint32_t>(sliceCount + 1);

	DrawGeometry2D(Matrix4x4f::GetIdentity(), ortho, EDrawType::LineStrip, vertexCount);
}

void GeometryShader2D::DrawGrid2D(const Matrix4x4f& ortho, float minX, float maxX, float strideX, float minY, float maxY, float strideY, const Vector4f& color)
{
	ASSERT((strideX >= 1.0f && strideY >= 1.0f), "The values of strideX and strideY are too small : %f, %f", strideX, strideY);
	
	float minXPosition = MathUtils::Min<float>(minX, maxX);
	float maxXPosition = MathUtils::Max<float>(minX, maxX);
	float minYPosition = MathUtils::Min<float>(minY, maxY);
	float maxYPosition = MathUtils::Max<float>(minY, maxY);

	uint32_t vertexCount = 0;
	for (float x = minXPosition; x <= maxXPosition; x += strideX)
	{
		ASSERT(vertexCount < MAX_VERTEX_SIZE, "overflow grid vertex count : %d", vertexCount);
		vertices_[vertexCount++] = VertexPositionColor(Vector3f(x + 0.5f, minYPosition + 0.5f, 0.0f), color);
		
		ASSERT(vertexCount < MAX_VERTEX_SIZE, "overflow grid vertex count : %d", vertexCount);
		vertices_[vertexCount++] = VertexPositionColor(Vector3f(x + 0.5f, maxYPosition + 0.5f, 0.0f), color);
	}

	for (float y = minYPosition; y <= maxYPosition; y += strideY)
	{
		ASSERT(vertexCount < MAX_VERTEX_SIZE, "overflow grid vertex count : %d", vertexCount);
		vertices_[vertexCount++] = VertexPositionColor(Vector3f(minXPosition + 0.5f, y + 0.5f, 0.0f), color);
		
		ASSERT(vertexCount < MAX_VERTEX_SIZE, "overflow grid vertex count : %d", vertexCount);
		vertices_[vertexCount++] = VertexPositionColor(Vector3f(maxXPosition + 0.5f, y + 0.5f, 0.0f), color);
	}

	DrawGeometry2D(Matrix4x4f::GetIdentity(), ortho, EDrawType::Lines, vertexCount);
}

void GeometryShader2D::DrawGeometry2D(const Matrix4x4f& transform, const Matrix4x4f& ortho, const EDrawType& drawType, uint32_t vertexCount)
{
	ASSERT(drawType != EDrawType::None, "invalid draw type...");

	const void* bufferPtr = reinterpret_cast<const void*>(vertices_.data());
	uint32_t bufferByteSize = static_cast<uint32_t>(VertexPositionColor::GetStride() * vertices_.size());
	WriteDynamicVertexBuffer(vertexBufferObject_, bufferPtr, bufferByteSize);

	Shader::Bind();
	if (drawType == EDrawType::Points)
	{
		Shader::SetUniform("pointSize", pointSize_);
	}

	Shader::SetUniform("transform", transform);
	Shader::SetUniform("ortho", ortho);

	GL_ASSERT(glBindVertexArray(vertexArrayObject_), "failed to bind 2d geometry vertex array...");
	GL_ASSERT(glDrawArrays(static_cast<GLenum>(drawType), 0, vertexCount), "failed to draw 2d geometry...");
	GL_ASSERT(glBindVertexArray(0), "failed to unbind 2d geometry vertex array...");

	Shader::Unbind();
}