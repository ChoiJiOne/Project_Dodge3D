#include "TextureUtils.h"

#include "Assertion.h"
#include "FileUtils.h"
#include "StringUtils.h"

#include <array>
#include <unordered_map>

#include <stb_image.h>

std::unordered_map<EAstcBlockSize, std::wstring> blockSizeMaps = {
	{ EAstcBlockSize::ASTC_4x4,   L"4x4"   },
	{ EAstcBlockSize::ASTC_5x4,   L"5x4"   },
	{ EAstcBlockSize::ASTC_5x5,   L"5x5"   },
	{ EAstcBlockSize::ASTC_6x5,   L"6x5"   },
	{ EAstcBlockSize::ASTC_6x6,   L"6x6"   },
	{ EAstcBlockSize::ASTC_8x5,   L"8x5"   },
	{ EAstcBlockSize::ASTC_8x6,   L"8x6"   },
	{ EAstcBlockSize::ASTC_8x8,   L"8x8"   },
	{ EAstcBlockSize::ASTC_10x5,  L"10x5"  },
	{ EAstcBlockSize::ASTC_10x6,  L"10x6"  },
	{ EAstcBlockSize::ASTC_10x8,  L"10x8"  },
	{ EAstcBlockSize::ASTC_10x10, L"10x10" },
	{ EAstcBlockSize::ASTC_12x10, L"12x10" },
	{ EAstcBlockSize::ASTC_12x12, L"12x12" },
};

std::array<std::wstring, 7> supportExtensions = {
	L"jpeg",
	L"jpg",
	L"png",
	L"tga",
	L"bmp",
	L"astc", // ¾ÐÃà Æ÷¸ä
	L"dds",  // ¾ÐÃà Æ÷¸ä
};

bool TextureUtils::IsSupportExtension(const std::wstring& path)
{
	std::wstring extension = StringUtils::ToLower(FileUtils::GetFileExtension(path));
	for (const auto& supportExtension : supportExtensions)
	{
		if (extension == supportExtension)
		{
			return true;
		}
	}

	return false;
}

GLenum TextureUtils::FindTextureFormatFromChannel(uint32_t channel)
{
	GLenum format = 0;

	switch (channel)
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
		format = static_cast<GLenum>(0xFFFF);
	}

	return format;
}

EAstcBlockSize TextureUtils::FindAstcBlockSizeFromFile(const std::wstring& path)
{
	std::wstring filename = FileUtils::RemoveBasePath(path);

	for (const auto& blockSize : blockSizeMaps)
	{
		if (filename.find(blockSize.second) != std::wstring::npos)
		{
			return blockSize.first;
		}
	}

	return EAstcBlockSize::None;
}

void TextureUtils::LoadImageFromFile(const std::wstring& path, int32_t& outWidth, int32_t& outHeight, int32_t& outChannels, std::vector<uint8_t>& outBuffer)
{
	std::string convertPath = StringUtils::Convert(path);

	uint8_t* bufferPtr = stbi_load(convertPath.c_str(), &outWidth, &outHeight, &outChannels, 0);
	ASSERT(bufferPtr != nullptr, "failed to load %s image file...", convertPath.c_str());

	std::size_t bufferSize = static_cast<std::size_t>(outWidth * outHeight * outChannels);
	outBuffer.resize(bufferSize);

	std::copy(bufferPtr, bufferPtr + bufferSize, &outBuffer[0]);

	stbi_image_free(bufferPtr);
	bufferPtr = nullptr;
}

void TextureUtils::LoadAstcFromFile(const std::wstring& path, std::vector<uint8_t>& outAstcBuffer, EAstcBlockSize& outBlockSize)
{
	outBlockSize = FindAstcBlockSizeFromFile(path);
	ASSERT(outBlockSize != EAstcBlockSize::None, L"%s can't find astc block size...", path.c_str());

	outAstcBuffer = FileUtils::ReadBufferFromFile(path);
}

void TextureUtils::LoadDxtFromFile(const std::wstring& path, std::vector<uint8_t>& outDxtBuffer, uint32_t& outFormat, uint32_t& outBlockSize)
{
	outDxtBuffer = FileUtils::ReadBufferFromFile(path);
	DDSFileHeader* dxtDataPtr = reinterpret_cast<DDSFileHeader*>(outDxtBuffer.data());

	std::string ddsFileCode;
	for (std::size_t index = 0; index < 4; ++index)
	{
		ddsFileCode += dxtDataPtr->magic[index];
	}
	ASSERT(ddsFileCode == "DDS ", L"invalid  %s dds file code...", path.c_str());

	switch (dxtDataPtr->dwFourCC)
	{
	case FOURCC_DXT1:
		outFormat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		outBlockSize = 8;
		return;

	case FOURCC_DXT3:
		outFormat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		outBlockSize = 16;
		return;

	case FOURCC_DXT5:
		outFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		outBlockSize = 16;
		return;
	}
	ASSERT(false, " %d is not support DXT format or invalid DDS file format...", dxtDataPtr->dwFourCC);
}
