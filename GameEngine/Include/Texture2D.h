#pragma once

#include <string>

#include "IResource.h"


/**
 * @brief 이미지 파일을 로딩하고 OpenGL 파이프라인에 바인딩 가능한 텍스처 리소스를 생성 및 관리합니다.
 * 
 * @note
 * - 이미지 파일은 .jpeg, .jpg, .png, .tga, .bmp 를 지원합니다.
 * - 압축 포멧은 ASTC와 DXT(S3TC) 형식을 지원합니다.
 * - ASTC 압축 포멧의 경우 반드시 astcenc.exe를 이용해서 생성한 파일이여야 합니다.
 * - DXT 압축 포멧의 경우 반드시 texconv.exe를 이용해서 생성한 파일이여야 합니다.
 */
class Texture2D : public IResource
{
public:
	/**
	 * @brief 텍스처의 디폴트 생성자입니다.
	 *
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	Texture2D() = default;


	/**
	 * @brief 텍스처의 가상 소멸자입니다.
	 *
	 * @note 텍스처 내부에서 할당된 요소를 해제하기 위해서는 반드시 Release를 호출해야 합니다.
	 */
	virtual ~Texture2D();


	/**
	 * @brief 텍스처의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Texture2D);


	/**
	 * @brief 이미지 파일을 읽고 텍스처 리소스를 생성합니다.
	 *
	 * @param path 이미지 파일의 경로입니다.
	 * 
	 * @note
	 * - 이미지 파일은 .jpeg, .jpg, .png, .tga, .bmp 를 지원합니다.
	 * - ASTC 압축 형식은 반드시 astcenc.exe를 이용해서 생성한 파일이여야 합니다.
	 * - ASTC 압축 형식의 확장자는 .astc로 되어 있어야 합니다.
	 * - DXT 압축 형식은 반드시 texconv.exe를 이용해서 생성한 파일이여야 합니다.
	 * - DXT 압축 형식의 확장자는 .dds로 되어 있어야 합니다.
	 */
	void Initialize(const std::wstring& path);


	/**
	 * @brief 텍스처의 내부 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 텍스처를 활성화합니다.
	 *
	 * @param unit 활성화 할 텍스처 유닛입니다.
	 */
	void Active(uint32_t unit) const;


private:
	/**
	 * @brief 비압축 텍스처 리소스를 생성합니다.
	 * 
	 * @param path 이미지 파일의 경로입니다.
	 * 
	 * @return 텍스처 리소스의 ID를 반환합니다.
	 */
	uint32_t CreateNonCompressionTexture(const std::wstring& path);


	/**
	 * @brief ASTC 압축 텍스처 리소스를 생성합니다.
	 * 
	 * @param path 이미지 파일의 경로입니다.
	 *
	 * @return 텍스처 리소스의 ID를 반환합니다.
	 */
	uint32_t CreateAstcCompressionTexture(const std::wstring& path);


	/**
	 * @brief DXT 압축 텍스처 리소스를 생성합니다.
	 * 
	 * @param path 이미지 파일의 경로입니다.
	 * 
	 * @return 텍스처 리소스의 ID를 반환합니다.
	 */
	uint32_t CreateDxtCompressionTexture(const std::wstring& path);


private:
	/**
	 * @brief 텍스처 리소스의 ID입니다.
	 */
	uint32_t textureID_ = 0;
};