#pragma once

#include <cstdint>
#include <string>
#include <vector>



/**
 * @brief ASTC 파일의 헤더입니다.
 *
 * @note
 * - astcenc.exe를 이용해서 생성한 파일 기준입니다.
 * - https://github.com/ARM-software/astc-encoder/blob/main/Docs/FileFormat.md
 */
struct AstcFileHeader
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
 * @note 
 * - OpenGL의 GL_COMPRESSED_RGBA_ASTC_<SIZE>x<SIZE>_KHR 상수와 일대일 대응합니다.
 *  - https://www.khronos.org/opengl/wiki/ASTC_Texture_Compression
 */
enum class EAstcBlockSize
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


/**
 * @brief 텍스처에 대한 확장 기능을 제공합니다.
 */
class TextureUtils
{
public:
	/**
	 * @brief 파일 이름으로부터 ASTC의 압축 블록 크기를 얻습니다.
	 * 
	 * @param path ASTC의 압축 블록 크기를 얻을 압축 텍스처 파일 경로입니다.
	 * 
	 * @note 
	 * - 파일 이름 내부에 반드시 압축 블럭 크기가 있어야 합니다.
	 * - ex. example_4x4.astc, example_6x6.astc
	 * - 반드시 astcenc.exe 파일로 생성한 파일이여야 합니다.
	 */
	static EAstcBlockSize FindAstcBlockSizeFromFile(const std::wstring& path);


	/**
	 * @brief ASTC 압축 텍스처 파일을 로딩합니다.
	 * 
	 * @param path ASTC 압축 텍스처 파일의 경로입니다.
	 * @param outAstcBuffer ASTC 압축 텍스처 파일의 버퍼입니다.
	 * @param outBlockSize ASTC 압축 텍스처의 압축 블록 크기입니다.
	 * 
	 * @note 
	 * - 파일 이름 내부에 반드시 압축 블럭 크기가 있어야 합니다.
	 * - ex. example_4x4.astc, example_6x6.astc
	 * - 반드시 astcenc.exe 파일로 생성한 파일이여야 합니다.
	 */
	static void LoadAstcFromFile(const std::wstring& path, std::vector<uint8_t>& outAstcBuffer, EAstcBlockSize& outBlockSize);
};