#pragma once

#include "IScene.h"
#include "UIButton.h"

#include "UIMainTitle.h"


/**
 * @brief 게임 시작 씬입니다.
 */
class StartScene : public IScene
{
public:
	/**
	 * @brief 게임 시작 씬의 생성자입니다.
	 */
	StartScene();


	/**
	 * @brief 게임 시작 씬의 가상 소멸자입니다.
	 */
	virtual ~StartScene();


	/**
	 * @brief 게임 시작 씬의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(StartScene);


	/**
	 * @brief 게임 시작 씬의 한 프레임을 진행합니다.
	 *
	 * @param deltaSeconds 델타 시간값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


private:
	/**
	 * @brief 메인 타이틀 UI 오브젝트입니다.
	 */
	UIMainTitle* mainTitle_ = nullptr;


	/**
	 * @brief UI 버튼입니다.
	 */
	UIButton* button_ = nullptr;
};