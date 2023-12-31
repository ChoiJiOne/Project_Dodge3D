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

void CreateSphere(float radius, uint32_t sliceCount, uint32_t stackCount, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices)
{
	outVertices.resize(0);
	outIndices.resize(0);

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	Vertex topVertex(Vector3f(0.0f, +radius, 0.0f), Vector3f(0.0f, +1.0f, 0.0f), Vector2f(0.0f, 0.0f), Vector3f(), Vector3f());
	Vertex bottomVertex(Vector3f(0.0f, -radius, 0.0f), Vector3f(0.0f, -1.0f, 0.0f), Vector2f(0.0f, 1.0f), Vector3f(), Vector3f());

	float phiStep = Pi / static_cast<float>(stackCount);
	float thetaStep = TwoPi / static_cast<float>(sliceCount);

	vertices.push_back(topVertex);
	for (uint32_t i = 1; i <= stackCount - 1; ++i)
	{
		float phi = static_cast<float>(i) * phiStep;

		for (uint32_t j = 0; j <= sliceCount; ++j)
		{
			float theta = static_cast<float>(j) * thetaStep;

			Vector3f position;
			position.x = radius * MathUtils::Sin(phi) * MathUtils::Cos(theta);
			position.y = radius * MathUtils::Cos(phi);
			position.z = radius * MathUtils::Sin(phi) * MathUtils::Sin(theta);

			Vector3 normal = MathUtils::Normalize(position);
			Vector2f texture = Vector2f(theta / TwoPi, phi / Pi);

			vertices.push_back(Vertex(position, normal, texture, Vector3f(), Vector3f()));
		}
	}
	vertices.push_back(bottomVertex);

	for (uint32_t i = 1; i <= sliceCount; ++i)
	{
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i + 0);
	}

	UINT baseIndex = 1;
	UINT ringVertexCount = sliceCount + 1;
	for (UINT i = 0; i < stackCount - 2; ++i)
	{
		for (UINT j = 0; j < sliceCount; ++j)
		{
			indices.push_back(baseIndex + i * ringVertexCount + j);
			indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
			indices.push_back(baseIndex + i * ringVertexCount + j + 1);

			indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
			indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
			indices.push_back(baseIndex + i * ringVertexCount + j + 1);
		}
	}


	UINT southPoleIndex = (UINT)vertices.size() - 1;
	baseIndex = southPoleIndex - ringVertexCount;

	for (UINT i = 0; i < sliceCount; ++i)
	{
		indices.push_back(southPoleIndex);
		indices.push_back(baseIndex + i + 1);
		indices.push_back(baseIndex + i);
	}

	outVertices = vertices;
	outIndices = indices;
}

void RunApplication()
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	Mesh* cube = ResourceManager::Get().CreateResource<Mesh>("Cube");
	GeometryGenerator::CreateCube(2.0f, 2.0f, 2.0f, vertices, indices);
	cube->Initialize(vertices, indices);

	Mesh* sphere = ResourceManager::Get().CreateResource<Mesh>("Sphere");
	CreateSphere(3.0f, 30, 30, vertices, indices);
	sphere->Initialize(vertices, indices);
	
	Texture2D* texture0 = ResourceManager::Get().CreateResource<Texture2D>("cubeTexture");
	texture0->Initialize(resourcePath + L"container6x6.astc");

	Texture2D* texture1 = ResourceManager::Get().CreateResource<Texture2D>("sphereTexture");
	texture1->Initialize(resourcePath + L"2k_earth_daymap.jpg");

	Vector3f currentCameraPosition = Vector3f(0.0f, 5.0f, 10.0f);
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
		RenderManager::Get().RenderMesh3D(MathUtils::CreateTranslation(-4.0f, 0.0f, 0.0f), view, projection, cube, texture0);
		RenderManager::Get().RenderMesh3D(MathUtils::CreateTranslation(+4.0f, 0.0f, 0.0f), view, projection, sphere, texture1);
		
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