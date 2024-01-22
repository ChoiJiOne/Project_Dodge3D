#pragma once

#include "PlayLogger.h"

#include "IScene.h"
#include "Sound.h"
#include "TTFont.h"
#include "UIMouseButton.h"
#include "UIPanel.h"


/**
 * @brief 플레이어의 기록을 보여주는 씬입니다.
 */
class RankScene : public IScene
{
public:
	/**
	 * @brief 플레이어의 기록을 보여주는 씬의 생성자입니다.
	 */
	RankScene();


	/**
	 * @brief 플레이어의 기록을 보여주는 씬의 가상 소멸자입니다.
	 */
	virtual ~RankScene();


	/**
	 * @brief 플레이어의 기록을 보여주는 씬의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(RankScene);


	/**
	 * @brief 플레이어의 기록을 보여주는 씬의 한 프레임을 진행합니다.
	 *
	 * @param deltaSeconds 델타 시간값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 플레이어의 기록을 보여주는 씬에 진입합니다.
	 */
	virtual void EnterScene() override;


	/**
	 * @brief 플레이어의 기록을 보여주는 씬에서 나갑니다.
	 */
	virtual void ExitScene() override;


	/**
	 * @brief 게임의 루프 종료 이벤트를 설정합니다.
	 *
	 * @param loopQuitEvent 설정할 게임 루프 종료 이벤트입니다.
	 */
	void SetLoopQuitEvent(const std::function<void()>& loopQuitEvent) { loopQuitEvent_ = loopQuitEvent; }


private:
	/**
	 * @brief 플레이어의 기록을 보여주는 씬의 리소스를 로딩합니다.
	 */
	void LoadResources();


	/**
	 * @brief 플레이어의 기록을 보여주는 씬의 오브젝트를 로딩합니다.
	 */
	void LoadObjects();


private:
	/**
	 * @brief 루프 종료 이벤트입니다.
	 */
	std::function<void()> loopQuitEvent_ = nullptr;


	/**
	 * @brief 크기가 32인 폰트 리소스입니다.
	 */
	TTFont* font32_ = nullptr;


	/**
	 * @brief 게임 리셋 버튼입니다.
	 */
	UIMouseButton* resetButton_ = nullptr;


	/**
	 * @brief 게임 종료 버튼입니다.
	 */
	UIMouseButton* quitButton_ = nullptr;


	/**
	 * @brief 플레이어의 기록을 관리하는 오브젝트입니다.
	 */
	PlayLogger* playLogger_ = nullptr;


	/**
	 * @brief 버튼 클릭 사운드입니다.
	 */
	Sound* buttonClick_ = nullptr;
};