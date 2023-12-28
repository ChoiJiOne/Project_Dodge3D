#include <cstdint>
#include <string>
#include <windows.h>

#include <glad/glad.h>

#include "Assertion.h"
#include "CommandLineUtils.h"
#include "FileManager.h"
#include "InputManager.h"
#include "MathUtils.h"
#include "Mesh.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "Texture2D.h"
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

void CreateAxisGrid(const Vector3f& minPosition, const Vector3f& maxPosition, const float& gap, const Vector4f& color, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices)
{
	static Vector4f xAxisColor = Vector4f(1.0f, 0.0f, 0.0f, 1.0f);
	static Vector4f yAxisColor = Vector4f(0.0f, 1.0f, 0.0f, 1.0f);
	static Vector4f zAxisColor = Vector4f(0.0f, 0.0f, 1.0f, 1.0f);

	outVertices.resize(0);
	outIndices.resize(0);

	uint32_t index = 0;
	Vector4f axisColor;
	for (float x = minPosition.x; x <= maxPosition.x; x += gap)
	{
		axisColor = (x == 0.0f) ? zAxisColor : color;

		outVertices.push_back(Vertex(Vector3f(x, 0.0f, minPosition.z), Vector3f(), Vector2f(), Vector3f(), Vector3f(), axisColor));
		outIndices.push_back(index++);

		outVertices.push_back(Vertex(Vector3f(x, 0.0f, maxPosition.z), Vector3f(), Vector2f(), Vector3f(), Vector3f(), axisColor));
		outIndices.push_back(index++);
	}

	for (float z = minPosition.z; z <= maxPosition.z; z += gap)
	{
		Vector4f axisColor = (z == 0.0f) ? xAxisColor : color;

		outVertices.push_back(Vertex(Vector3f(minPosition.x, 0.0f, z), Vector3f(), Vector2f(), Vector3f(), Vector3f(), axisColor));
		outIndices.push_back(index++);

		outVertices.push_back(Vertex(Vector3f(maxPosition.x, 0.0f, z), Vector3f(), Vector2f(), Vector3f(), Vector3f(), axisColor));
		outIndices.push_back(index++);
	}

	outVertices.push_back(Vertex(Vector3f(0.0f, minPosition.y, 0.0f), Vector3f(), Vector2f(), Vector3f(), Vector3f(), yAxisColor));
	outIndices.push_back(index++);

	outVertices.push_back(Vertex(Vector3f(0.0f, maxPosition.y, 0.0f), Vector3f(), Vector2f(), Vector3f(), Vector3f(), yAxisColor));
	outIndices.push_back(index++);
}

void RunApplication()
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	
	Shader* shader = ResourceManager::Get().CreateResource<Shader>("MeshColor");
	shader->Initialize(shaderPath + L"MeshColor.vert", shaderPath + L"MeshColor.frag");

	Mesh* grid = ResourceManager::Get().CreateResource<Mesh>("Grid");
	CreateAxisGrid(Vector3f(-100.0f, -100.0f, -100.0f), Vector3f(+100.0f, +100.0f, +100.0f), 1.0f, Vector4f(1.0f, 1.0f, 1.0f, 0.5f), vertices, indices);
	grid->Initialize(vertices, indices);
		
	while (!bIsDone)
	{
		InputManager::Get().Tick();

		/*static float time = 0.0f;
		time += 0.0001f;
		Matrix4x4f view = MathUtils::CreateLookAt(Vector3f(10.0f * MathUtils::Cos(time), 10.0f, 10.0f * MathUtils::Sin(time)), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));*/
		
		Matrix4x4f view = MathUtils::CreateLookAt(Vector3f(10.0f, 10.0f, 10.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
		Matrix4x4f projection = MathUtils::CreatePerspective(MathUtils::ToRadian(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.01f, 1000.0f);

		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
		{
			shader->Bind();

			shader->SetMatrix4x4fParameter("model", Matrix4x4f::GetIdentity());
			shader->SetMatrix4x4fParameter("view", view);
			shader->SetMatrix4x4fParameter("projection", projection);

			glBindVertexArray(grid->GetVertexArrayObject());
			glDrawElements(GL_LINES, grid->GetIndexCount(), GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
			shader->Unbind();
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
	RenderManager::Get().Startup();
	ResourceManager::Get().Startup();
	
	auto quitEvent = [&]() { bIsDone = true; };
	auto resizeEvent = [&]() {
		window.GetSize(width, height);
		RenderManager::Get().SetViewport(0, 0, width, height);
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