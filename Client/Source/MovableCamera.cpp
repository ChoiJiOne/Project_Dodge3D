#include "MovableCamera.h"
#include "Player.h"

#include "Assertion.h"
#include "MathUtils.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "Window.h"

MovableCamera::~MovableCamera() {}

void MovableCamera::Initialize()
{
	relativePosition_ = Vector3f(0.0f, 7.0f, 7.0f);

	Window* window = RenderManager::Get().GetRenderTargetWindow();
	Camera3D::Initialize(
		relativePosition_, Vector3f(0.0f, -1.0f, -1.0f), Vector3f(0.0f, +1.0f, 0.0f),
		MathUtils::ToRadian(45.0f), window->GetAspectSize(), 0.1f, 100.0f
	);
}

void MovableCamera::Tick(float deltaSeconds)
{
	Player* player = ObjectManager::Get().GetObject<Player>("Player");
	Vector3f playerPosition = player->GetTransform().GetLocation();

	SetEyePosition(playerPosition + relativePosition_);
}

void MovableCamera::Release()
{
	Camera3D::Release();
}