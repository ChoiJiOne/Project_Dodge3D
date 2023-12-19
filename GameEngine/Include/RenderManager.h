#pragma once

#include <cstdint>

#include "IManager.h"


class Window;


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
	static RenderManager& Get()
	{
		static RenderManager instance;
		return instance;
	}


	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 사용을 시작합니다.
	 * 
	 * @note 
	 * - 이 메서드 호출 전에 렌더링 대상이 되는 윈도우 포인터를 설정해야 합니다.
	 * - 이 메서드는 한 번만 호출되어야 합니다.
	 */
	virtual void Startup() override;


	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 사용을 종료합니다.
	 * 
	 * @note
	 * - 애플리케이션 종료 전에 이 메서드를 반드시 호출하여 내부 리소스를 정리해야 합니다.
	 * - 이 메서드는 반드시 한 번만 호출되어야 합니다.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief 렌더링 대상이 되는 윈도우를 설정합니다.
	 * 
	 * @param window 렌더링 대상이 되는 윈도우입니다.
	 */
	void SetRenderTargetWindow(Window* window) { renderTargetWindow_ = window; }


	/**
	 * @brief 렌더링 대상이 되는 윈도우를 얻습니다.
	 * 
	 * @return 렌더링 대상이 되는 윈도우의 포인터를 반환합니다.
	 */
	Window* GetRenderTargetWindow() const { return renderTargetWindow_; }


private:
	/**
	 * @brief 렌더링 처리를 수행하는 매니저에 디폴트 생성자와 빈 가상 소멸자를 삽입합니다.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(RenderManager);


private:
	/**
	 * @brief 렌더링 대상이 되는 윈도우 포인터입니다.
	 */
	Window* renderTargetWindow_ = nullptr;
};