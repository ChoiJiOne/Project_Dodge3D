#pragma once

#include "Camera3D.h"
#include "IScene.h"
#include "Shader.h"
#include "LightShader.h"
#include "StaticMesh.h"
#include "Material.h"
#include "ShadowMap.h"
#include "ShadowShader.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Window.h"
#include "Light.h"

class ShadowScene : public IScene
{
public:
	ShadowScene();
	virtual ~ShadowScene();
	DISALLOW_COPY_AND_ASSIGN(ShadowScene);
	virtual void Tick(float deltaSeconds) override;
	
private:
	Camera3D* camera;

	ShadowShader* shadowShader;
	LightShader* lightShader;

	StaticMesh* floor;
	StaticMesh* cube;
	StaticMesh* sphere;
	Material* material;

	ShadowMap* shadowMap;

	Light* light;
	
	const uint32_t SHADOW_WIDTH = 1024;
	const uint32_t SHADOW_HEIGHT = 1024;

	Window* window = nullptr;
};