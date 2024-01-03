#include "TextureUtils.h"

#include <array>
#include <unordered_map>

#include "Assertion.h"
#include "FileManager.h"
#include "StringUtils.h"

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
	std::wstring filename = FileManager::Get().RemoveBasePath(path);

	for (const auto& blockSize : blockSizeMaps)
	{
		if (filename.find(blockSize.second) != std::wstring::npos)
		{
			return blockSize.first;
		}
	}

	return EAstcBlockSize::None;
}

void TextureUtils::LoadAstcFromFile(const std::wstring& path, std::vector<uint8_t>& outAstcBuffer, EAstcBlockSize& outBlockSize)
{
	outBlockSize = FindAstcBlockSizeFromFile(path);
	ASSERT(outBlockSize != EAstcBlockSize::None, L"%s can't find astc block size...", path.c_str());

	outAstcBuffer = FileManager::Get().ReadBufferFromFile(path);
}