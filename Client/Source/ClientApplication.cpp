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

		projection_ = MathUtils::CreatePerspective(MathUtils::ToRadian(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.01f, 1000.0f);

		glViewport(0, 0, width, height);
	};
	InputManager::Get().AddWindowEventAction("ClientResizeEvent",   EWindowEvent::Resize,        clientResizeEvent, true);
	InputManager::Get().AddWindowEventAction("ClientExitMinimize",  EWindowEvent::ExitMinimize,  clientResizeEvent, true);
	InputManager::Get().AddWindowEventAction("ClientEnterMaximize", EWindowEvent::EnterMaximize, clientResizeEvent, true);
	InputManager::Get().AddWindowEventAction("ClientExitMaximize",  EWindowEvent::ExitMaximize,  clientResizeEvent, true);

	int32_t width;
	int32_t height;
	window_->GetSize(width, height);

	view_ = MathUtils::CreateLookAt(Vector3f(5.0f, 5.0f, 5.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
	projection_ = MathUtils::CreatePerspective(MathUtils::ToRadian(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.01f, 1000.0f);

	std::vector<StaticMesh::Vertex> vertices;
	std::vector<uint32_t> indices;

	GeometryGenerator::CreateCube(Vector3f(4.0f, 1.0f, 4.0f), vertices, indices);
	floor_ = ResourceManager::Get().CreateResource<StaticMesh>("floor");
	floor_->Initialize(vertices, indices);

	chrome_ = ResourceManager::Get().CreateResource<Material>("chrome");
	chrome_->Initialize(Vector3f(0.25f, 0.25f, 0.25f), Vector3f(0.4f, 0.4f, 0.4f), Vector3f(0.774597f, 0.774597f, 0.774597f), 76.8);

	GeometryGenerator::CreateSphere(3.0f, 50, vertices, indices);
	sphere_ = ResourceManager::Get().CreateResource<StaticMesh>("sphere");
	sphere_->Initialize(vertices, indices);

	gold_ = ResourceManager::Get().CreateResource<Material>("gold");
	gold_->Initialize(Vector3f(0.24725f, 0.1995f, 0.0745f), Vector3f(0.75164f, 0.60648f, 0.22648f), Vector3f(0.628281f, 0.555802f, 0.366065f), 51.2f);

	shader_ = ResourceManager::Get().CreateResource<Shader>("EffectLights");
	shader_->Initialize(clientPath_ + L"Shader/EffectLights.vert", clientPath_ + L"Shader/EffectLights.frag");
}

void ClientApplication::Shutdown()
{
}

void ClientApplication::Run()
{
	float yDirection = -1.0f;

	timer_.Reset();
	while (!bIsDoneLoop_)
	{
		timer_.Tick();
		InputManager::Get().Tick();
		{ // 업데이트 시작...

		}

		RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
		{ // 렌더링 시작...
			shader_->Bind();
			shader_->SetUniform("world", MathUtils::CreateTranslation(Vector3f(0.0f, 0.5f, 0.0f)));
			shader_->SetUniform("view", view_);
			shader_->SetUniform("projection", projection_);

			shader_->SetUniform("cameraPosition", Vector3f(5.0f, 5.0f, 5.0f));
			shader_->SetUniform("material.ambient", gold_->GetAmbient());
			shader_->SetUniform("material.diffuse", gold_->GetDiffuse());
			shader_->SetUniform("material.specular", gold_->GetSpecular());
			shader_->SetUniform("material.shininess", gold_->GetShininess());
			shader_->SetUniform("light.direction", Vector3f(-1.0f, yDirection, 0.0f));
			shader_->SetUniform("light.ambient", Vector3f(0.2f, 0.2f, 0.2f));
			shader_->SetUniform("light.diffuse", Vector3f(0.5f, 0.5f, 0.5f));
			shader_->SetUniform("light.specular", Vector3f(1.0f, 1.0f, 1.0f));

			glBindVertexArray(floor_->GetVertexArrayObject());
			glDrawElements(GL_TRIANGLES, floor_->GetIndexCount(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			shader_->Unbind();

			RenderManager::Get().RenderGrid3D(view_, projection_, -10.0f, 10.0f, 1.0f, -10.0f, 10.0f, 1.0f, Vector4f(1.0f, 1.0f, 1.0f, 0.5f));
		}


		RenderManager::Get().EndFrame();
	}
}