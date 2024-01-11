#include "IApplication.h"


/**
 * @brief Geometry ���� �� ���ø����̼��Դϴ�.
 */
class GeometryExporterApp : public IApplication
{
public:
	/**
	 * @brief ���� �� ���ø����̼��� ����Ʈ �������Դϴ�.
	 */
	GeometryExporterApp() = default;


	/**
	 * @brief ���� �� ���ø����̼��� ���� �Ҹ����Դϴ�.
	 */
	virtual ~GeometryExporterApp()
	{
		Shutdown();
	}


	/**
	 * @brief ���� �� ���ø����̼��� ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(GeometryExporterApp);


	/**
	 * @brief ���� �� �����ӿ�ũ�� �ʱ�ȭ�մϴ�.
	 */
	virtual void Setup() override
	{
		IApplication::Setup();

		toolPath_ = rootPath_ + L"GeometryExporter/";
	}


	/**
	 * @brief ���� �� �����ӿ�ũ ����� �����մϴ�.
	 */
	virtual void Shutdown() override
	{
		IApplication::Shutdown();
	}


	/**
	 * @brief ���� �� �����ӿ�ũ�� �����մϴ�.
	 */
	virtual void Run() override
	{
		timer_.Reset();
		while (!bIsDoneLoop_)
		{
			timer_.Tick();
			InputManager::Get().Tick();

			RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
			RenderManager::Get().EndFrame();
		}
	}


private:
	/**
	 * @brief �� ����Դϴ�.
	 */
	std::wstring toolPath_;


	/**
	 * @brief Ÿ�̸��Դϴ�.
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