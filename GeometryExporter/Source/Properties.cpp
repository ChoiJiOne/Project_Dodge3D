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

	lightDirection_ = Vector3f(-1.0f, -1.0f, -1.0f);
	lightAmbientRGB_ = Vector3f(+0.5f, +0.5f, +0.5f);
	lightDiffuseRGB_ = Vector3f(+0.7f, +0.7f, +0.7f);
	lightSpecularRGB_ = Vector3f(+1.0f, +1.0f, +1.0f);

	directionalLight_ = DirectionalLight(lightDirection_, lightAmbientRGB_, lightDiffuseRGB_, lightSpecularRGB_);
	
	bIsInitialized_ = true;
}

void Properties::Tick(float deltaSeconds)
{
	ImGui::Begin("Light Properties");

	if (ImGui::CollapsingHeader("Light"))
	{
		ImGui::SliderFloat3("direction", lightDirection_.GetPtr(), -1.0f, 1.0f);
		ImGui::ColorEdit3("ambient", lightAmbientRGB_.GetPtr());
		ImGui::ColorEdit3("diffuse", lightDiffuseRGB_.GetPtr());
		ImGui::ColorEdit3("specular", lightSpecularRGB_.GetPtr());

		directionalLight_.SetDirection(lightDirection_);
		directionalLight_.SetAmbientRGB(lightAmbientRGB_);
		directionalLight_.SetDiffuseRGB(lightDiffuseRGB_);
		directionalLight_.SetSpecularRGB(lightSpecularRGB_);
	}

	if (ImGui::CollapsingHeader("Material"))
	{

	}

	ImGui::End();
}

void Properties::Release()
{
	ASSERT(bIsInitialized_, "not initialized before or has already been released...");

	bIsInitialized_ = false;
}