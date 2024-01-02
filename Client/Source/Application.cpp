#include <array>
#include <cstdint>
#include <string>
#include <windows.h>

#include <glad/glad.h>

#include "Assertion.h"
#include "CommandLineUtils.h"
#include "FileManager.h"
#include "GameTimer.h"
#include "GeometryGenerator.h"
#include "InputManager.h"
#include "MathUtils.h"
#include "Mesh.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "StringUtils.h"
#include "Texture2D.h"
#include "TTFont.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Vertex.h"
#include "Window.h"
#include "WindowsCrashUtils.h"

bool bIsDone = false;
int32_t width = 800;
int32_t height = 600;
std::wstring shaderPath;
std::wstring resourcePath;

void RunApplication()
{
	Shader* shader = ResourceManager::Get().CreateResource<Shader>("Shader");
	shader->Initialize(shaderPath + L"LightEffect.vert", shaderPath + L"LightEffect.frag");
	
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	Mesh* sphere = ResourceManager::Get().CreateResource<Mesh>("Sphere");
	GeometryGenerator::CreateSphere(2.0f, 30, vertices, indices);
	//GeometryGenerator::CreateCylinder(2.0f, 2.0f, 30, vertices, indices);
	//GeometryGenerator::CreateXZQuad(10.0f, 10.0f, vertices, indices);
	sphere->Initialize(vertices, indices);

	Vector3f lightPosition;
	Mesh* light = ResourceManager::Get().CreateResource<Mesh>("Light");
	GeometryGenerator::CreateSphere(0.5f, 30, vertices, indices);
	light->Initialize(vertices, indices);

	Texture2D* texture = ResourceManager::Get().CreateResource<Texture2D>("texture");
	texture->Initialize(resourcePath + L"White.png");
	
	GameTimer timer;
	timer.Reset();
	while (!bIsDone)
	{
		timer.Tick();
		InputManager::Get().Tick();

		lightPosition = Vector3f(5.0f * MathUtils::Cos(timer.GetTotalSeconds()), 5.0f, 5.0f * MathUtils::Sin(timer.GetTotalSeconds()));

		Matrix4x4f view = MathUtils::CreateLookAt(Vector3f(10.0f, 10.0f, 10.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
		Matrix4x4f projection = MathUtils::CreatePerspective(MathUtils::ToRadian(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.01f, 1000.0f);

		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
		RenderManager::Get().RenderAxisGrid3D(view, projection, (-100.0f, -100.0f, -100.0f), Vector3f(+100.0f, +100.0f, +100.0f), 1.0f, Vector4f(1.0f, 1.0f, 1.0f, 0.5f));
		{
			shader->Bind();
			shader->SetMatrix4x4fParameter("world", Matrix4x4f::GetIdentity());
			shader->SetMatrix4x4fParameter("view", view);
			shader->SetMatrix4x4fParameter("projection", projection);
			shader->SetVector3fParameter("viewPosition", Vector3f(10.0f, 10.0f, 10.0f));
			shader->SetVector3fParameter("lightColor", Vector3f(1.0f, 0.5f, 0.31f));

			shader->SetVector3fParameter("material.ambient", Vector3f(0.0215, 0.1745, 0.0215));
			shader->SetVector3fParameter("material.diffuse", Vector3f(0.07568, 0.61424, 0.07568));
			shader->SetVector3fParameter("material.specular", Vector3f(0.633, 0.727811, 0.633));
			shader->SetFloatParameter("material.shininess", 128.0f * 0.6f);

			shader->SetVector3fParameter("light.position", lightPosition);
			shader->SetVector3fParameter("light.ambient", Vector3f(0.2f, 0.2f, 0.2f));
			shader->SetVector3fParameter("light.diffuse", Vector3f(0.5f, 0.5f, 0.5f));
			shader->SetVector3fParameter("light.specular", Vector3f(1.0f, 1.0f, 1.0f));

			glBindVertexArray(sphere->GetVertexArrayObject());
			glDrawElements(GL_TRIANGLES, sphere->GetIndexCount(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			shader->Unbind();

			RenderManager::Get().RenderMesh3D(MathUtils::CreateTranslation(lightPosition), view, projection, light, texture);
		}
		RenderManager::Get().EndFrame();
	}
}

int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
	WindowsCrashUtils::RegisterExceptionFilter();

	CommandLineUtils::Parse();
	CommandLineUtils::GetStringValue(L"shaderPath", shaderPath);
	CommandLineUtils::GetStringValue(L"resourcePath", resourcePath);

	Window::RegisterWindowClass(L"ProjectA", InputManager::WindowProc);

	Window window;
	window.Create(L"ProjectA", 200, 200, 800, 600, true, false);
	InputManager::Get().SetInputControlWindow(&window);
	RenderManager::Get().SetRenderTargetWindow(&window);

	FileManager::Get().Startup();
	InputManager::Get().Startup();
	ResourceManager::Get().Startup();
	RenderManager::Get().Startup();
	
	auto quitEvent = [&]() { bIsDone = true; };
	auto resizeEvent = [&]() {
		window.GetSize(width, height);
		RenderManager::Get().SetViewport(0, 0, width, height);
		RenderManager::Get().Resize();
	};
		
	InputManager::Get().AddWindowEventAction("CloseLoop",     EWindowEvent::Close,         quitEvent,   true);
	InputManager::Get().AddWindowEventAction("Resize",        EWindowEvent::Resize,        resizeEvent, true);
	InputManager::Get().AddWindowEventAction("ExitMinimize",  EWindowEvent::ExitMinimize,  resizeEvent, true);
	InputManager::Get().AddWindowEventAction("EnterMaximize", EWindowEvent::EnterMaximize, resizeEvent, true);
	InputManager::Get().AddWindowEventAction("ExitMaximize",  EWindowEvent::ExitMaximize,  resizeEvent, true);

	RunApplication();
	
	ResourceManager::Get().Shutdown();
	RenderManager::Get().Shutdown();
	InputManager::Get().Shutdown();
	FileManager::Get().Shutdown();
	window.Destroy();

	Window::UnregisterWindowClass();
	WindowsCrashUtils::UnregisterExceptionFilter();
	return 0;
}