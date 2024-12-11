#include "IApplication.h"

#include "Config.h"
#include "GameScene.h"
#include "RankScene.h"
#include "StartScene.h"


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
		IApplication::SetProperties(WINDOW_TITLE, WINDOW_X, WINDOW_Y, WINDOW_W, WINDOW_H, WINDOW_RESIZE, WINDOW_FULLSCREEN, WINDOW_VSYNC, WINDOW_IMGUI);
		IApplication::Setup();
		
		window_->SetIcon(L"Resource/Icon/Icon.ico");

		LoadResources();
		LoadScenes();
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
		IScene* currentScene = startScene_;
		currentScene->EnterScene();

		timer_.Reset();
		while (!bIsDoneLoop_)
		{
			timer_.Tick();
			InputManager::Get().Tick();

			currentScene->Tick(timer_.GetDeltaSeconds());

			if (currentScene->DetectSwitchScene())
			{
				currentScene->ExitScene();
				currentScene = currentScene->GetNextScene();
				currentScene->EnterScene();
			}
		}
	}


private:
	/**
	 * @brief 리소스를 로딩합니다.
	 */
	void LoadResources()
	{
		std::wstring resourcePath = clientPath_ + L"Resource/";

		TTFont* font32 = ResourceManager::Get().CreateResource<TTFont>("Font32");
		font32->Initialize(resourcePath + L"Font/SeoulNamsanEB.ttf", 32, 127, 32.0f);

		TTFont* font64 = ResourceManager::Get().CreateResource<TTFont>("Font64");
		font64->Initialize(resourcePath + L"Font/SeoulNamsanEB.ttf", 32, 127, 64.0f);

		TTFont* font128 = ResourceManager::Get().CreateResource<TTFont>("Font128");
		font128->Initialize(resourcePath + L"Font/SeoulNamsanEB.ttf", 32, 127, 128.0f);

		Sound* buttonClickSound = ResourceManager::Get().CreateResource<Sound>("ButtonClick");
		buttonClickSound->Initialize(resourcePath + L"Sound/ButtonClick.mp3");
		buttonClickSound->SetLooping(false);

		Sound* hitSound = ResourceManager::Get().CreateResource<Sound>("Hit");
		hitSound->Initialize(resourcePath + L"Sound/Hit.mp3");
		hitSound->SetLooping(false);
	}


	/**
	 * @brief 씬을 로딩합니다.
	 */
	void LoadScenes()
	{
		loopQuitEvent_ = [&]() { bIsDoneLoop_ = true; };

		startScene_ = SceneManager::Get().CreateScene<StartScene>("StartScene");
		gameScene_ = SceneManager::Get().CreateScene<GameScene>("GameScene");
		rankScene_ = SceneManager::Get().CreateScene<RankScene>("RankScene");

		startScene_->SetLoopQuitEvent(loopQuitEvent_);
		startScene_->SetNextScene(gameScene_);

		gameScene_->SetLoopQuitEvent(loopQuitEvent_);
		gameScene_->SetNextResetScene(startScene_);
		gameScene_->SetNextRankScene(rankScene_);

		rankScene_->SetLoopQuitEvent(loopQuitEvent_);
		rankScene_->SetNextScene(startScene_);
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


	/**
	 * @brief 게임 루프 종료 이벤트입니다.
	 */
	std::function<void()> loopQuitEvent_ = nullptr;


	/**
	 * @brief 게임 시작 씬입니다.
	 */
	StartScene* startScene_ = nullptr;


	/**
	 * @brief 게임 플레이 씬입니다.
	 */
	GameScene* gameScene_ = nullptr;


	/**
	 * @brief 플레이어의 랭킹을 보여주는 씬입니다.
	 */
	RankScene* rankScene_ = nullptr;
};


int32_t WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int32_t nCmdShow)
{
	std::unique_ptr<IApplication> game = std::make_unique<GameApplication>();
	game->Setup();
	game->Run();
	game->Shutdown();
	return 0;
}