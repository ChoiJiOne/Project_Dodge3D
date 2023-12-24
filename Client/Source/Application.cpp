#include <cstdint>
#include <string>
#include <windows.h>

#include <glad/glad.h>

#include "CommandLineUtils.h"
#include "FileManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Window.h"

bool bIsDone = false;

int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
	CommandLineUtils::Parse();
	Window::RegisterWindowClass(L"ProjectA", InputManager::WindowProc);

	Window window;
	window.Create(L"ProjectA", 200, 200, 800, 600, true, false);
	InputManager::Get().SetInputControlWindow(&window);
	RenderManager::Get().SetRenderTargetWindow(&window);

	FileManager::Get().Startup();
	InputManager::Get().Startup();
	RenderManager::Get().Startup();

	auto quitEvent = [&]() { bIsDone = true; };
	auto resizeEvent = [&]() {
		int32_t width;
		int32_t height;
		window.GetSize(width, height);
		glViewport(0, 0, width, height);
	};
		
	InputManager::Get().AddWindowEventAction("CloseLoop",     EWindowEvent::Close,         quitEvent,   true);
	InputManager::Get().AddWindowEventAction("Resize",        EWindowEvent::Resize,        resizeEvent, true);
	InputManager::Get().AddWindowEventAction("ExitMinimize",  EWindowEvent::ExitMinimize,  resizeEvent, true);
	InputManager::Get().AddWindowEventAction("EnterMaximize", EWindowEvent::EnterMaximize, resizeEvent, true);
	InputManager::Get().AddWindowEventAction("ExitMaximize",  EWindowEvent::ExitMaximize,  resizeEvent, true);

	std::wstring shaderPath;
	CommandLineUtils::GetStringValue(L"shaderPath", shaderPath);

	std::vector<uint8_t> vertexShaderBuffer = FileManager::Get().ReadBufferFromFile(shaderPath + L"Shader.vert");
	std::vector<uint8_t> fragmentShaderBuffer = FileManager::Get().ReadBufferFromFile(shaderPath + L"Shader.frag");

	std::string vertexShaderSource = std::string(vertexShaderBuffer.begin(), vertexShaderBuffer.end());
	const char* vertexShaderSourcePtr = vertexShaderSource.c_str();
	uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSourcePtr, nullptr);
	glCompileShader(vertexShader);
	
	std::string fragmentShaderSource = std::string(fragmentShaderBuffer.begin(), fragmentShaderBuffer.end());
	const char* fragmentShaderSourcePtr = fragmentShaderSource.c_str();
	uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSourcePtr, nullptr);
	glCompileShader(fragmentShader);

	uint32_t shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	std::vector<Vector3f> vertices = {
		Vector3f(-0.5f, -0.5f, 0.0f),
		Vector3f(+0.5f, -0.5f, 0.0f),
		Vector3f(+0.0f, +0.5f, 0.0f),
	};

	uint32_t vbo;
	uint32_t vao;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, static_cast<uint32_t>(vertices.size()) * sizeof(Vector3f), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3f), (void*)(0));
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	while (!bIsDone)
	{
		InputManager::Get().Tick();

		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
		{
			glUseProgram(shaderProgram);
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, static_cast<uint32_t>(vertices.size()));

			glBindVertexArray(0);
			glUseProgram(0);
		}
		RenderManager::Get().EndFrame();
	}

	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(shaderProgram);
	
	RenderManager::Get().Shutdown();
	InputManager::Get().Shutdown();
	FileManager::Get().Shutdown();
	window.Destroy();

	Window::UnregisterWindowClass();
	return 0;
}