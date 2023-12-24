#include <cstdint>
#include <string>
#include <windows.h>

#include <glad/glad.h>

#include "CommandLineUtils.h"
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

	std::string vertexShaderSource =
		"#version 460 core\n"
		"layout(location = 0) in vec3 inPosition;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = vec4(inPosition, 1.0f);\n"
		"}";
	const char* vertexShaderSourcePtr = vertexShaderSource.c_str();
	uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSourcePtr, nullptr);
	glCompileShader(vertexShader);
	
	std::string fragmentShaderSource =
		"#version 460 core\n"
		"layout(location = 0) out vec4 outColor;\n"
		"void main()\n"
		"{\n"
		"    outColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
		"}";
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
	window.Destroy();

	Window::UnregisterWindowClass();
	return 0;
}