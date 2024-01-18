#pragma once

#include <array>

#include "GameObject.h"
#include "IScene.h"
#include "LightShader.h"
#include "Skybox.h"
#include "ShadowMap.h"
#include "ShadowShader.h"

#include "Bullet.h"
#include "BulletSpawner.h"
#include "EastWall.h"
#include "Floor.h"
#include "MovableCamera.h"
#include "NorthWall.h"
#include "Player.h"
#include "SouthWall.h"
#include "StaticLight.h"
#include "WestWall.h"


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
	 * @brief 게임 씬의 리소스를 로딩합니다.
	 */
	void LoadResources();


	/**
	 * @brief 게임 씬의 오브젝트를 로딩합니다.
	 */
	void LoadObjects();
	

private:
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


	/**
	 * @brief 플레이어가 조종하는 오브젝트를 따라다니는 카메라입니다.
	 */
	MovableCamera* camera_ = nullptr;


	/**
	 * @brief 게임 내의 정적 라이트입니다.
	 */
	StaticLight* light_ = nullptr;


	/**
	 * @brief 플레이어가 조종 가능한 오브젝트입니다.
	 */
	Player* player_ = nullptr;


	/**
	 * @brief 바닥 오브젝트입니다.
	 */
	Floor* floor_ = nullptr;


	/**
	 * @brief 플레이어가 바라보는 방향 기준의 북쪽 벽입니다.
	 */
	NorthWall* northWall_ = nullptr;

	
	/**
	 * @brief 플레이어가 바라보는 방향 기준의 남쪽 벽입니다.
	 */
	SouthWall* southWall_ = nullptr;


	/**
	 * @brief 플레이어가 바라보는 방향 기준의 서쪽 벽입니다.
	 */
	WestWall* westWall_ = nullptr;


	/**
	 * @brief 플레이어가 바라보는 방향 기준의 동쪽 벽입니다.
	 */
	EastWall* eastWall_ = nullptr;


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트입니다.
	 */
	BulletSpawner* bulletSpawner0_ = nullptr;


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트입니다.
	 */
	BulletSpawner* bulletSpawner1_ = nullptr;


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트입니다.
	 */
	BulletSpawner* bulletSpawner2_ = nullptr;


	/**
	 * @brief 플레이어가 피해야 할 총알을 생성하는 오브젝트입니다.
	 */
	BulletSpawner* bulletSpawner3_ = nullptr;


	/**
	 * @brief 게임 내의 업데이트 가능한 오브젝트들입니다.
	 */
	std::array<GameObject*, 10> updateObjects_;


	/**
	 * @brief 게임 내의 렌더링 가능한 오브젝트들입니다.
	 */
	std::array<GameObject*, 10> renderObjects_;
};