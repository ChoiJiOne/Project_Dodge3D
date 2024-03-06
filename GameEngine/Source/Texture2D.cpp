#include <array>
#include <unordered_map>

#include <glad/glad.h>

#include "Assertion.h"
#include "Texture2D.h"
#include "FileUtils.h"
#include "StringUtils.h"
#include "TextureUtils.h"

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
	ASSERT(TextureUtils::IsSupportExtension(path), L"%s is not support extension...", path.c_str());

	std::wstring extension = StringUtils::ToLower(FileUtils::GetFileExtension(path));
	if (extension == L"astc")
	{
		textureID_ = CreateAstcCompressionTexture(path);
	}
	else if (extension == L"dds")
	{
		textureID_ = CreateDxtCompressionTexture(path);
	}
	else
	{
		textureID_ = CreateNonCompressionTexture(path);
	}

	bIsInitialized_ = true;
}

void Texture2D::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	GL_ASSERT(glDeleteTextures(1, &textureID_), "failed to delete texture object...");

	bIsInitialized_ = false;
}

void Texture2D::Active(uint32_t unit) const
{
	GL_ASSERT(glActiveTexture(GL_TEXTURE0 + unit), "failed to active %d texture unit...", (GL_TEXTURE0 + unit));
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, textureID_), "failed to bind texture...");
}

uint32_t Texture2D::CreateNonCompressionTexture(const std::wstring& path)
{
	int32_t width;
	int32_t height;
	int32_t channels;
	std::vector<uint8_t> buffer;
	TextureUtils::LoadImageFromFile(path, width, height, channels, buffer);

	GLenum format = TextureUtils::FindTextureFormatFromChannel(channels);
	ASSERT(format != 0xFFFF, "%d is not support image channel...", channels);

	uint32_t textureID;
	GL_ASSERT(glGenTextures(1, &textureID), "failed to generate texture object...");
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, textureID), "failed to bind texture object...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), "failed to set texture object warp s...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), "failed to set texture object warp t...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR), "failed to set texture object min filter...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR), "failed to set texture object mag filter...");
	GL_ASSERT(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, buffer.data()), "failed to allows elements of an image array to be read by shaders...");
	GL_ASSERT(glGenerateMipmap(GL_TEXTURE_2D), "failed to generate texture mipmap...");
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, 0), "failed to unbind texture object...");
	
	return textureID;
}

uint32_t Texture2D::CreateAstcCompressionTexture(const std::wstring& path)
{
	std::vector<uint8_t> astcData;
	EAstcBlockSize blockSize = EAstcBlockSize::None;
	TextureUtils::LoadAstcFromFile(path, astcData, blockSize);

	AstcFileHeader* astcDataPtr = reinterpret_cast<AstcFileHeader*>(astcData.data());

	int32_t xsize = astcDataPtr->xsize[0] + (astcDataPtr->xsize[1] << 8) + (astcDataPtr->xsize[2] << 16);
	int32_t ysize = astcDataPtr->ysize[0] + (astcDataPtr->ysize[1] << 8) + (astcDataPtr->ysize[2] << 16);
	int32_t zsize = astcDataPtr->zsize[0] + (astcDataPtr->zsize[1] << 8) + (astcDataPtr->zsize[2] << 16);
	int32_t xblocks = (xsize + astcDataPtr->blockdimX - 1) / astcDataPtr->blockdimX;
	int32_t yblocks = (ysize + astcDataPtr->blockdimY - 1) / astcDataPtr->blockdimY;
	int32_t zblocks = (zsize + astcDataPtr->blockdimZ - 1) / astcDataPtr->blockdimZ;
	GLenum compressionFormat = static_cast<GLenum>(blockSize);

	uint32_t byteToRead = (xblocks * yblocks * zblocks) << 4;

	uint32_t textureID;
	GL_ASSERT(glGenTextures(1, &textureID), "failed to generate texture object...");
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, textureID), "failed to bind texture object...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), "failed to set texture object warp s...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), "failed to set texture object warp t...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR), "failed to set texture object min filter...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR), "failed to set texture object mag filter...");
	GL_ASSERT(glCompressedTexImage2D(GL_TEXTURE_2D, 0, compressionFormat, xsize, ysize, 0, byteToRead, reinterpret_cast<const void*>(&astcDataPtr[1])), "failed to compress texture...");
	GL_ASSERT(glGenerateMipmap(GL_TEXTURE_2D), "failed to generate texture mipmap...");
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, 0), "failed to unbind texture object...");

	return textureID;
}

uint32_t Texture2D::CreateDxtCompressionTexture(const std::wstring& path)
{
	std::vector<uint8_t> dxtData;
	GLenum format;
	uint32_t blockSize;
	TextureUtils::LoadDxtFromFile(path, dxtData, format, blockSize);

	DDSFileHeader* dxtDataPtr = reinterpret_cast<DDSFileHeader*>(dxtData.data());
	uint32_t width = dxtDataPtr->dwWidth;
	uint32_t height = dxtDataPtr->dwHeight;
	uint32_t linearSize = dxtDataPtr->dwPitchOrLinearSize;
	uint32_t mipMapCount = dxtDataPtr->dwMipMapCount;
	uint32_t bufferSize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	uint8_t* bufferPtr = reinterpret_cast<uint8_t*>(&dxtDataPtr[1]);

	uint32_t textureID;
	GL_ASSERT(glGenTextures(1, &textureID), "failed to generate texture object...");
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, textureID), "failed to bind texture object...");
	GL_ASSERT(glPixelStorei(GL_UNPACK_ALIGNMENT, 1), "failed to set pixel storage modes...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), "failed to set texture object warp s...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), "failed to set texture object warp t...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR), "failed to set texture object min filter...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR), "failed to set texture object mag filter...");

	for (uint32_t level = 0, offset = 0; level < mipMapCount; ++level)
	{
		if (width == 0 || height == 0)
		{
			mipMapCount--;
			continue;
		}

		uint32_t size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
		GL_ASSERT(glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, bufferPtr + offset), "failed to compression texture...");

		offset += size;
		width /= 2;
		height /= 2;
	}

	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, 0), "failed to unbind texture object...");

	return textureID;
}