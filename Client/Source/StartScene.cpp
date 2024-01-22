#include "StartScene.h"

#include "Assertion.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Sound.h"
#include "ObjectManager.h"
#include "MathUtils.h"
#include "Window.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

void StartScene::Tick(float deltaSeconds)
{
	if (sceneState_ == ESceneState::Ready)
	{
		mainTitle_->Tick(deltaSeconds);
		startButton_->Tick(deltaSeconds);
		quitButton_->Tick(deltaSeconds);
	}
	else // sceneState_ == ESceneState::Start
	{
		stepTime_ += deltaSeconds;
		stepTime_ = MathUtils::Clamp<float>(stepTime_, 0.0f, fadeOutStepTime_);

		if (stepTime_ >= fadeOutStepTime_)
		{
			bDetectSwitchScene_ = true;
		}
	}

	RenderManager::Get().SetWindowViewport();
	RenderManager::Get().BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);

	if (sceneState_ == ESceneState::Start)
	{
		framebuffer_->Bind();
		framebuffer_->Clear(0.0f, 0.0f, 0.0f, 1.0f);
	}

	mainTitle_->Render();
	startButton_->Render();
	quitButton_->Render();

	if (sceneState_ == ESceneState::Start)
	{
		float fadeBias = 1.0f - MathUtils::Clamp<float>(stepTime_ / fadeOutStepTime_, 0.0f, 1.0f);

		framebuffer_->Unbind();
		postEffectShader_->Bind();
		postEffectShader_->SetUniform("fadeBias", fadeBias);
		postEffectShader_->BlitEffect(framebuffer_);
		postEffectShader_->Unbind();
	}
	RenderManager::Get().EndFrame();
}

void StartScene::EnterScene()
{
	LoadResources();
	LoadObjects();

	stepTime_ = 0.0f;
	fadeOutStepTime_ = 1.0f;

	sceneState_ = ESceneState::Ready;
	bIsEnterScene_ = true;
	bDetectSwitchScene_ = false;
}

void StartScene::ExitScene()
{
	bIsEnterScene_ = false;
}

void StartScene::LoadResources()
{
	font32_ = ResourceManager::Get().GetResource<TTFont>("Font32");
	font128_ = ResourceManager::Get().GetResource<TTFont>("Font128");
	buttonClick_ = ResourceManager::Get().GetResource<Sound>("ButtonClick");

	framebuffer_ = ResourceManager::Get().GetResource<Framebuffer>("StartScene_Framebuffer");
	if (!framebuffer_)
	{
		int32_t bufferWidth;
		int32_t bufferHeight;
		RenderManager::Get().GetRenderTargetWindow()->GetSize(bufferWidth, bufferHeight);

		framebuffer_ = ResourceManager::Get().CreateResource<Framebuffer>("StartScene_Framebuffer");
		framebuffer_->Initialize(bufferWidth, bufferHeight);
	}

	postEffectShader_ = ResourceManager::Get().GetResource<PostEffectShader>("FadeEffect");
}

void StartScene::LoadObjects()
{
	int32_t windowWidth;
	int32_t windowHeight;
	RenderManager::Get().GetRenderTargetWindow()->GetSize(windowWidth, windowHeight);
	Vector2f windowCenter(static_cast<float>(windowWidth) / 2.0f, static_cast<float>(windowHeight) / 2.0f);

	mainTitle_ = ObjectManager::Get().GetObject<UIPanel>("StartScene_MainTitle");
	if (!mainTitle_)
	{
		mainTitle_ = ObjectManager::Get().CreateObject<UIPanel>("StartScene_MainTitle");
		mainTitle_->Initialize(
			UIPanel::UIPanelConstructParam {
				600.0f,
				200.0f,
				windowCenter - Vector2f(0.0f, 100.0f),
				L"Dodge3D",
				font128_,
				Vector4f(0.227f, 0.663f,   1.0f, 0.9f),
				Vector4f(0.094f, 0.122f, 0.165f, 0.9f),
				Vector4f(0.227f, 0.663f,   1.0f, 0.9f)
			}
		);
	}

	startButton_ = ObjectManager::Get().GetObject<UIMouseButton>("StartScene_StartButton");
	if (!startButton_)
	{
		startButton_ = ObjectManager::Get().CreateObject<UIMouseButton>("StartScene_StartButton");
		startButton_->Initialize(
			UIMouseButton::UIButtonConstructParam{
				200.0f,
				50.0f,
				windowCenter + Vector2f(0.0f, 100.0f),
				L"Start",
				font32_,
				Vector4f(0.227f, 0.663f,   1.0f, 0.7f),
				Vector4f(0.227f, 0.663f,   1.0f, 1.0f),
				Vector4f(0.118f, 0.180f, 0.286f, 0.7f),
				Vector4f(0.145f, 0.267f, 0.431f, 0.7f),
				Vector4f(0.224f, 0.486f, 0.804f, 0.7f),
				Vector4f(0.118f, 0.180f, 0.286f, 0.7f),
				UIMouseButton::EType::LButton,
				[&]() {
					buttonClick_->Play();
					sceneState_ = ESceneState::Start;
				}
			}
		);
	}

	quitButton_ = ObjectManager::Get().GetObject<UIMouseButton>("StartScene_QuitButton");
	if (!quitButton_)
	{
		quitButton_ = ObjectManager::Get().CreateObject<UIMouseButton>("StartScene_QuitButton");
		quitButton_->Initialize(
			UIMouseButton::UIButtonConstructParam{
				200.0f,
				50.0f,
				windowCenter + Vector2f(0.0f, 200.0f),
				L"Quit",
				font32_,
				Vector4f(0.227f, 0.663f,   1.0f, 0.7f),
				Vector4f(0.227f, 0.663f,   1.0f, 1.0f),
				Vector4f(0.118f, 0.180f, 0.286f, 0.7f),
				Vector4f(0.145f, 0.267f, 0.431f, 0.7f),
				Vector4f(0.224f, 0.486f, 0.804f, 0.7f),
				Vector4f(0.118f, 0.180f, 0.286f, 0.7f),
				UIMouseButton::EType::LButton,
				loopQuitEvent_
			}
		);
	}
}