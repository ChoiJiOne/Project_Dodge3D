#include <cstdint>
#include <string>
#include <windows.h>

#include <glad/glad.h>

#include "Assertion.h"
#include "CommandLineUtils.h"
#include "FileManager.h"
#include "InputManager.h"
#include "MathUtils.h"
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

void CreateGrid(std::vector<VertexPositionColor>& vertices, uint32_t& vao, uint32_t& vbo)
{
	float minX = -100.0f;
	float maxX = 100.0f;
	float minY = -100.0f;
	float maxY = 100.0f;
	float minZ = -100.0f;
	float maxZ = 100.0f;
	float gap = 1.0f;
	Vector4f color = Vector4f(1.0f, 1.0f, 1.0f, 1.0f);

	for (float x = minX; x <= maxX; x += gap)
	{
		color = (x == 0.0f) ? Vector4f(1.0f, 0.0f, 0.0f, 1.0f) : Vector4f(1.0f, 1.0f, 1.0f, 0.5f);
		
		vertices.push_back(VertexPositionColor(Vector3f(x, 0.0f, minZ), color));
		vertices.push_back(VertexPositionColor(Vector3f(x, 0.0f, maxZ), color));
	}

	for (float z = minZ; z <= maxZ; z += gap)
	{
		color = (z == 0.0f) ? Vector4f(0.0f, 0.0f, 1.0f, 1.0f) : Vector4f(1.0f, 1.0f, 1.0f, 0.5f);
		
		vertices.push_back(VertexPositionColor(Vector3f(minX, 0.0f, z), color));
		vertices.push_back(VertexPositionColor(Vector3f(maxX, 0.0f, z), color));
	}

	vertices.push_back(VertexPositionColor(Vector3f(0.0f, minY, 0.0f), Vector4f(0.0f, 1.0f, 0.0f, 1.0f)));
	vertices.push_back(VertexPositionColor(Vector3f(0.0f, maxY, 0.0f), Vector4f(0.0f, 1.0f, 0.0f, 1.0f)));
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, static_cast<uint32_t>(vertices.size()) * VertexPositionColor::GetStride(), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VertexPositionColor::GetStride(), (void*)(offsetof(VertexPositionColor, position)));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexPositionColor::GetStride(), (void*)(offsetof(VertexPositionColor, color)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void RunApplication()
{
	Shader* shader = ResourceManager::Get().CreateResource<Shader>("Shader");
	shader->Initialize(shaderPath + L"Shader.vert", shaderPath + L"Shader.frag");

	std::vector<VertexPositionColor> vertices;
	uint32_t vao;
	uint32_t vbo;
	CreateGrid(vertices, vao, vbo);

	while (!bIsDone)
	{
		InputManager::Get().Tick();

		Matrix4x4f view = MathUtils::CreateLookAt(Vector3f(10.0f, 10.0f, 10.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
		Matrix4x4f projection = MathUtils::CreatePerspective(MathUtils::ToRadian(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.01f, 1000.0f);

		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
		{
			shader->Bind();

			shader->SetMatrix4x4fParameter("model", Matrix4x4f::GetIdentity());
			shader->SetMatrix4x4fParameter("view", view);
			shader->SetMatrix4x4fParameter("projection", projection);

			glBindVertexArray(vao);
			glDrawArrays(GL_LINES, 0, static_cast<uint32_t>(vertices.size()));

			glBindVertexArray(0);
			shader->Unbind();
		}
		RenderManager::Get().EndFrame();
	}

	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
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