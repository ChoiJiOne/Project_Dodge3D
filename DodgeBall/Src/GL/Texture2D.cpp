#pragma warning(push)
#pragma warning(disable: 26451)

#include <map>
#include <vector>

#include <glad/glad.h>
#include <stb_image.h>

#include "GL/GLAssert.h"
#include "GL/Texture2D.h"
#include "Utils/Assertion.h"
#include "Utils/Utils.h"

#define PIXEL_FORMAT_R    1
#define PIXEL_FORMAT_RG   2
#define PIXEL_FORMAT_RGB  3
#define PIXEL_FORMAT_RGBA 4

Texture2D::Texture2D(const std::string& path, const EFilter& filter)
	: textureID_(CreateTextureFromImage(path, filter))
{
	bIsInitialized_ = true;
}

Texture2D::~Texture2D()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Texture2D::Release()
{
	CHECK(bIsInitialized_);

	GL_API_CHECK(glDeleteTextures(1, &textureID_));

	bIsInitialized_ = false;
}

void Texture2D::Active(uint32_t unit) const
{
	GL_API_CHECK(glActiveTexture(GL_TEXTURE0 + unit));
	GL_API_CHECK(glBindTexture(GL_TEXTURE_2D, textureID_));
}

uint32_t Texture2D::CreateTextureFromImage(const std::string& path, const EFilter& filter)
{
	uint8_t* imagePtr = stbi_load(path.c_str(), &width_, &height_, &channels_, 0);
	ASSERT(imagePtr != nullptr, "Failed to load %s file.", path.c_str());

	std::size_t bufferSize = static_cast<std::size_t>(width_ * height_ * channels_);
	std::vector<uint8_t> buffer(bufferSize);
	std::copy(imagePtr, imagePtr + bufferSize, buffer.data());

	stbi_image_free(imagePtr);
	imagePtr = nullptr;

	static std::map<uint32_t, uint32_t> formats =
	{
		{ PIXEL_FORMAT_R,    GL_RED  },
		{ PIXEL_FORMAT_RG,   GL_RG   },
		{ PIXEL_FORMAT_RGB,  GL_RGB  },
		{ PIXEL_FORMAT_RGBA, GL_RGBA },
	};

	GLenum format = formats.at(channels_);
	const void* bufferPtr = reinterpret_cast<const void*>(buffer.data());
	uint32_t textureID = 0;

	float borderColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	GL_API_CHECK(glGenTextures(1, &textureID));
	GL_API_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
	GL_API_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
	GL_API_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
	GL_API_CHECK(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));
	GL_API_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(filter)));
	GL_API_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(filter)));
	GL_API_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, format, width_, height_, 0, format, GL_UNSIGNED_BYTE, bufferPtr));
	GL_API_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
	GL_API_CHECK(glBindTexture(GL_TEXTURE_2D, 0));

	return textureID;
}

#pragma warning(pop)