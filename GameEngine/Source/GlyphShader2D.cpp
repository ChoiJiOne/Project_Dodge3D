#include <glad/glad.h>

#include "Assertion.h"
#include "GlyphShader2D.h"
#include "TTFont.h"

GlyphShader2D::~GlyphShader2D()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void GlyphShader2D::Initialize(const std::wstring& vsPath, const std::wstring& fsPath)
{
	ASSERT(!bIsInitialized_, "already initialize glyph shader 2d resource...");

	Shader::Initialize(vsPath, fsPath);

	GL_ASSERT(glGenVertexArrays(1, &vertexArrayObject_), "failed to generate glyph vertex array...");
	GL_ASSERT(glGenBuffers(1, &vertexBufferObject_), "failed to generate glyph vertex buffer...");

	GL_ASSERT(glBindVertexArray(vertexArrayObject_), "failed to bind glyph vertex array...");
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject_), "failed to bind glyph vertex buffer...");
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, VertexPositionTexture::GetStride() * vertices_.size(), reinterpret_cast<const void*>(vertices_.data()), GL_DYNAMIC_DRAW),
		"failed to create a new data store for a glyph buffer object...");

	GL_ASSERT(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VertexPositionTexture::GetStride(), (void*)(offsetof(VertexPositionTexture, position))),
		"failed to specify the location and data format of the array of generic vertex attributes at index...");
	GL_ASSERT(glEnableVertexAttribArray(0), "failed to enable vertex attrib array...");

	GL_ASSERT(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VertexPositionTexture::GetStride(), (void*)(offsetof(VertexPositionTexture, texture))),
		"failed to specify the location and data format of the array of generic vertex attributes at index...");
	GL_ASSERT(glEnableVertexAttribArray(1), "failed to enable vertex attrib array...");

	GL_ASSERT(glBindVertexArray(0), "failed to unbind glyph vertex array...");

	Shader::Bind();
	orthoLocation_ = GetUniformLocation("ortho");
	glyphColorLocation_ = GetUniformLocation("glyphColor");
	Shader::Unbind();
}

void GlyphShader2D::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	Shader::Release();

	GL_ASSERT(glDeleteBuffers(1, &vertexBufferObject_), "failed to delete glyph vertex buffer...");
	GL_ASSERT(glDeleteVertexArrays(1, &vertexArrayObject_), "failed to delete glyph vertex array object...");
}

void GlyphShader2D::DrawText2D(const Matrix4x4f& ortho, const TTFont* font, const std::wstring& text, const Vector2f& center, const Vector4f& color)
{
	ASSERT(text.length() <= MAX_STRING_LEN, L"overflow text length for draw %d...", text.length());
	ASSERT(font != nullptr, "invalid font resource...");

	int32_t vertexCount = UpdateGlyphVertexBuffer(font, text, center);

	const void* bufferPtr = reinterpret_cast<const void*>(vertices_.data());
	uint32_t bufferByteSize = static_cast<uint32_t>(VertexPositionTexture::GetStride() * vertices_.size());
	WriteDynamicVertexBuffer(vertexBufferObject_, bufferPtr, bufferByteSize);

	Shader::Bind();

	GL_ASSERT(glActiveTexture(GL_TEXTURE0), "failed to active glyph texture atlas...");
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, font->GetGlyphAtlasID()), "failed to bind glyph texture atlas...");

	Shader::SetUniform("ortho", ortho);
	Shader::SetUniform("glyphColor", color);

	glBindVertexArray(vertexArrayObject_);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glBindVertexArray(0);

	Shader::Unbind();
}

uint32_t GlyphShader2D::UpdateGlyphVertexBuffer(const TTFont* font, const std::wstring& text, const Vector2f& center)
{
	float glyphAtlasSize = static_cast<float>(font->GetGlyphAtlasSize());

	float textWidth = 0.0f;
	float textHeight = 0.0f;
	font->MeasureText(text, textWidth, textHeight);

	Vector2f position(center.x - textWidth / 2.0f, center.y + textHeight / 2.0f);

	int32_t vertexCount = 0;
	for (const auto& unicode : text)
	{
		const Glyph& glyph = font->GetGlyph(static_cast<int32_t>(unicode));

		float unicodeWidth = static_cast<float>(glyph.position1.x - glyph.position0.x);
		float unicodeHeight = static_cast<float>(glyph.position1.y - glyph.position0.y);

		vertices_[vertexCount + 0].position = Vector3f(position.x + glyph.xoffset, position.y + glyph.yoffset, 0.0f);
		vertices_[vertexCount + 0].texture  = Vector2f(static_cast<float>(glyph.position0.x) / glyphAtlasSize, static_cast<float>(glyph.position0.y) / glyphAtlasSize);

		vertices_[vertexCount + 1].position = Vector3f(position.x + glyph.xoffset, position.y + unicodeHeight + glyph.yoffset, 0.0f);
		vertices_[vertexCount + 1].texture  = Vector2f(static_cast<float>(glyph.position0.x) / glyphAtlasSize, static_cast<float>(glyph.position1.y) / glyphAtlasSize);


		vertices_[vertexCount + 2].position = Vector3f(position.x + glyph.xoffset + unicodeWidth, position.y + glyph.yoffset, 0.0f);
		vertices_[vertexCount + 2].texture  = Vector2f(static_cast<float>(glyph.position1.x) / glyphAtlasSize, static_cast<float>(glyph.position0.y) / glyphAtlasSize);

		vertices_[vertexCount + 3].position = Vector3f(position.x + glyph.xoffset + unicodeWidth, position.y + glyph.yoffset, 0.0f);
		vertices_[vertexCount + 3].texture  = Vector2f(static_cast<float>(glyph.position1.x) / glyphAtlasSize, static_cast<float>(glyph.position0.y) / glyphAtlasSize);


		vertices_[vertexCount + 4].position = Vector3f(position.x + glyph.xoffset, position.y + unicodeHeight + glyph.yoffset, 0.0f);
		vertices_[vertexCount + 4].texture  = Vector2f(static_cast<float>(glyph.position0.x) / glyphAtlasSize, static_cast<float>(glyph.position1.y) / glyphAtlasSize);

		vertices_[vertexCount + 5].position = Vector3f(position.x + glyph.xoffset + unicodeWidth, position.y + unicodeHeight + glyph.yoffset, 0.0f);
		vertices_[vertexCount + 5].texture  = Vector2f(static_cast<float>(glyph.position1.x) / glyphAtlasSize, static_cast<float>(glyph.position1.y) / glyphAtlasSize);

		position.x += glyph.xadvance;
		vertexCount += 6;
	}

	return vertexCount;
}