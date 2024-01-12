#pragma once

#include <memory>
#include <string>

#include "IResource.h"

#include <miniaudio.h>


/**
 * @brief 플레이 가능한 사운드 리소스입니다.
 */
class Sound : public IResource
{
public:
	/**
	 * @brief 사운드의 디폴트 생성자입니다.
	 * 
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	Sound() = default;


	/**
	 * @brief 사운드의 가상 소멸자입니다.
	 * 
	 * @note 사운드 내부에서 할당된 요소를 해제하기 위해서는 반드시 Release를 호출해야 합니다.
	 */
	virtual ~Sound();


	/**
	 * @brief 사운드의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Sound);


	/**
	 * @brief 사운드 파일을 로딩하고 초기화합니다.
	 * 
	 * @param path 사운드 파일의 경로입니다.
	 */
	void Initialize(const std::wstring& path);


	/**
	 * @brief 사운드의 내부 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


private:
	/**
	 * @brief miniaudio 사운드 리소스입니다.
	 */
	std::unique_ptr<ma_sound> sound_ = nullptr;
};