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

void LoadWavefrontFile(const std::string& path, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices)
{
	std::string basePath = FileManager::Get().GetBasePath(path);

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	tinyobj::LoadObj(&attrib, &shapes, &materials, nullptr, path.c_str(), basePath.c_str());

	for (const auto& shape : shapes)
	{
		const tinyobj::mesh_t& mesh = shape.mesh;

		for (std::size_t index = 0; index < mesh.indices.size(); ++index)
		{
			tinyobj::index_t idx = mesh.indices[index];

			Vector3f position;
			Vector3f normal;
			Vector2f texture;

			if (idx.vertex_index >= 0)
			{
				float x = attrib.vertices[idx.vertex_index * 3 + 0];
				float y = attrib.vertices[idx.vertex_index * 3 + 1];
				float z = attrib.vertices[idx.vertex_index * 3 + 2];

				position = Vector3f(x, y, z);
			}

			if (idx.normal_index >= 0)
			{
				float nx = attrib.normals[idx.normal_index * 3 + 0];
				float ny = attrib.normals[idx.normal_index * 3 + 1];
				float nz = attrib.normals[idx.normal_index * 3 + 2];
				
				normal = Vector3f(nx, ny, nz);
			}

			if (idx.texcoord_index >= 0)
			{
				float u = attrib.texcoords[idx.texcoord_index * 2 + 0];
				float v = attrib.texcoords[idx.texcoord_index * 2 + 1];

				texture = Vector2f(u, v);
			}

			outVertices.push_back(Vertex(position, normal, texture));
			outIndices.push_back(index);
		}
	}
}

void RunApplication()
{
	std::string objPath = StringUtils::Convert(resourcePath) + "Sphere.obj";
	
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	LoadWavefrontFile(objPath, vertices, indices);

	Mesh* mesh = ResourceManager::Get().CreateResource<Mesh>("Sphere");
	mesh->Initialize(vertices, indices);

	Texture2D* texture = ResourceManager::Get().CreateResource<Texture2D>("Texture");
	texture->Initialize(resourcePath + L"Magenta.png");

	while (!bIsDone)
	{
		InputManager::Get().Tick();

		Matrix4x4f view = MathUtils::CreateLookAt(Vector3f(1.0f, 5.0f, 5.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
		Matrix4x4f projection = MathUtils::CreatePerspective(MathUtils::ToRadian(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.01f, 1000.0f);

		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
		RenderManager::Get().RenderAxisGrid3D(view, projection, (-100.0f, -100.0f, -100.0f), Vector3f(+100.0f, +100.0f, +100.0f), 1.0f, Vector4f(1.0f, 1.0f, 1.0f, 0.5f));
		RenderManager::Get().RenderMesh3D(Matrix4x4f::GetIdentity(), view, projection, mesh, texture);

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