#include "MovableCamera.h"

#include "Assertion.h"
#include "MathUtils.h"
#include "RenderManager.h"
#include "Window.h"

MovableCamera::~MovableCamera() {}

void MovableCamera::Initialize()
{
	Window* window = RenderManager::Get().GetRenderTargetWindow();
	Camera3D::Initialize(
		Vector3f(0.0f, 4.0f, 4.0f), Vector3f(0.0f, -1.0f, -1.0f), Vector3f(0.0f, +1.0f, 0.0f),
		MathUtils::ToRadian(45.0f), window->GetAspectSize(), 0.1f, 100.0f
	);
}

void MovableCamera::Tick(float deltaSeconds)
{
}

void MovableCamera::Release()
{
	Camera3D::Release();
}