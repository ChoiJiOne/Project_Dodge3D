#include "Texture2D.h"

#include "Assertion.h"
#include "FileManager.h"
#include "GLAssertion.h"
#include "StringUtils.h"

#include <array>
#include <unordered_map>

#include <glad/glad.h>
#include <stb_image.h>

Texture2D::~Texture2D()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Texture2D::Initialize(const std::wstring& path)
{
	ASSERT(!bIsInitialized_, "already initialize 2d texture resource...");

	bIsInitialized_ = true;
}

void Texture2D::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	bIsInitialized_ = false;
}

void Texture2D::Active(uint32_t unit) const
{
}

bool Texture2D::IsSupportExtension(const std::wstring& path)
{
	static const std::array<std::wstring, 7> supportExtensions = {
		L"jpeg",
		L"jpg",
		L"png",
		L"tga",
		L"bmp",
		L"astc", // ¾ÐÃà Æ÷¸ä
		L"dds",  // ¾ÐÃà Æ÷¸ä
	};

	std::wstring extension = StringUtils::ToLower(FileManager::Get().GetFileExtension(path));
	for (const auto& supportExtension : supportExtensions)
	{
		if (extension == supportExtension)
		{
			return true;
		}
	}

	return false;
}

uint32_t Texture2D::CreateNonCompressionTexture(const std::wstring& path)
{
	std::string convertPath = StringUtils::Convert(path);

	int32_t width;
	int32_t height;
	int32_t channels;

	uint8_t* buffer = stbi_load(convertPath.c_str(), &width, &height, &channels, 0);
	ASSERT(buffer != nullptr, "failed to load %s image resource...", convertPath.c_str());

	GLenum format = 0;
	switch (channels)
	{
	case 1:
		format = static_cast<GLenum>(GL_RED);
		break;

	case 3:
		format = static_cast<GLenum>(GL_RGB);
		break;

	case 4:
		format = static_cast<GLenum>(GL_RGBA);
		break;

	default:
		ASSERT(false, "%d is not support image channel", channels);
	}

	uint32_t textureID;
	GL_ASSERT(glGenTextures(1, &textureID), "failed to generate texture object...");
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, textureID), "failed to bind texture object...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), "failed to set texture object warp s...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), "failed to set texture object warp t...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR), "failed to set texture object min filter...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR), "failed to set texture object mag filter...");
	GL_ASSERT(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, buffer), "failed to allows elements of an image array to be read by shaders...");
	GL_ASSERT(glGenerateMipmap(GL_TEXTURE_2D), "failed to generate texture mipmap...");
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, 0), "failed to unbind texture object...");

	stbi_image_free(buffer);
	buffer = nullptr;

	return textureID;
}