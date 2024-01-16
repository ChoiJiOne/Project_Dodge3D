#pragma once

#include "GameObject.h"
#include "IScene.h"
#include "LightShader.h"
#include "ShadowMap.h"
#include "ShadowShader.h"

#include "MovableCamera.h"
#include "StaticLight.h"


/**
 * @brief 게임 플레이 씬입니다.
 */
class GameScene : public IScene
{
public:
	/**
	 * @brief 게임 플레이 씬의 생성자입니다.
	 */
	GameScene();


	/**
	 * @brief 게임 플레이 씬의 가상 소멸자입니다.
	 */
	virtual ~GameScene();


	/**
	 * @brief 게임 플레이 씬의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(GameScene);


	/**
	 * @brief 게임 플레이 씬의 한 프레임을 진행합니다.
	 * 
	 * @param deltaSeconds 델타 시간값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


private:
	/**
	 * @brief 플레이어가 조종하는 오브젝트를 따라다니는 카메라입니다.
	 */
	MovableCamera* camera_ = nullptr;


	/**
	 * @brief 게임 내의 정적 라이트입니다.
	 */
	StaticLight* light_ = nullptr;


	/**
	 * @brief 게임 내의 업데이트 가능한 오브젝트들입니다.
	 */
	std::vector<GameObject*> updateObjects_;


	/**
	 * @brief 게임 내의 렌더링 가능한 오브젝트들입니다.
	 */
	std::vector<GameObject*> renderObjects_;


	/**
	 * @brief 게임 내 렌더링 씬의 깊이 값을 기록한 텍스처입니다.
	 */
	ShadowMap* shadowMap_ = nullptr;


	/**
	 * @brief 셰도우 맵의 가로 크기입니다.
	 */
	const uint32_t SHADOW_WIDTH = 1024;


	/**
	 * @brief 셰도우 맵의 세로 크기입니다.
	 */
	const uint32_t SHADOW_HEIGHT = 1024;


	/**
	 * @brief 게임 내 렌더링 씬의 깊이 값을 렌더링하는 셰이더입니다.
	 */
	ShadowShader* shadowShader_ = nullptr;

	/**
	 * @brief 게임 내 렌더링 씬에 라이팅 효과를 적용하는 셰이더입니다.
	 */
	LightShader* lightShader_ = nullptr;
};