#pragma once

#include "Macro.h"


/**
 * @brief 씬 인터페이스입니다.
 * 
 * @note 게임 내의 씬은 모두 이 인터페이스를 상속받아야 합니다.
 */
class IScene
{
public:
	/**
	 * @brief 씬의 디폴트 생성자입니다.
	 */
	IScene() = default;


	/**
	 * @brief 씬의 가상 소멸자입니다.
	 */
	virtual ~IScene() {}


	/**
	 * @brief 씬의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(IScene);


	/**
	 * @brief 씬의 한 프레임을 진행합니다.
	 *
	 * @param deltaSeconds 델타 시간값입니다.
	 */
	virtual void Tick(float deltaSeconds) = 0;


	/**
	 * @brief 씬에 진입합니다.
	 */
	virtual void EnterScene() = 0;


	/**
	 * @brief 씬에서 나갑니다.
	 */
	virtual void ExitScene() = 0;


	/**
	 * @brief 씬 전환이 감지되었는지 확인합니다.
	 *
	 * @return 씬 전환이 감지되었다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	virtual bool DetectSwitchScene() { return bDetectSwitchScene_; }


	/**
	 * @brief 현재 씬에 연결된 다음 씬을 얻습니다.
	 * 
	 * @return 현재 씬에 연결된 다음 씬의 포인터를 반환합니다.
	 */
	virtual IScene* GetNextScene() { return nextScene_; }


	/**
	 * @brief 현재 씬에 다음 씬을 설정합니다.
	 * 
	 * @param scene 현재 씬에 설정할 다음 씬입니다.
	 */
	virtual void SetNextScene(IScene* nextScene) { nextScene_ = nextScene; }


protected:
	/**
	 * @brief 씬에 진입했는지 확인합니다
	 */
	bool bIsEnterScene_ = false;


	/**
	 * @brief 씬 전환이 감지되었는지 확인합니다.
	 */
	bool bDetectSwitchScene_ = false;


	/**
	 * @brief 씬의 다음 씬입니다.
	 */
	IScene* nextScene_ = nullptr;
};