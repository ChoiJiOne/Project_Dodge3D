#pragma once

#include <windows.h>
#include <glad/glad.h>

#include <cstdint>
#include <string>
#include <vector>


#define FOURCC_DXT1 0x31545844
#define FOURCC_DXT3 0x33545844
#define FOURCC_DXT5 0x35545844


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
 * @brief DDS 파일의 헤더입니다.
 *
 * @see https://learn.microsoft.com/en-us/windows/win32/direct3ddds/dds-header
 */
struct DDSFileHeader
{
	uint8_t  magic[4];
	uint32_t dwSize;
	uint32_t dwFlags;
	uint32_t dwHeight;
	uint32_t dwWidth;
	uint32_t dwPitchOrLinearSize;
	uint32_t dwDepth;
	uint32_t dwMipMapCount;
	uint32_t dwReserved1[11];
	uint32_t dwPixelSize;
	uint32_t dwPixelFlags;
	uint32_t dwFourCC;
	uint32_t dwRGBBitCount;
	uint32_t dwRBitMask;
	uint32_t dwGBitMask;
	uint32_t dwBBitMask;
	uint32_t dwABitMask;
	uint32_t dwCaps;
	uint32_t dwCaps2;
	uint32_t dwCaps3;
	uint32_t dwCaps4;
	uint32_t dwReserved2;
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
	 * @brief 이미지 파일의 확장자가 지원 가능한 파일인지 검사합니다.
	 *
	 * @param 지원 가능한 파일인지 검사할 텍스처 파일 경로입니다.
	 *
	 * @return 텍스처 파일이 지원 가능하다면 true, 그렇지 않으면 false를 반환합니다.
	 * 
	 * @note
	 * - 이미지 파일은 .jpeg, .jpg, .png, .tga, .bmp 를 지원합니다.
	 * - 압축 포멧은 ASTC와 DXT(S3TC) 형식을 지원합니다.
	 * - ASTC 압축 포멧의 경우 반드시 astcenc.exe를 이용해서 생성한 파일이여야 합니다.
	 * - DXT 압축 포멧의 경우 반드시 texconv.exe를 이용해서 생성한 파일이여야 합니다.
	 */
	static bool IsSupportExtension(const std::wstring& path);


	/**
	 * @brief 이미지 채널에 대응하는 OpenGL 텍스처 포멧의 enum 값을 찾습니다.
	 * 
	 * @param channel 이미지의 채널값입니다.
	 * 
	 * @return 텍스처 포멧의 정수 열겨형 값을 반환합니다.
	 * 
	 * @note
	 * - channels 값이 1이면 GL_RED를 반환합니다.
	 * - channels 값이 3이면 GL_RGB를 반환합니다.
	 * - channels 값이 4이면 GL_RGBA를 반환합니다.
	 * - channels 값이 2는 지원하지 않습니다.
	 */
	static GLenum FindTextureFormatFromChannel(uint32_t channel);


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
	 * @brief 이미지 파일을 로딩합니다.
	 * 
	 * @param path 이미지 파일의 경로입니다.
	 * @param outWidth 이미지의 가로 크기입니다.
	 * @param outHeight 이미지의 세로 크기입니다.
	 * @param outChannels 이미지의 픽셀 체널입니다.
	 * @param outBuffer 이미지의 버퍼입니다.
	 * 
	 * @note 이미지 파일은 .jpeg, .jpg, .png, .tga, .bmp 를 지원합니다.
	 */
	static void LoadImageFromFile(const std::wstring& path, int32_t& outWidth, int32_t& outHeight, int32_t& outChannels, std::vector<uint8_t>& outBuffer);


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


	/**
	 * @brief DXT 압축 텍스처 파일을 로딩합니다.
	 * 
	 * @param path DXT 압축 텍스처 파일의 경로입니다.
	 * @param outFormat DXT 압축 텍스처의 포멧입니다.
	 * @param outBlockSize DXT 압축 텍스처의 블록 크기입니다.
	 * 
	 * @note
	 * - 파일 이름 내부에 반드시 DXT 압축 형식이 포함되어 있어야 합니다.
	 * - ex. example_dxt1.dds, example_dxt3.dds
	 * - 반드시 texconv.exe 파일로 생성한 파일이여야 합니다.
	 */
	static void LoadDxtFromFile(const std::wstring& path, std::vector<uint8_t>& outDxtBuffer, uint32_t& outFormat, uint32_t& outBlockSize);
};