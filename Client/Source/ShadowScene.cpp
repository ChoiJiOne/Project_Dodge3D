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
	
	cameraPosition = Vector3f(1.0f, 5.0f, 10.0f);

	depthShader = ResourceManager::Get().GetResource<Shader>("ShadowMap");
	shadowShader = ResourceManager::Get().CreateResource<Shader>("shadow");
	shadowShader->Initialize(clientPath + L"Shader/Shadow.vert", clientPath + L"Shader/Shadow.frag");

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

	shadowMap = ResourceManager::Get().CreateResource<ShadowMap>("shadowMap");
	shadowMap->Initialize(SHADOW_WIDTH, SHADOW_HEIGHT);

	lightPosition = Vector3f(0.0f, 4.0f, +0.0f);

	window = RenderManager::Get().GetRenderTargetWindow();
}

ShadowScene::~ShadowScene()
{
}

void ShadowScene::Tick(float deltaSeconds)
{
	RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

	float nearPlane = 0.1f;
	float farPlane = 100.0f;
	Matrix4x4f view = MathUtils::CreateLookAt(cameraPosition, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
	Matrix4x4f projection = MathUtils::CreatePerspective(MathUtils::ToRadian(45.0f), window->GetAspectSize(), 0.1f, 100.0f);
	Matrix4x4f lightView = MathUtils::CreateLookAt(lightPosition, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, +1.0f));
	Matrix4x4f lightProjection = MathUtils::CreateOrtho(-10.0f, +10.0f, -10.0f, +10.0f, nearPlane, farPlane);

	{
		depthShader->Bind();
		depthShader->SetUniform("lightView", lightView);
		depthShader->SetUniform("lightProjection", lightProjection);

		RenderManager::Get().SetViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		shadowMap->Bind();
		shadowMap->Clear();

		// 1. 
		depthShader->SetUniform("world", MathUtils::CreateTranslation(Vector3f(0.0f, -3.0f, 0.0f)));
		RenderManager::Get().RenderStaticMesh3D(floor);

		// 2.
		depthShader->SetUniform("world", MathUtils::CreateTranslation(Vector3f(-1.0f, 1.0f, 0.0f)));
		RenderManager::Get().RenderStaticMesh3D(sphere);

		// 3.
		depthShader->SetUniform("world", MathUtils::CreateTranslation(Vector3f(0.0f, 1.0f, 0.0f)));
		RenderManager::Get().RenderStaticMesh3D(sphere);

		// 4.
		depthShader->SetUniform("world", MathUtils::CreateTranslation(Vector3f(+1.0f, 1.0f, 0.0f)));
		RenderManager::Get().RenderStaticMesh3D(sphere);

		shadowMap->Unbind();
		depthShader->Unbind();
	}
	{
		RenderManager::Get().SetWindowViewport();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shadowShader->Bind();
		shadowShader->SetUniform("view", view);
		shadowShader->SetUniform("projection", projection);
		shadowShader->SetUniform("lightView", lightView);
		shadowShader->SetUniform("lightProjection", lightProjection);
		shadowShader->SetUniform("lightPosition", lightPosition);
		shadowShader->SetUniform("viewPosition", cameraPosition);

		shadowMap->Active(0);

		// 1.
		shadowShader->SetUniform("world", MathUtils::CreateTranslation(Vector3f(0.0f, -3.0f, 0.0f)));
		RenderManager::Get().RenderStaticMesh3D(floor);

		// 2.
		shadowShader->SetUniform("world", MathUtils::CreateTranslation(Vector3f(-1.0f, 1.0f, 0.0f)));
		RenderManager::Get().RenderStaticMesh3D(sphere);

		// 3.
		shadowShader->SetUniform("world", MathUtils::CreateTranslation(Vector3f(0.0f, 1.0f, 0.0f)));
		RenderManager::Get().RenderStaticMesh3D(sphere);

		// 4.
		shadowShader->SetUniform("world", MathUtils::CreateTranslation(Vector3f(+1.0f, 1.0f, 0.0f)));
		RenderManager::Get().RenderStaticMesh3D(sphere);

		shadowShader->Unbind();
	}

	RenderManager::Get().EndFrame();
}
