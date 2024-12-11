#pragma once

#include <array>
#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Assertion.h"
#include "AudioManager.h"
#include "Box3D.h"
#include "Camera3D.h"
#include "CommandLineUtils.h"
#include "FileUtils.h"
#include "Framebuffer.h"
#include "GameTimer.h"
#include "GeometryGenerator.h"
#include "InputManager.h"
#include "IManager.h"
#include "IObject.h"
#include "IScene.h"
#include "Light.h"
#include "LightShader.h"
#include "Macro.h"
#include "Material.h"
#include "MathUtils.h"
#include "ObjectManager.h"
#include "PostEffectShader.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Shader.h"
#include "ShadowMap.h"
#include "ShadowShader.h"
#include "Skybox.h"
#include "Sound.h"
#include "Sphere3D.h"
#include "StaticMesh.h"
#include "StringUtils.h"
#include "Texture2D.h"
#include "Transform.h"
#include "TTFont.h"
#include "Window.h"
#include "WindowsCrashUtils.h"


/**
 * @brief 애플리케이션 인터페이스입니다.
 *
 * @note 애플리케이션을 초기화 및 실행하는 클래스는 반드시 이 클래스를 상속받아야 합니다.
 */
class IApplication
{
public:
	/**
	 * @brief 애플리케이션 인터페이스의 생성자입니다.
	 */
	IApplication();


	/**
	 * @brief 애플리케이션 인터페이스의 가상 소멸자입니다.
	 */
	virtual ~IApplication();


	/**
	 * @brief 애플리케이션 인터페이스의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(IApplication);


	/**
	 * @brief 애플리케이션 인터페이스를 초기화합니다.
	 *
	 * @note 하위 클래스에서는 초기화 전에 이 메서드를 반드시 호출해야 합니다.
	 */
	virtual void Setup();


	/**
	 * @brief 애플리케이션 인터페이스의 사용을 종료합니다.
	 */
	virtual void Shutdown();


	/**
	 * @brief 애플리케이션을 실행합니다.
	 */
	virtual void Run() = 0;

	
protected:
	/**
	 * @brief 애플리케이션의 속성을 설정합니다.
	 * 
	 * @param windowTitle 애플리케이션의 윈도우 타이틀입니다.
	 * @param windowPosX 애플리케이션의 화면 상 윈도우의 X 위치입니다.
	 * @param windowPosY 애플리케이션의 화면 상 윈도우의 X 위치입니다.
	 * @param windowWidth 애플리케이션의 윈도우 가로 크기입니다.
	 * @param windowHeight 애플리케이션의 윈도우 세로 크기입니다.
	 * @param bIsResize 애플리케이션의 윈도우 크기 변경 여부입니다.
	 * @param bIsFullscreen 애플리케이션의 윈도우 풀 스크린 여부입니다.
	 * @param bIsVsync 애플리케이션의 수직 동기화 여부입니다.
	 * @param bIsImGui ImGui 라이브러리 사용 여부입니다.
	 */
	void SetProperties(
		const std::wstring& windowTitle, 
		int32_t windowPosX,
		int32_t windowPosY,
		int32_t windowWidth, 
		int32_t windowHeight,
		bool bIsResize,
		bool bIsFullscreen,
		bool bIsVsync,
		bool bIsImGui
	);

	
protected:
	/**
	 * @brief 게임 프레임워크를 초기화했는지 확인합니다.
	 */
	bool bIsSetup_ = false;


	/**
	 * @brief 속성 설정에 성공했는지 확인합니다.
	 */
	bool bIsPropertiesSet_ = false;


	/**
	 * @brief 개발 모드인지 확인합니다.
	 */
	bool bIsDevMode_ = false;


	/**
	 * @brief 애플리케이션 윈도우 타이틀입니다.
	 */
	std::wstring windowTitle_;


	/**
	 * @brief 애플리케이션의 화면 상 (x, y) 좌표입니다.
	 */
	Vector2i windowPosition_;


	/**
	 * @brief 애플리케이션의 화면 상의 가로 크기입니다.
	 */
	int32_t windowWidth_ = 0;


	/**
	 * @brief 애플리케이션의 화면 상의 세로 크기입니다.
	 */
	int32_t windowHeight_ = 0;


	/**
	 * @brief 애플리케이션의 윈도우 크기 변경 여부입니다.
	 */
	bool bIsResize_ = false;


	/**
	 * @brief 애플리케이션의 윈도우 풀 스크린 여부입니다.
	 */
	bool bIsFullscreen_ = false;


	/**
	 * @brief 애플리케이션의 수직 동기화 여부입니다.
	 */
	bool bIsVsync_ = true;


	/**
	 * @brief ImGui 라이브러리 사용 여부입니다.
	 */
	bool bIsImGui_ = false;

	
	/**
	 * @brief 게임 루프 종료가 감지되었는지 확인합니다.
	 */
	bool bIsDoneLoop_ = false;

	
	/**
	 * @brief 게임 윈도우입니다.
	 */
	std::unique_ptr<Window> window_ = nullptr;
};