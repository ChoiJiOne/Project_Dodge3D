#include "IApplication.h"

#include "Floor.h"
#include "MovableCamera.h"
#include "StaticLight.h"


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
		MovableCamera* camera = ObjectManager::Get().CreateObject<MovableCamera>("MainCamera");
		camera->Initialize();

		StaticLight* light = ObjectManager::Get().CreateObject<StaticLight>("GlobalLight");
		light->Initialize();

		Floor* floor = ObjectManager::Get().CreateObject<Floor>("Floor");
		floor->Initialize();

		ShadowShader* shadowShader = ResourceManager::Get().GetResource<ShadowShader>("ShadowShader");
		LightShader* lightShader = ResourceManager::Get().GetResource<LightShader>("LightShader");

		const uint32_t SHADOW_WIDTH = 1024;
		const uint32_t SHADOW_HEIGHT = 1024;
		ShadowMap* shadowMap = ResourceManager::Get().CreateResource<ShadowMap>("shadowMap");
		shadowMap->Initialize(SHADOW_WIDTH, SHADOW_HEIGHT);
		
		timer_.Reset();
		while (!bIsDoneLoop_)
		{
			timer_.Tick();
			InputManager::Get().Tick();

			floor->Tick(timer_.GetDeltaSeconds());
			camera->Tick(timer_.GetDeltaSeconds());
			light->Tick(timer_.GetDeltaSeconds());
			
			{// 깊이 씬 그리기
				RenderManager::Get().SetDepthMode(true);
				RenderManager::Get().SetViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);

				shadowMap->Bind();
				shadowMap->Clear();

				shadowShader->Bind();
				shadowShader->SetLight(light);
				shadowShader->DrawMesh3D(MathUtils::CreateTranslation(floor->GetPosition()),  floor->GetMesh());

				shadowShader->Unbind();
				shadowMap->Unbind();
			}

			RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
			{ // 씬 그리기
				RenderManager::Get().SetWindowViewport();

				lightShader->Bind();
				lightShader->SetLight(light);
				lightShader->SetCamera(camera);

				lightShader->SetMaterial(floor->GetMaterial());
				lightShader->DrawMesh3D(MathUtils::CreateTranslation(floor->GetPosition()), floor->GetMesh(), shadowMap);

				lightShader->Unbind();
			}
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