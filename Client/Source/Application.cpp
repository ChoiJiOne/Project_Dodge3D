#include <cstdint>
#include <string>
#include <windows.h>

#include <glad/glad.h>

#include "Assertion.h"
#include "CommandLineUtils.h"
#include "FileManager.h"
#include "GeometryGenerator.h"
#include "InputManager.h"
#include "MathUtils.h"
#include "Mesh.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Shader.h"
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
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	Mesh* mesh = ResourceManager::Get().CreateResource<Mesh>("Mesh");
	//GeometryGenerator::CreateXZQuad(2.0f, 2.0f, vertices, indices);
	GeometryGenerator::CreateCylinder(2.0f, 2.0f, 30, 30, vertices, indices);
	mesh->Initialize(vertices, indices);
	
	Texture2D* texture = ResourceManager::Get().CreateResource<Texture2D>("texture");
	texture->Initialize(resourcePath + L"container6x6.astc");

	Vector3f currentCameraPosition = Vector3f(0.0f, 0.0f, 10.0f);
	while (!bIsDone)
	{
		InputManager::Get().Tick();
		if (InputManager::Get().GetVirtualKeyPressState(EVirtualKey::VKEY_LEFT) == EPressState::Held)
		{
			currentCameraPosition.x -= 0.1f;
		}

		if (InputManager::Get().GetVirtualKeyPressState(EVirtualKey::VKEY_RIGHT) == EPressState::Held)
		{
			currentCameraPosition.x += 0.1f;
		}

		Matrix4x4f view = MathUtils::CreateLookAt(currentCameraPosition, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
		Matrix4x4f projection = MathUtils::CreatePerspective(MathUtils::ToRadian(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.01f, 1000.0f);

		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
		RenderManager::Get().RenderAxisGrid3D(view, projection, (-100.0f, -100.0f, -100.0f), Vector3f(+100.0f, +100.0f, +100.0f), 1.0f, Vector4f(1.0f, 1.0f, 1.0f, 0.5f));
		RenderManager::Get().RenderMesh3D(Matrix4x4f::GetIdentity(), view, projection, mesh, texture);

		for (std::size_t index = 0; index < 1; ++index)
		{
			const Vector3f& position = vertices[index].position;
			const Vector3f& normal = vertices[index].normal * 0.5f;
			const Vector3f& tangent = vertices[index].tangent * 0.5f;
			const Vector3f& bitangent = vertices[index].bitangent * 0.5f;

			RenderManager::Get().RenderLine3D(view, projection, position, position + tangent, Vector4f(1.0f, 0.0f, 0.0f, 1.0f));
			RenderManager::Get().RenderLine3D(view, projection, position, position + bitangent, Vector4f(0.0f, 1.0f, 0.0f, 1.0f));
			RenderManager::Get().RenderLine3D(view, projection, position, position + normal, Vector4f(0.0f, 0.0f, 1.0f, 1.0f));
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