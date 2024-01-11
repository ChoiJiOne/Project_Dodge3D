#include "Properties.h"

#include "Assertion.h"

#include <imgui.h>

Properties::~Properties()
{
	if (bIsInitialized_)
	{
		Release();
	}
}

void Properties::Initialize()
{
	ASSERT(!bIsInitialized_, "already initialize light properties object...");

	direction_ = Vector3f(-1.0f, -1.0f, -1.0f);
	ambientRGB_ = Vector3f(+0.5f, +0.5f, +0.5f);
	diffuseRGB_ = Vector3f(+0.7f, +0.7f, +0.7f);
	specularRGB_ = Vector3f(+1.0f, +1.0f, +1.0f);

	directionalLight_ = DirectionalLight(direction_, ambientRGB_, diffuseRGB_, specularRGB_);
	
	bIsInitialized_ = true;
}

void Properties::Tick(float deltaSeconds)
{
	ImGui::Begin("Light Properties");

	ImGui::SliderFloat3("direction", direction_.GetPtr(), -1.0f, 1.0f);
	ImGui::ColorEdit3("ambient", ambientRGB_.GetPtr());
	ImGui::ColorEdit3("diffuse", diffuseRGB_.GetPtr());
	ImGui::ColorEdit3("specular", specularRGB_.GetPtr());

	directionalLight_.SetDirection(direction_);
	directionalLight_.SetAmbientRGB(ambientRGB_);
	directionalLight_.SetDiffuseRGB(diffuseRGB_);
	directionalLight_.SetSpecularRGB(specularRGB_);

	ImGui::End();
}

void Properties::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	bIsInitialized_ = false;
}