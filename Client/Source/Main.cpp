#include "IApplication.h"


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
		Box3D aabb0(Vector3f(-2.0f, 0.0f, -2.0f), Vector3f(1.0f, 1.0f, 1.0f));
		Box3D aabb1(Vector3f(+2.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
		
		Camera3D* camera = ObjectManager::Get().CreateObject<Camera3D>("camera");
		camera->Initialize(
			Vector3f(0.0f, 5.0f, 5.0f),
			Vector3f(0.0f, -1.0f, -1.0f),
			Vector3f(0.0f, 1.0f, 0.0f),
			MathUtils::ToRadian(45.0f),
			window_->GetAspectSize(),
			0.1f,
			100.0f
		);


		Vector4f collision;

		timer_.Reset();
		while (!bIsDoneLoop_)
		{
			timer_.Tick();
			InputManager::Get().Tick();

			if (InputManager::Get().GetVirtualKeyPressState(EVirtualKey::VKEY_RIGHT) == EPressState::Pressed)
			{
				Vector3f center0 = aabb0.GetCenter();
				center0.x += 0.1f;
				center0.z += 0.1f;
				aabb0.SetCenter(center0);
			}
			
			collision = aabb0.IsCollision(aabb1) ? Vector4f(1.0f, 0.0f, 0.0f, 1.0f) : Vector4f(0.0f, 0.0f, 1.0f, 1.0f);

			RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
			RenderManager::Get().SetWindowViewport();

			RenderManager::Get().RenderAxisAlignedBoundingBox3D(camera, aabb0.GetCenter(), aabb0.GetExtents(), collision);
			RenderManager::Get().RenderAxisAlignedBoundingBox3D(camera, aabb1.GetCenter(), aabb1.GetExtents(), collision);

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