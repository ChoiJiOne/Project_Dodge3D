#include "IApplication.h"

#include "DirectionalLightShader.h"
#include "Properties.h"


/**
 * @brief Geometry 생성 툴 애플리케이션입니다.
 */
class GeometryExporterApp : public IApplication
{
public:
	/**
	 * @brief 생성 툴 애플리케이션의 디폴트 생성자입니다.
	 */
	GeometryExporterApp() = default;


	/**
	 * @brief 생성 툴 애플리케이션의 가상 소멸자입니다.
	 */
	virtual ~GeometryExporterApp()
	{
		Shutdown();
	}


	/**
	 * @brief 생성 툴 애플리케이션의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(GeometryExporterApp);


	/**
	 * @brief 생성 툴 프레임워크를 초기화합니다.
	 */
	virtual void Setup() override
	{
		IApplication::Setup();

		toolPath_ = rootPath_ + L"GeometryExporter/";
	}


	/**
	 * @brief 생성 툴 프레임워크 사용을 종료합니다.
	 */
	virtual void Shutdown() override
	{
		IApplication::Shutdown();
	}


	/**
	 * @brief 생성 툴 프레임워크를 실행합니다.
	 */
	virtual void Run() override
	{
		Camera3D* camera = ObjectManager::Get().CreateObject<Camera3D>("camera");
		camera->Initialize(
			Vector3f(0.0f, 5.0f, 5.0f),
			Vector3f(0.0f, -1.0f, -1.0f),
			Vector3f(0.0f, 1.0f, 0.0f),
			MathUtils::ToRadian(45.0f),
			window_->GetAspectSize(),
			0.01f,
			1000.0f
		);

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		GeometryGenerator::CreateSphere(1.0f, 40, vertices, indices);

		StaticMesh* sphere = ResourceManager::Get().CreateResource<StaticMesh>("sphere");
		sphere->Initialize(vertices, indices);

		Material* material = ResourceManager::Get().CreateResource<Material>("material");
		material->Initialize(
			Vector3f(0.329412f, 0.223529f, 0.027451f),
			Vector3f(0.780392f, 0.568627f, 0.113725f),
			Vector3f(0.992157f, 0.941176f, 0.807843f),
			128.0f * 0.21794872f
		);

		DirectionalLightShader* directionalLightShader = ResourceManager::Get().CreateResource<DirectionalLightShader>("DirectionalLightShader");
		directionalLightShader->Initialize(toolPath_ + L"Shader/DirectionalLight.vert", toolPath_ + L"Shader/DirectionalLight.frag");

		Properties* properties = ObjectManager::Get().CreateObject<Properties>("Properties");
		properties->Initialize();

		timer_.Reset();
		while (!bIsDoneLoop_)
		{
			timer_.Tick();
			InputManager::Get().Tick();
			
			properties->Tick(timer_.GetDeltaSeconds());
			
			RenderManager::Get().SetWindowViewport();
			RenderManager::Get().SetDepthMode(true);
			RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
			
			directionalLightShader->Bind();
			directionalLightShader->SetCamera(camera);
			directionalLightShader->SetMaterial(material);
			directionalLightShader->SetDirectionalLight(properties->GetDirectionalLight());

			directionalLightShader->DrawMesh3D(Matrix4x4f::GetIdentity(), sphere);

			directionalLightShader->Unbind();

			RenderManager::Get().RenderGrid3D(
				camera->GetViewMatrix(), camera->GetProjectionMatrix(),
				-10.0f, +10.0f, 1.0f, -10.0f, +10.0f, 1.0f, Vector4f(1.0f, 1.0f, 1.0f, 0.5f)
			);
			RenderManager::Get().EndFrame();
		}
	}


private:
	/**
	 * @brief 툴 경로입니다.
	 */
	std::wstring toolPath_;


	/**
	 * @brief 타이머입니다.
	 */
	GameTimer timer_;
};


int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
	std::unique_ptr<IApplication> app = std::make_unique<GeometryExporterApp>();
	app->Setup();
	app->Run();
	app->Shutdown();
	return 0;
}