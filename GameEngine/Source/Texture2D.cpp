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