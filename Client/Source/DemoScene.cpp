#include "DemoScene.h"

#include "Camera3D.h"
#include "Assertion.h"
#include "CommandLineUtils.h"
#include "GeometryGenerator.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "MathUtils.h"
#include "ObjectManager.h"
#include "RenderManager.h"

#include <glad/glad.h>

DemoScene::DemoScene()
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
	
	shadowShader = ResourceManager::Get().GetResource<ShadowShader>("ShadowShader");
	lightShader = ResourceManager::Get().GetResource<LightShader>("LightShader");

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

	shadowMap = ResourceManager::Get().CreateResource<ShadowMap>("shadowMap");
	shadowMap->Initialize(SHADOW_WIDTH, SHADOW_HEIGHT);

	light = ObjectManager::Get().CreateObject<Light>("light");
	light->Initialize(
		Vector3f(-10.0f, +10.0f, 0.0f),
		Vector3f(1.0f, -1.0f, 0.0f),
		Vector3f(0.5f, 0.5f, 0.5f),
		Vector3f(0.5f, 0.5f, 0.5f),
		Vector3f(1.0f, 1.0f, 1.0f),
		Vector3f(0.0f, 0.0f, +1.0f),
		MathUtils::CreateOrtho(-10.0f, +10.0f, -10.0f, +10.0f, 0.1f, 100.0f)
	);
}

DemoScene::~DemoScene()
{
}

void DemoScene::Tick(float deltaSeconds)
{
	RenderManager::Get().SetDepthMode(true);
	{
		RenderManager::Get().SetViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		shadowMap->Bind();
		shadowMap->Clear();
		
		shadowShader->Bind();
		shadowShader->SetLight(light);
		shadowShader->DrawMesh3D(MathUtils::CreateTranslation(Vector3f(0.0f, 0.0f, 0.0f)), floor);
	
		for (float x = -2.0f; x <= 2.0f; x += 1.0f)
		{
			for (float z = -2.0f; z <= 2.0f; z += 1.0f)
			{
				shadowShader->DrawMesh3D(MathUtils::CreateTranslation(Vector3f(x, 1.0f, z)), sphere);
			}
		}

		shadowShader->Unbind();
		shadowMap->Unbind();
	}
	{
		RenderManager::Get().SetWindowViewport();
		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

		lightShader->Bind();
		lightShader->SetLight(light);
		lightShader->SetMaterial(material);
		lightShader->SetCamera(camera);
		lightShader->DrawMesh3D(MathUtils::CreateTranslation(Vector3f(0.0f, 0.0f, 0.0f)), floor, shadowMap);

		for (float x = -2.0f; x <= 2.0f; x += 1.0f)
		{
			for (float z = -2.0f; z <= 2.0f; z += 1.0f)
			{
				lightShader->DrawMesh3D(MathUtils::CreateTranslation(Vector3f(x, 1.0f, z)), sphere, shadowMap);
			}
		}

		lightShader->Unbind();
	}

	RenderManager::Get().EndFrame();
}
