#include "ShadowScene.h"

#include "Assertion.h"
#include "CommandLineUtils.h"
#include "GeometryGenerator.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "MathUtils.h"

#include <glad/glad.h>

ShadowScene::ShadowScene()
{
	std::wstring rootPath;
	CommandLineUtils::GetStringValue(L"rootPath", rootPath);

	std::wstring clientPath = rootPath + L"Client/";
	
	cameraPosition = Vector3f(0.0f, 20.0f, 20.0f);

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

	shadowMap0 = ResourceManager::Get().CreateResource<ShadowMap>("shadowMap0");
	shadowMap0->Initialize(SHADOW_WIDTH, SHADOW_HEIGHT);

	lightPosition0 = Vector3f(-10.0f, +10.0f, 0.0f);
	lightDirection0 = Vector3f(1.0f, -1.0f, 0.0f);
	lightView0 = MathUtils::CreateLookAt(lightPosition0, lightPosition0 + lightDirection0, Vector3f(0.0f, 0.0f, +1.0f));
	lightProjection0 = MathUtils::CreateOrtho(-10.0f, +10.0f, -10.0f, +10.0f, 0.1f, 100.0f);

	window = RenderManager::Get().GetRenderTargetWindow();
}

ShadowScene::~ShadowScene()
{
}

void ShadowScene::Tick(float deltaSeconds)
{
	Matrix4x4f view = MathUtils::CreateLookAt(cameraPosition, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
	Matrix4x4f projection = MathUtils::CreatePerspective(MathUtils::ToRadian(45.0f), window->GetAspectSize(), 0.1f, 100.0f);

	{
		depthShader->Bind();
		depthShader->SetUniform("lightView", lightView0);
		depthShader->SetUniform("lightProjection", lightProjection0);

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
		light->SetUniform("view", view);
		light->SetUniform("projection", projection);
		light->SetUniform("lightView", lightView0);
		light->SetUniform("lightProjection", lightProjection0);
		light->SetUniform("viewPosition", cameraPosition);

		light->SetUniform("material.ambientRGB", Vector3f(0.329412f, 0.223529f, 0.027451f));
		light->SetUniform("material.diffuseRGB", Vector3f(0.780392f, 0.568627f, 0.113725f));
		light->SetUniform("material.specularRGB", Vector3f(0.992157f, 0.941176f, 0.807843f));
		light->SetUniform("material.shininess", 128.0f * 0.21794872f);
		light->SetUniform("light.position", lightPosition0);
		light->SetUniform("light.direction", lightDirection0);
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
