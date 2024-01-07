#include "ClientApplication.h"

ClientApplication::~ClientApplication()
{
	Shutdown();
}

void ClientApplication::Setup()
{
	IGameFramework::Setup();
	clientPath_ = rootPath_ + L"Client/";

	auto clientResizeEvent = [&]() {
		int32_t width;
		int32_t height;
		window_->GetSize(width, height);
		glViewport(0, 0, width, height);
	};

	InputManager::Get().AddWindowEventAction("ClientResizeEvent",   EWindowEvent::Resize,       clientResizeEvent, true);
	InputManager::Get().AddWindowEventAction("ClientExitMinimize",  EWindowEvent::ExitMinimize, clientResizeEvent, true);
	InputManager::Get().AddWindowEventAction("ClientEnterMaximize", EWindowEvent::EnterMaximize,clientResizeEvent, true);
	InputManager::Get().AddWindowEventAction("ClientExitMaximize",  EWindowEvent::ExitMaximize, clientResizeEvent, true);
}

void ClientApplication::Shutdown()
{
}

void ClientApplication::Run()
{
	Vector3f cameraPosition = Vector3f(1.0f, 5.0f, 10.0f);

	Shader* depthShader = ResourceManager::Get().CreateResource<Shader>("depth");
	depthShader->Initialize(clientPath_ + L"Shader/Depth.vert", clientPath_ + L"Shader/Depth.frag");

	Shader* shadowShader = ResourceManager::Get().CreateResource<Shader>("shadow");
	shadowShader->Initialize(clientPath_ + L"Shader/Shadow.vert", clientPath_ + L"Shader/Shadow.frag");

	std::vector<StaticMesh::Vertex> vertices = {
		StaticMesh::Vertex(Vector3f(-1.0f, -1.0f, 0.0f), Vector3f(), Vector2f(0.0f, 0.0f)),
		StaticMesh::Vertex(Vector3f(+1.0f, -1.0f, 0.0f), Vector3f(), Vector2f(1.0f, 0.0f)),
		StaticMesh::Vertex(Vector3f(+1.0f, +1.0f, 0.0f), Vector3f(), Vector2f(1.0f, 1.0f)),
		StaticMesh::Vertex(Vector3f(-1.0f, +1.0f, 0.0f), Vector3f(), Vector2f(0.0f, 1.0f)),
	};

	std::vector<uint32_t> indices = {
		0, 1, 2,
		0, 2, 3,
	};
	StaticMesh* quad = ResourceManager::Get().CreateResource<StaticMesh>("quad");
	quad->Initialize(vertices, indices);

	vertices = {
		StaticMesh::Vertex(Vector3f(-25.0f, -0.5f, -25.0f), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(0.0f, 0.0f)),
		StaticMesh::Vertex(Vector3f(+25.0f, -0.5f, -25.0f), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(1.0f, 0.0f)),
		StaticMesh::Vertex(Vector3f(+25.0f, -0.5f, +25.0f), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(1.0f, 1.0f)),
		StaticMesh::Vertex(Vector3f(-25.0f, -0.5f, +25.0f), Vector3f(0.0f, 1.0f, 0.0f), Vector2f(0.0f, 1.0f)),
	};

	indices = {
		0, 1, 2,
		0, 2, 3,
	};
	StaticMesh* floor = ResourceManager::Get().CreateResource<StaticMesh>("floor");
	floor->Initialize(vertices, indices);

	StaticMesh* cube = ResourceManager::Get().CreateResource<StaticMesh>("cube");
	GeometryGenerator::CreateCube(Vector3f(2.0f, 2.0f, 2.0f), vertices, indices);
	cube->Initialize(vertices, indices);

	const uint32_t SHADOW_WIDTH = 1024;
	const uint32_t SHADOW_HEIGHT = 1024;

	uint32_t depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);

	uint32_t depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	Vector3f lightPosition = Vector3f(-2.0f, 4.0f, -2.0f);

	timer_.Reset();
	while (!bIsDoneLoop_)
	{
		timer_.Tick();
		InputManager::Get().Tick();

		lightPosition = Vector3f(
			2.0f * MathUtils::Sin(timer_.GetTotalSeconds() / 10.0f),
			4.0f, 
			2.0f * MathUtils::Cos(timer_.GetTotalSeconds() / 10.0f)
		);

		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

		float nearPlane = 1.0f;
		float farPlane = 7.5f;
		Matrix4x4f lightView = MathUtils::CreateLookAt(lightPosition, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
		Matrix4x4f lightProjection = MathUtils::CreateOrtho(-10.0f, +10.0f, -10.0f, +10.0f, nearPlane, farPlane);

		depthShader->Bind();
		depthShader->SetUniform("lightView", lightView);
		depthShader->SetUniform("lightProjection", lightProjection);

		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);

		depthShader->SetUniform("world", MathUtils::CreateTranslation(Vector3f(0.0f, -1.5f, 0.0f)));
		glBindVertexArray(floor->GetVertexArrayObject());
		glDrawElements(GL_TRIANGLES, floor->GetIndexCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// 1.
		Matrix4x4f world = MathUtils::CreateScale(Vector3f(0.5f, 0.5f, 0.5f)) * MathUtils::CreateTranslation(Vector3f(0.0f, 1.5f, 0.0f));
		depthShader->SetUniform("world", world);
		glBindVertexArray(cube->GetVertexArrayObject());
		glDrawElements(GL_TRIANGLES, cube->GetIndexCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// 2.
		world = MathUtils::CreateScale(Vector3f(0.5f, 0.5f, 0.5f)) * MathUtils::CreateTranslation(Vector3f(2.0f, 0.0f, 1.0f));
		depthShader->SetUniform("world", world);
		glBindVertexArray(cube->GetVertexArrayObject());
		glDrawElements(GL_TRIANGLES, cube->GetIndexCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// 3.
		world = MathUtils::CreateScale(Vector3f(0.25f, 0.25f, 0.25f))
			  * MathUtils::CreateRotate(MathUtils::ToRadian(60.0f), Vector3f(1.0f, 0.0f, 1.0f)) 
			  * MathUtils::CreateTranslation(Vector3f(-1.0f, 0.0f, 2.0f));
		depthShader->SetUniform("world", world);
		glBindVertexArray(cube->GetVertexArrayObject());
		glDrawElements(GL_TRIANGLES, cube->GetIndexCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		depthShader->Unbind();

		RenderManager::Get().SetWindowViewport();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Matrix4x4f view = MathUtils::CreateLookAt(cameraPosition, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
		Matrix4x4f projection = MathUtils::CreatePerspective(MathUtils::ToRadian(45.0f), window_->GetAspectSize(), 0.1f, 100.0f);

		shadowShader->Bind();
		shadowShader->SetUniform("view", view);
		shadowShader->SetUniform("projection", projection);
		shadowShader->SetUniform("lightView", lightView);
		shadowShader->SetUniform("lightProjection", lightProjection);
		shadowShader->SetUniform("lightPosition", lightPosition);
		shadowShader->SetUniform("viewPosition", cameraPosition);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthMap);

		shadowShader->SetUniform("world", MathUtils::CreateTranslation(Vector3f(0.0f, -1.5f, 0.0f)));
		glBindVertexArray(floor->GetVertexArrayObject());
		glDrawElements(GL_TRIANGLES, floor->GetIndexCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// 1.
		world = MathUtils::CreateScale(Vector3f(0.5f, 0.5f, 0.5f)) * MathUtils::CreateTranslation(Vector3f(0.0f, 1.5f, 0.0f));
		shadowShader->SetUniform("world", world);
		glBindVertexArray(cube->GetVertexArrayObject());
		glDrawElements(GL_TRIANGLES, cube->GetIndexCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// 2.
		world = MathUtils::CreateScale(Vector3f(0.5f, 0.5f, 0.5f)) * MathUtils::CreateTranslation(Vector3f(2.0f, 0.0f, 1.0f));
		shadowShader->SetUniform("world", world);
		glBindVertexArray(cube->GetVertexArrayObject());
		glDrawElements(GL_TRIANGLES, cube->GetIndexCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// 3.
		world = MathUtils::CreateScale(Vector3f(0.25f, 0.25f, 0.25f))
			* MathUtils::CreateRotate(MathUtils::ToRadian(60.0f), Vector3f(1.0f, 0.0f, 1.0f))
			* MathUtils::CreateTranslation(Vector3f(-1.0f, 0.0f, 2.0f));
		shadowShader->SetUniform("world", world);
		glBindVertexArray(cube->GetVertexArrayObject());
		glDrawElements(GL_TRIANGLES, cube->GetIndexCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		shadowShader->Unbind();

		RenderManager::Get().RenderLine3D(view, projection, Vector3f(-10.0f,   0.0f,   0.0f), Vector3f(+10.0f,   0.0f,   0.0f), Vector4f(1.0f, 0.0f, 0.0f, 1.0f));
		RenderManager::Get().RenderLine3D(view, projection, Vector3f(  0.0f, -10.0f,   0.0f), Vector3f(  0.0f, +10.0f,   0.0f), Vector4f(0.0f, 1.0f, 0.0f, 1.0f));
		RenderManager::Get().RenderLine3D(view, projection, Vector3f(  0.0f,   0.0f, -10.0f), Vector3f(  0.0f,   0.0f, +10.0f), Vector4f(0.0f, 0.0f, 1.0f, 1.0f));
		RenderManager::Get().RenderLine3D(view, projection, Vector3f(0.0f, 0.0f, 0.0f), lightPosition, Vector4f(0.0f, 1.0f, 1.0f, 1.0f));
		RenderManager::Get().EndFrame();
	}

	glDeleteTextures(1, &depthMap);
	glDeleteFramebuffers(1, &depthMapFBO);
}