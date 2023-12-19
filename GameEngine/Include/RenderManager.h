#pragma once

#include <cstdint>
#include <memory>

#include "IManager.h"


/**
 * @brief 렌더링 처리를 수행하는 매니저입니다.
 * 
 * @note 이 클래스는 싱글턴입니다.
 */
class RenderManager : public IManager
{
public:
	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(RenderManager);


	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 참조 인스턴스를 얻습니다.
	 * 
	 * @return 렌더링 처리를 수행하는 매니저의 참조자를 반환합니다.
	 */
	static RenderManager& Get();


	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 포인터를 얻습니다.
	 * 
	 * @return 렌더링 처리를 수행하는 매니저의 포인터를 반환합니다.
	 */
	static RenderManager* GetPtr();


	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 사용을 시작합니다.
	 */
	virtual void Startup() override;


	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 사용을 종료합니다.
	 */
	virtual void Shutdown() override;


private:
	/**
	 * @brief 렌더링 처리를 수행하는 매니저에 디폴트 생성자와 빈 가상 소멸자를 삽입합니다.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(RenderManager);


private:
	/**
	 * @brief 렌더링 처리를 수행하는 클래스의 유일한 인스턴스입니다.
	 */
	static std::unique_ptr<RenderManager> renderManager_;
};