#include <array>
#include <cstdint>
#include <string>
#include <windows.h>

#include <glad/glad.h>
#include <tiny_obj_loader.h>

#include "Assertion.h"
#include "CommandLineUtils.h"
#include "FileManager.h"
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
	std::string basePath = StringUtils::Convert(resourcePath);
	std::string objPath = StringUtils::Convert(resourcePath) + "Map.obj";

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	tinyobj::LoadObj(&attrib, &shapes, &materials, nullptr, objPath.c_str(), basePath.c_str());
		
	for (const auto& shape : shapes)
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		const tinyobj::mesh_t& mesh = shape.mesh;
		
		for (std::size_t index = 0; index < mesh.indices.size(); ++index)
		{
			tinyobj::index_t i = mesh.indices[index];

			Vector3f position = Vector3f(
				attrib.vertices[i.vertex_index * 3 + 0],
				attrib.vertices[i.vertex_index * 3 + 1],
				attrib.vertices[i.vertex_index * 3 + 2]
			);
			Vector3f normal = Vector3f(
				attrib.normals[i.normal_index * 3 + 0],
				attrib.normals[i.normal_index * 3 + 1],
				attrib.normals[i.normal_index * 3 + 2]
			);
			Vector2f texture = Vector2f(
				attrib.texcoords[i.texcoord_index * 2 + 0],
				attrib.texcoords[i.texcoord_index * 2 + 1]
			);

			vertices.push_back(Vertex(position, normal, texture));
			indices.push_back(index);
		}

		Mesh* meshPtr = ResourceManager::Get().CreateResource<Mesh>(shape.name);
		meshPtr->Initialize(vertices, indices);
	}
	
	std::array<Texture2D*, 4> textures = {
		ResourceManager::Get().CreateResource<Texture2D>("red"),
		ResourceManager::Get().CreateResource<Texture2D>("green"),
		ResourceManager::Get().CreateResource<Texture2D>("yellow"),
		ResourceManager::Get().CreateResource<Texture2D>("pink"),
	};

	textures[0]->Initialize(resourcePath + L"Red.png");
	textures[1]->Initialize(resourcePath + L"Green.png");
	textures[2]->Initialize(resourcePath + L"Yellow.png");
	textures[3]->Initialize(resourcePath + L"Pink.png");

	while (!bIsDone)
	{
		InputManager::Get().Tick();

		Matrix4x4f view = MathUtils::CreateLookAt(Vector3f(0.0f, 30.0f, 30.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
		Matrix4x4f projection = MathUtils::CreatePerspective(MathUtils::ToRadian(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.01f, 1000.0f);

		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
		RenderManager::Get().RenderAxisGrid3D(view, projection, (-100.0f, -100.0f, -100.0f), Vector3f(+100.0f, +100.0f, +100.0f), 1.0f, Vector4f(1.0f, 1.0f, 1.0f, 0.5f));
		
		std::size_t index = 0;
		for (const auto& shape : shapes)
		{
			Mesh* mesh = ResourceManager::Get().GetResource<Mesh>(shape.name);
			RenderManager::Get().RenderMesh3D(Matrix4x4f::GetIdentity(), view, projection, mesh, textures[index]);
			index = (index + 1) % textures.size();
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