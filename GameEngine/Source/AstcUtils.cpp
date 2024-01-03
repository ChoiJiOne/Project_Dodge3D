#include "AstcUtils.h"

#include <unordered_map>

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

EAstcBlockSize AstcUtils::FindAstcBlockSizeFromFile(const std::wstring& path)
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