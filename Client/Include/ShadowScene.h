#pragma once

#include "Camera3D.h"
#include "IScene.h"
#include "Shader.h"
#include "StaticMesh.h"
#include "Material.h"
#include "ShadowMap.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Window.h"
#include "Light.h"


/**
 * @brief 기능 구현을 위한 게임 씬입니다.
 */
class ShadowScene : public IScene
{
public:
	/**
	 * @brief 씬 생성자입니다.
	 */
	ShadowScene();


	/**
	 * @brief 씬의 가상 소멸자입니다.
	 */
	virtual ~ShadowScene();


	/**
	 * @brief 게임 씬의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(ShadowScene);


	/**
	 * @brief 씬의 한 프레임을 진행합니다.
	 * 
	 * @param deltaSeconds 델타 시간값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


private:
	Camera3D* camera;

	Shader* depthShader;
	Shader* light;

	StaticMesh* floor;
	StaticMesh* cube;
	StaticMesh* sphere;
	Material* material;

	// 1.
	ShadowMap* shadowMap0;

	Light* lightObject;
	
	const uint32_t SHADOW_WIDTH = 1024;
	const uint32_t SHADOW_HEIGHT = 1024;

	Window* window = nullptr;
};