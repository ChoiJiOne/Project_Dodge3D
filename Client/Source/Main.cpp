#include "IApplication.h"

#include "DemoScene.h"

#include <imgui.h>


/**
 * @brief 게임 애플리케이션입니다.
 */
class GameApplication : public IApplication
{
public:
	/**
	 * @brief 게임 애플리케이션의 디폴트 생성자입니다.
	 */
	GameApplication() = default;


	/**
	 * @brief 게임 애플리케이션의 가상 소멸자입니다.
	 */
	virtual ~GameApplication()
	{
		Shutdown();
	}


	/**
	 * @brief 게임 애플리케이션의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(GameApplication);


	/**
	 * @brief 게임 프레임워크를 초기화합니다.
	 */
	virtual void Setup() override
	{
		IApplication::Setup();

		clientPath_ = rootPath_ + L"Client/";

		ImGui::StyleColorsDark();
		
	}


	/**
	 * @brief 게임 프레임워크 사용을 종료합니다.
	 */
	virtual void Shutdown() override
	{
		IApplication::Shutdown();
	}


	/**
	 * @brief 게임 프레임워크를 실행합니다.
	 */
	virtual void Run() override
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		StaticMesh* wall = ResourceManager::Get().CreateResource<StaticMesh>("wall");
		GeometryGenerator::CreateCube(Vector3f(+1.0f, +5.0f, +5.0f), vertices, indices);
		wall->Initialize(vertices, indices);

		StaticMesh* cube = ResourceManager::Get().CreateResource<StaticMesh>("cube");
		GeometryGenerator::CreateCube(Vector3f(+1.0f, +1.0f, +1.0f), vertices, indices);
		cube->Initialize(vertices, indices);
		
		StaticMesh* sphere = ResourceManager::Get().CreateResource<StaticMesh>("sphere");
		GeometryGenerator::CreateSphere(0.5f, 40, vertices, indices);
		sphere->Initialize(vertices, indices);

		Texture2D* wood = ResourceManager::Get().CreateResource<Texture2D>("wood");
		wood->Initialize(clientPath_ + L"Resource/wood.png");

		Shader* pointShadowsDepth = ResourceManager::Get().CreateResource<Shader>("PointShadowsDepth");
		pointShadowsDepth->Initialize(clientPath_ + L"Shader/PointShadowsDepth.vert", clientPath_ + L"Shader/PointShadowsDepth.geom", clientPath_ + L"Shader/PointShadowsDepth.frag");

		Shader* pointShadows = ResourceManager::Get().CreateResource<Shader>("PointShadows");
		pointShadows->Initialize(clientPath_ + L"Shader/PointShadows.vert", clientPath_ + L"Shader/PointShadows.frag");

		const uint32_t SHADOW_WIDTH = 1024;
		const uint32_t SHADOW_HEIGHT = 1024;

		uint32_t depthMapFBO;
		glGenFramebuffers(1, &depthMapFBO);

		uint32_t depthCubemap;
		glGenTextures(1, &depthCubemap);
		glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
		for (uint32_t i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		timer_.Reset();
		while (!bIsDoneLoop_)
		{
			timer_.Tick();
			InputManager::Get().Tick();

			int32_t width;
			int32_t height;
			window_->GetSize(width, height);

			Vector3f cameraPosition(0.0f, 5.0f, 10.0f);
			static Vector3f lightPosition(0.0f, 0.0f, 0.0f);

			ImGui::Begin("Position");
			ImGui::SliderFloat3("Position", lightPosition.GetPtr(), -1.0f, 1.0f);
			ImGui::End();

			Matrix4x4f view = MathUtils::CreateLookAt(cameraPosition, Vector3f(+0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
			Matrix4x4f projection = MathUtils::CreatePerspective(MathUtils::ToRadian(45.0f), window_->GetAspectSize(), 0.01f, 1000.0f);

			float nearPlane = 0.01f;
			float farPlane = 1000.0f;

			Matrix4x4f shadowProjection = MathUtils::CreatePerspective(MathUtils::ToRadian(90.0f), 1.0f, nearPlane, farPlane);
			std::vector<Matrix4x4f> shadowLookAts = {
				MathUtils::CreateLookAt(lightPosition, lightPosition + Vector3f(+1.0f, +0.0f, +0.0f), Vector3f(0.0f, -1.0f,  0.0f)),
				MathUtils::CreateLookAt(lightPosition, lightPosition + Vector3f(-1.0f, +0.0f, +0.0f), Vector3f(0.0f, -1.0f,  0.0f)),
				MathUtils::CreateLookAt(lightPosition, lightPosition + Vector3f(+0.0f, +1.0f, +0.0f), Vector3f(0.0f,  0.0f,  1.0f)),
				MathUtils::CreateLookAt(lightPosition, lightPosition + Vector3f(+0.0f, -1.0f, +0.0f), Vector3f(0.0f,  0.0f, -1.0)),
				MathUtils::CreateLookAt(lightPosition, lightPosition + Vector3f(+0.0f, +0.0f, +1.0f), Vector3f(0.0f, -1.0f,  0.0f)),
				MathUtils::CreateLookAt(lightPosition, lightPosition + Vector3f(+0.0f, +0.0f, -1.0f), Vector3f(0.0f, -1.0f,  0.0f)),
			};

			{// 1. 
				glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
				glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
				glClear(GL_DEPTH_BUFFER_BIT);
				pointShadowsDepth->Bind();
				pointShadowsDepth->SetUniform("shadowProjection", shadowProjection);
				for (std::size_t index = 0; index < shadowLookAts.size(); ++index)
				{
					pointShadowsDepth->SetUniform(StringUtils::PrintF("shaodwLookAts[%d]", index), shadowLookAts[index]);
				}
				pointShadowsDepth->SetUniform("farPlane", farPlane);
				pointShadowsDepth->SetUniform("lightPosition", lightPosition);

				{// 장면 그리기
					pointShadowsDepth->SetUniform("world", MathUtils::CreateTranslation(Vector3f(-5.0f, 0.0f, 0.0f)));
					GL_ASSERT(glBindVertexArray(wall->GetVertexArrayObject()), "failed to bind static mesh vertex array...");
					GL_ASSERT(glDrawElements(GL_TRIANGLES, wall->GetIndexCount(), GL_UNSIGNED_INT, 0), "failed to draw static mesh...");
					GL_ASSERT(glBindVertexArray(0), "failed to unbind static mesh vertex array...");

					pointShadowsDepth->SetUniform("world", MathUtils::CreateTranslation(Vector3f(+5.0f, 0.0f, 0.0f)));
					GL_ASSERT(glBindVertexArray(wall->GetVertexArrayObject()), "failed to bind static mesh vertex array...");
					GL_ASSERT(glDrawElements(GL_TRIANGLES, wall->GetIndexCount(), GL_UNSIGNED_INT, 0), "failed to draw static mesh...");
					GL_ASSERT(glBindVertexArray(0), "failed to unbind static mesh vertex array...");

					pointShadowsDepth->SetUniform("world", MathUtils::CreateTranslation(Vector3f(-3.0f, 0.0f, 0.0f)));
					GL_ASSERT(glBindVertexArray(sphere->GetVertexArrayObject()), "failed to bind static mesh vertex array...");
					GL_ASSERT(glDrawElements(GL_TRIANGLES, sphere->GetIndexCount(), GL_UNSIGNED_INT, 0), "failed to draw static mesh...");
					GL_ASSERT(glBindVertexArray(0), "failed to unbind static mesh vertex array...");

					pointShadowsDepth->SetUniform("world", MathUtils::CreateTranslation(Vector3f(+3.0f, 0.0f, 0.0f)));
					GL_ASSERT(glBindVertexArray(cube->GetVertexArrayObject()), "failed to bind static mesh vertex array...");
					GL_ASSERT(glDrawElements(GL_TRIANGLES, cube->GetIndexCount(), GL_UNSIGNED_INT, 0), "failed to draw static mesh...");
					GL_ASSERT(glBindVertexArray(0), "failed to unbind static mesh vertex array...");
				}
				pointShadowsDepth->Unbind();
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}
			{// 2.
				RenderManager::Get().SetWindowViewport();
				RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

				pointShadows->Bind();
				pointShadows->SetUniform("view", view);
				pointShadows->SetUniform("projection", projection);
				pointShadows->SetUniform("lightPosition", lightPosition);
				pointShadows->SetUniform("viewPosition", cameraPosition);
				pointShadows->SetUniform("farPlane", farPlane);

				wood->Active(0);

				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);

				{
					pointShadows->SetUniform("world", MathUtils::CreateTranslation(Vector3f(-5.0f, 0.0f, 0.0f)));
					GL_ASSERT(glBindVertexArray(wall->GetVertexArrayObject()), "failed to bind static mesh vertex array...");
					GL_ASSERT(glDrawElements(GL_TRIANGLES, wall->GetIndexCount(), GL_UNSIGNED_INT, 0), "failed to draw static mesh...");
					GL_ASSERT(glBindVertexArray(0), "failed to unbind static mesh vertex array...");

					pointShadows->SetUniform("world", MathUtils::CreateTranslation(Vector3f(+5.0f, 0.0f, 0.0f)));
					GL_ASSERT(glBindVertexArray(wall->GetVertexArrayObject()), "failed to bind static mesh vertex array...");
					GL_ASSERT(glDrawElements(GL_TRIANGLES, wall->GetIndexCount(), GL_UNSIGNED_INT, 0), "failed to draw static mesh...");
					GL_ASSERT(glBindVertexArray(0), "failed to unbind static mesh vertex array...");

					pointShadows->SetUniform("world", MathUtils::CreateTranslation(Vector3f(-3.0f, 0.0f, 0.0f)));
					GL_ASSERT(glBindVertexArray(sphere->GetVertexArrayObject()), "failed to bind static mesh vertex array...");
					GL_ASSERT(glDrawElements(GL_TRIANGLES, sphere->GetIndexCount(), GL_UNSIGNED_INT, 0), "failed to draw static mesh...");
					GL_ASSERT(glBindVertexArray(0), "failed to unbind static mesh vertex array...");

					pointShadows->SetUniform("world", MathUtils::CreateTranslation(Vector3f(+3.0f, 0.0f, 0.0f)));
					GL_ASSERT(glBindVertexArray(cube->GetVertexArrayObject()), "failed to bind static mesh vertex array...");
					GL_ASSERT(glDrawElements(GL_TRIANGLES, cube->GetIndexCount(), GL_UNSIGNED_INT, 0), "failed to draw static mesh...");
					GL_ASSERT(glBindVertexArray(0), "failed to unbind static mesh vertex array...");
				}
				pointShadows->Unbind();
			}

			RenderManager::Get().RenderLine3D(view, projection, Vector3f(-3.0f, 0.0f, 0.0f), lightPosition, Vector4f(0.0f, 1.0f, 0.0f, 1.0f));
			RenderManager::Get().RenderLine3D(view, projection, Vector3f(+3.0f, 0.0f, 0.0f), lightPosition, Vector4f(0.0f, 1.0f, 0.0f, 1.0f));
			RenderManager::Get().RenderGrid3D(view, projection, -10.0f, 10.0f, 1.0f, -10.0f, 10.0f, 1.0f, Vector4f(1.0f, 1.0f, 1.0f, 0.5f));
			RenderManager::Get().EndFrame();
		}
	}


private:
	/**
	 * @brief 클라이언트 경로입니다.
	 */
	std::wstring clientPath_;


	/**
	 * @brief 게임 타이머입니다.
	 */
	GameTimer timer_;
};


int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
	std::unique_ptr<IApplication> game = std::make_unique<GameApplication>();
	game->Setup();
	game->Run();
	game->Shutdown();
	return 0;
}