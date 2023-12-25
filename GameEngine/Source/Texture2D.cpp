#include "Texture2D.h"

#include "Assertion.h"
#include "FileManager.h"
#include "GLAssertion.h"
#include "StringUtils.h"

#include <array>
#include <unordered_map>

#include <glad/glad.h>
#include <stb_image.h>

/**
 * @brief ASTC 파일의 헤더입니다.
 *
 * @note 
 * - astcenc.exe를 이용해서 생성한 파일 기준입니다.
 * - https://github.com/ARM-software/astc-encoder/blob/main/Docs/FileFormat.md
 */
struct ASTCFileHeader
{
	uint8_t magic[4];
	uint8_t blockdimX;
	uint8_t blockdimY;
	uint8_t blockdimZ;
	uint8_t xsize[3];
	uint8_t ysize[3];
	uint8_t zsize[3];
};

/**
 * @brief ASTC 블록 크기를 나타내는 열거형입니다.
 *
 * @note OpenGL의 GL_COMPRESSED_RGBA_ASTC_<SIZE>x<SIZE>_KHR 상수와 일대일 대응합니다.
 */
enum class EASTCBlockSize
{
	ASTC_4x4 = 0x93B0,
	ASTC_5x4 = 0x93B1,
	ASTC_5x5 = 0x93B2,
	ASTC_6x5 = 0x93B3,
	ASTC_6x6 = 0x93B4,
	ASTC_8x5 = 0x93B5,
	ASTC_8x6 = 0x93B6,
	ASTC_8x8 = 0x93B7,
	ASTC_10x5 = 0x93B8,
	ASTC_10x6 = 0x93B9,
	ASTC_10x8 = 0x93BA,
	ASTC_10x10 = 0x93BB,
	ASTC_12x10 = 0x93BC,
	ASTC_12x12 = 0x93BD,
	None = 0xFFFF,
};

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
		L"astc", // 압축 포멧
		L"dds",  // 압축 포멧
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

uint32_t Texture2D::FindAstcBlockSizeFromFile(const std::wstring& path)
{
	static const std::unordered_map<EASTCBlockSize, std::wstring> blockSizeMaps = {
		{ EASTCBlockSize::ASTC_4x4,   L"4x4"   },
		{ EASTCBlockSize::ASTC_5x4,   L"5x4"   },
		{ EASTCBlockSize::ASTC_5x5,   L"5x5"   },
		{ EASTCBlockSize::ASTC_6x5,   L"6x5"   },
		{ EASTCBlockSize::ASTC_6x6,   L"6x6"   },
		{ EASTCBlockSize::ASTC_8x5,   L"8x5"   },
		{ EASTCBlockSize::ASTC_8x6,   L"8x6"   },
		{ EASTCBlockSize::ASTC_8x8,   L"8x8"   },
		{ EASTCBlockSize::ASTC_10x5,  L"10x5"  },
		{ EASTCBlockSize::ASTC_10x6,  L"10x6"  },
		{ EASTCBlockSize::ASTC_10x8,  L"10x8"  },
		{ EASTCBlockSize::ASTC_10x10, L"10x10" },
		{ EASTCBlockSize::ASTC_12x10, L"12x10" },
		{ EASTCBlockSize::ASTC_12x12, L"12x12" },
	};

	std::wstring filename = FileManager::Get().RemoveBasePath(path);

	for (const auto& blockSize : blockSizeMaps)
	{
		if (filename.find(blockSize.second) != std::wstring::npos)
		{
			return static_cast<uint32_t>(blockSize.first);
		}
	}

	return static_cast<uint32_t>(EASTCBlockSize::None);
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

uint32_t Texture2D::CreateASTCCompressionTexture(const std::wstring& path)
{

	return uint32_t();
}
