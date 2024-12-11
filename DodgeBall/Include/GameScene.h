#pragma once

#include <array>
#include <list>
#include <functional>

#include "Framebuffer.h"
#include "GameObject.h"
#include "IScene.h"
#include "PostEffectShader.h"
#include "LightShader.h"
#include "UIMouseButton.h"
#include "UIKeyButton.h"
#include "Sound.h"
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
#include "PlayLogger.h"
#include "SouthWall.h"
#include "StaticLight.h"
#include "UIBoard.h"
#include "WestWall.h"


/**
 * @brief 게임 플레이 씬입니다.
 */
class GameScene : public IScene
{
public:
	/**
	 * @brief 게임 플레이 씬의 상태입니다.
	 */
	enum class ESceneState : int32_t
	{
		Ready = 0x00, // 게임 플레이 준비 상태입니다.
		Play  = 0x01, // 게임 플레이 상태입니다.
		Pause = 0x02, // 게임 중단 상태입니다.
		Done  = 0x03, // 게임 종료 상태입니다.
	};


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


	/**
	 * @brief 게임 플레이 씬에 진입합니다.
	 */
	virtual void EnterScene() override;


	/**
	 * @brief 게임 플레이 씬에서 나갑니다.
	 */
	virtual void ExitScene() override;


	/**
	 * @brief 게임 리셋 시 다음 씬을 설정합니다.
	 * 
	 * @param scene 게임 리셋 시 설정할 다음 씬입니다.
	 */
	void SetNextResetScene(IScene* nextScene) { nextResetScene_ = nextScene; }


	/**
	 * @brief 랭크 버튼 클릭 시 전환될 다음 씬을 설정합니다.
	 * 
	 * @param scene 랭크 버튼 클릭 시 설정할 다음 씬입니다.
	 */
	void SetNextRankScene(IScene* nextScene) { nextRankScene_ = nextScene; }


	/**
	 * @brief 게임의 루프 종료 이벤트를 설정합니다.
	 *
	 * @param loopQuitEvent 설정할 게임 루프 종료 이벤트입니다.
	 */
	void SetLoopQuitEvent(const std::function<void()>& loopQuitEvent) { loopQuitEvent_ = loopQuitEvent; }


private:
	/**
	 * @brief 게임 씬의 리소스를 로딩합니다.
	 */
	void LoadResources();


	/**
	 * @brief 게임 씬의 오브젝트를 로딩합니다.
	 */
	void LoadObjects();


	/**
	 * @brief 씬 내의 오브젝트들을 업데이트합니다.
	 * 
	 * @param deltaSeconds 델타 시간값입니다.
	 */
	void UpdateScene(float deltaSeconds);


	/**
	 * @brief 대기 상태일 때의 씬을 업데이트합니다.
	 * 
	 * @param deltaSeconds 델타 시간값입니다.
	 */
	void UpdateReadyStateScene(float deltaSeconds);


	/**
	 * @brief 플레이 상태일 때의 씬을 업데이트합니다.
	 * 
	 * @param deltaSeconds 델타 시간값입니다.
	 */
	void UpdatePlayStateScene(float deltaSeconds);


	/**
	 * @brief 중지 상태일 때의 씬을 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간값입니다.
	 */
	void UpdatePauseStateScene(float deltaSeconds);


	/**
	 * @brief 종료 상태일 때의 씬을 업데이트합니다.
	 * 
	 * @param deltaSeconds 델타 시간값입니다.
	 */
	void UpdateDoneStateScene(float deltaSeconds);


	/**
	 * @brief 깊이 씬을 렌더링합니다.
	 */
	void RenderDepthScene();


	/**
	 * @brief 씬을 렌더링합니다.
	 */
	void RenderScene();
	

private:
	/**
	 * @brief 루프 종료 이벤트입니다.
	 */
	std::function<void()> loopQuitEvent_ = nullptr;


	/**
	 * @brief 게임 플레이 씬의 상태입니다.
	 */
	ESceneState sceneState_ = ESceneState::Ready;


	/**
	 * @brief 플레이어와 총알이 충돌되었는지 확인합니다.
	 */
	bool bIsCollisionToPlayer_ = false;


	/**
	 * @brief 크기가 32인 폰트 리소스입니다.
	 */
	TTFont* font32_ = nullptr;


	/**
	 * @brief 버튼 클릭 사운드입니다.
	 */
	Sound* buttonClick_ = nullptr;


	/**
	 * @brief 게임 내 렌더링 씬의 깊이 값을 기록한 텍스처입니다.
	 */
	ShadowMap* shadowMap_ = nullptr;


	/**
	 * @brief 후처리 효과를 적용하기 위한 프레임 버퍼입니다.
	 */
	Framebuffer* framebuffer_ = nullptr;


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
	 * @brief 후처리 효과를 적용하기 위한 그레이 스케일 셰이더입니다.
	 */
	PostEffectShader* grayscaleEffectShader_ = nullptr;

	
	/**
	 * @brief 후처리 효과를 적용하기 위한 페이드 효과 셰이더입니다.
	 */
	PostEffectShader* fadeEffectShader_ = nullptr;


	/**
	 * @brief 후처리 효과를 적용하기 위한 가우시안 블러 셰이더입니다.
	 */
	PostEffectShader* blurEffectShader_ = nullptr;


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
	 * @brief 플레이어의 플레이 기록을 관리하는 오브젝트입니다.
	 */
	PlayLogger* playLogger_ = nullptr;


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
	 * @brief 게임 내의 렌더링 가능한 오브젝트들입니다.
	 */
	std::array<GameObject*, 10> renderObjects_;


	/**
	 * @brief 게임 내의 총알 오브젝트입니다.
	 */
	std::list<Bullet*> bullets_;


	/**
	 * @brief 게임 내의 생성된 총알 오브젝트 수입니다.
	 */
	uint32_t countOfbullet_ = 0;


	/**
	 * @brief 총알 삭제 이벤트입니다.
	 */
	std::function<bool(Bullet*)> bulletRemoveEvent_;


	/**
	 * @brief 플레이어의 플레이 정보를 표시하는 UI입니다.
	 */
	UIBoard* board_ = nullptr;


	/**
	 * @brief 페이드 인 계산을 위한 시간값입니다.
	 */
	float stepTime_ = 0.0f;


	/**
	 * @brief 페이드 인 시간입니다.
	 */
	float fadeInStepTime_ = 1.0f;


	/**
	 * @brief 리셋을 수행할 경우의 다음 씬입니다.
	 */
	IScene* nextResetScene_ = nullptr;


	/**
	 * @brief 랭킹 버튼을 클릭할 경우의 다음 씬입니다.
	 */
	IScene* nextRankScene_ = nullptr;


	/**
	 * @brief 중지된 게임을 계속 플레이하는 버튼입니다.
	 */
	UIMouseButton* continueButton_ = nullptr;


	/**
	 * @brief 플레이어의 랭킹을 확인하기 위한 버튼입니다.
	 */
	UIMouseButton* rankButton_ = nullptr;


	/**
	 * @brief 게임 리셋 버튼입니다.
	 */
	UIMouseButton* resetButton_ = nullptr;


	/**
	 * @brief 게임 종료 버튼입니다.
	 */
	UIMouseButton* quitButton_ = nullptr;


	/**
	 * @brief 게임의 중단을 감지하는 버튼입니다.
	 */
	UIKeyButton* pauseButton_ = nullptr;
};