#include "ShadowScene.h"

#include "Camera3D.h"
#include "Assertion.h"
#include "CommandLineUtils.h"
#include "GeometryGenerator.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "MathUtils.h"
#include "ObjectManager.h"

#include <glad/glad.h>

ShadowScene::ShadowScene()
{
	std::wstring rootPath;
	CommandLineUtils::GetStringValue(L"rootPath", rootPath);

	std::wstring clientPath = rootPath + L"Client/";

	window = RenderManager::Get().GetRenderTargetWindow();

	camera = ObjectManager::Get().CreateObject<Camera3D>("camera");
	camera->Initialize(
		Vector3f(0.0f, 20.0f, 20.0f),
		Vector3f(0.0f, -1.0f, -1.0f),
		Vector3f(0.0f, 1.0f, 0.0f),
		MathUtils::ToRadian(45.0f),
		window->GetAspectSize(), 
		0.1f, 
		100.0f
	);
	
	depthShader = ResourceManager::Get().GetResource<Shader>("ShadowMap");
	light = ResourceManager::Get().GetResource<Shader>("Light");

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;;

	floor = ResourceManager::Get().CreateResource<StaticMesh>("floor");
	GeometryGenerator::CreateCube(Vector3f(50.0f, 1.0f, 50.0f), vertices, indices);
	floor->Initialize(vertices, indices);

	cube = ResourceManager::Get().CreateResource<StaticMesh>("cube");
	GeometryGenerator::CreateCube(Vector3f(2.0f, 2.0f, 2.0f), vertices, indices);
	cube->Initialize(vertices, indices);

	sphere = ResourceManager::Get().CreateResource<StaticMesh>("sphere");
	GeometryGenerator::CreateSphere(0.5f, 30, vertices, indices);
	sphere->Initialize(vertices, indices);

	material = ResourceManager::Get().CreateResource<Material>("material");
	material->Initialize(
		Vector3f(0.329412f, 0.223529f, 0.027451f),
		Vector3f(0.780392f, 0.568627f, 0.113725f),
		Vector3f(0.992157f, 0.941176f, 0.807843f),
		128.0f * 0.21794872f
	);

	shadowMap0 = ResourceManager::Get().CreateResource<ShadowMap>("shadowMap0");
	shadowMap0->Initialize(SHADOW_WIDTH, SHADOW_HEIGHT);

	lightObject = ObjectManager::Get().CreateObject<Light>("LightObject");
	lightObject->Initialize(
		Vector3f(-10.0f, +10.0f, 0.0f),
		Vector3f(1.0f, -1.0f, 0.0f),
		Vector3f(0.5f, 0.5f, 0.5f),
		Vector3f(0.7f, 0.7f, 0.7f),
		Vector3f(1.0f, 1.0f, 1.0f),
		Vector3f(0.0f, 0.0f, +1.0f),
		MathUtils::CreateOrtho(-10.0f, +10.0f, -10.0f, +10.0f, 0.1f, 100.0f)
	);
}

ShadowScene::~ShadowScene()
{
}

void ShadowScene::Tick(float deltaSeconds)
{
	{
		depthShader->Bind();
		depthShader->SetUniform("lightView", lightObject->GetViewMatrix());
		depthShader->SetUniform("lightProjection", lightObject->GetProjectionMatrix());

		RenderManager::Get().SetViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		shadowMap0->Bind();
		shadowMap0->Clear();

		depthShader->SetUniform("world", MathUtils::CreateTranslation(Vector3f(0.0f, 0.0f, 0.0f)));
		RenderManager::Get().RenderStaticMesh3D(floor);

		for (float x = -10.0; x <= 10.0f; x += 1.0f)
		{
			for (float z = -10.0f; z <= 10.0f; z += 1.0f)
			{
				depthShader->SetUniform("world", MathUtils::CreateTranslation(Vector3f(x, 1.0f, z)));
				RenderManager::Get().RenderStaticMesh3D(sphere);
			}
		}

		shadowMap0->Unbind();
		depthShader->Unbind();
	}
	{
		RenderManager::Get().SetWindowViewport();
		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

		light->Bind();
		light->SetUniform("view", camera->GetViewMatrix());
		light->SetUniform("projection", camera->GetProjectionMatrix());
		light->SetUniform("lightView", lightObject->GetViewMatrix());
		light->SetUniform("lightProjection", lightObject->GetProjectionMatrix());
		light->SetUniform("viewPosition", camera->GetEyePosition());

		light->SetUniform("material.ambientRGB", material->GetAmbientRGB());
		light->SetUniform("material.diffuseRGB", material->GetDiffuseRGB());
		light->SetUniform("material.specularRGB", material->GetSpecularRGB());
		light->SetUniform("material.shininess", material->GetShininess());
		light->SetUniform("light.position", lightObject->GetPosition());
		light->SetUniform("light.direction", lightObject->GetDirection());
		light->SetUniform("light.ambientRGB", Vector3f(0.5f, 0.5f, 0.5f));
		light->SetUniform("light.diffuseRGB", Vector3f(0.5f, 0.5f, 0.5f));
		light->SetUniform("light.specularRGB", Vector3f(1.0f, 1.0f, 1.0f));
		
		shadowMap0->Active(0);

		light->SetUniform("world", MathUtils::CreateTranslation(Vector3f(0.0f, 0.0f, 0.0f)));
		RenderManager::Get().RenderStaticMesh3D(floor);

		for (float x = -10.0; x <= 10.0f; x += 1.0f)
		{
			for (float z = -10.0f; z <= 10.0f; z += 1.0f)
			{
				light->SetUniform("world", MathUtils::CreateTranslation(Vector3f(x, 1.0f, z)));
				RenderManager::Get().RenderStaticMesh3D(sphere);
			}
		}

		light->Unbind();
	}

	RenderManager::Get().EndFrame();
}
