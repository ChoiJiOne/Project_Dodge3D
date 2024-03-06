#include <glad/glad.h>
#include <stb_rect_pack.h>
#include <stb_truetype.h>

#include "Assertion.h"
#include "TTFont.h"
#include "FileUtils.h"

TTFont::~TTFont()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void TTFont::Initialize(const std::wstring& path, int32_t beginCodePoint, int32_t endCodePoint, float fontSize)
{
	ASSERT(!bIsInitialized_, "already initialize true type font resource...");

	beginCodePoint_ = beginCodePoint;
	endCodePoint_ = endCodePoint;

	std::vector<uint8_t> buffer = FileUtils::ReadBufferFromFile(path);

	stbtt_fontinfo info;
	const unsigned char* bufferPtr = reinterpret_cast<const unsigned char*>(&buffer[0]);
	ASSERT((stbtt_InitFont(&info, bufferPtr, stbtt_GetFontOffsetForIndex(bufferPtr, 0)) != 0), "failed to initialize stb_truetype...");

	std::shared_ptr<uint8_t[]> glyphAtlasBitmap = GenerateGlyphAtlasBitmap(buffer, beginCodePoint_, endCodePoint_, fontSize, glyphs_, glyphAtlasSize_);
	glyphAtlasID_ = CreateGlyphAtlasFromBitmap(glyphAtlasBitmap, glyphAtlasSize_);

	bIsInitialized_ = true;
}

void TTFont::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	GL_ASSERT(glDeleteTextures(1, &glyphAtlasID_), "failed to delete true type font glyph atlas...");

	bIsInitialized_ = false;
}

const Glyph& TTFont::GetGlyph(int32_t codePoint) const
{
	ASSERT(IsValidCodePoint(codePoint), "%d is invalid code point in true type font...", codePoint);
	int32_t index = codePoint - beginCodePoint_;
	return glyphs_[index];
}

bool TTFont::IsValidCodePoint(int32_t codePoint) const
{
	return (beginCodePoint_ <= codePoint) && (codePoint <= endCodePoint_);
}

void TTFont::MeasureText(const std::wstring& text, float& outWidth, float& outHeight) const
{
	int32_t textHeight = -1;
	int32_t textWidth = 0;

	for (const auto& unicode : text)
	{
		const Glyph& glyph = GetGlyph(static_cast<int32_t>(unicode));

		int32_t currentWidth = static_cast<int32_t>(glyph.xadvance);
		int32_t currentHeight = glyph.position1.y - glyph.position0.y;

		textWidth += currentWidth;

		if (currentHeight > textHeight)
		{
			textHeight = currentHeight;
		}
	}

	outWidth = static_cast<float>(textWidth);
	outHeight = static_cast<float>(textHeight);
}

std::shared_ptr<uint8_t[]> TTFont::GenerateGlyphAtlasBitmap(const std::vector<uint8_t>& buffer, int32_t beginCodePoint, int32_t endCodePoint, float fontSize, std::vector<Glyph>& outGlyphs, int32_t& outGlyphAtlasSize)
{
	std::vector<stbtt_packedchar> packedchars(endCodePoint - beginCodePoint + 1);
	outGlyphs.resize(endCodePoint - beginCodePoint + 1);

	int32_t success = 0;
	stbtt_pack_context packContext;
	std::shared_ptr<uint8_t[]> bitmap = nullptr;

	for (int32_t size = 16; size < 8192; size *= 2)
	{
		bitmap = std::make_unique<uint8_t[]>(size * size);
		success = stbtt_PackBegin(&packContext, bitmap.get(), size, size, 0, 1, nullptr);
		stbtt_PackSetOversampling(&packContext, 1, 1);

		success = stbtt_PackFontRange(
			&packContext,
			reinterpret_cast<const unsigned char*>(&buffer[0]),
			0,
			fontSize,
			beginCodePoint,
			static_cast<int>(packedchars.size()),
			&packedchars[0]
		);

		if (success)
		{
			stbtt_PackEnd(&packContext);
			outGlyphAtlasSize = size;
			break;
		}
		else
		{
			stbtt_PackEnd(&packContext);
			bitmap.reset();
		}
	}

	for (std::size_t index = 0; index < packedchars.size(); ++index)
	{
		outGlyphs[index].codePoint = static_cast<int32_t>(index + beginCodePoint);

		outGlyphs[index].position0 = Vector2i(packedchars[index].x0, packedchars[index].y0);
		outGlyphs[index].position1 = Vector2i(packedchars[index].x1, packedchars[index].y1);

		outGlyphs[index].xoffset = packedchars[index].xoff;
		outGlyphs[index].yoffset = packedchars[index].yoff;

		outGlyphs[index].xoffset2 = packedchars[index].xoff2;
		outGlyphs[index].yoffset2 = packedchars[index].yoff2;

		outGlyphs[index].xadvance = packedchars[index].xadvance;
	}

	return bitmap;
}

uint32_t TTFont::CreateGlyphAtlasFromBitmap(const std::shared_ptr<uint8_t[]>& bitmap, const int32_t& glyphAtlasSize)
{
	uint32_t textureAtlas;
	GL_ASSERT(glGenTextures(1, &textureAtlas), "failed to generate true type font glyph atlas...");
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, textureAtlas), "failed to bind glyph atlas object...");

	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE), "failed to set glyph atlas object warp s...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE), "failed to set glyph atlas object warp t...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR), "failed to set glyph atlas object min filter...");
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR), "failed to set glyph atlas object mag filter...");

	const void* bufferPtr = reinterpret_cast<const void*>(&bitmap[0]);
	GL_ASSERT(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, glyphAtlasSize, glyphAtlasSize, 0, GL_RED, GL_UNSIGNED_BYTE, bufferPtr),
		"failed to allows elements of an image array to be read by shaders...");
	GL_ASSERT(glGenerateMipmap(GL_TEXTURE_2D), "failed to generate glyph atlas mipmap...");

	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, 0), "failed to unbind glyph atlas object...");

	return textureAtlas;
}