#pragma once

#include <array>
#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Assertion.h"
#include "CommandLineUtils.h"
#include "DirectionalLight.h"
#include "FileUtils.h"
#include "GameTimer.h"
#include "GeometryGenerator.h"
#include "GLAssertion.h"
#include "InputManager.h"
#include "Macro.h"
#include "Material.h"
#include "MathUtils.h"
#include "PointLight.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "SpotLight.h"
#include "StaticMesh.h"
#include "StringUtils.h"
#include "ShadowMap.h"
#include "Skybox.h"
#include "Texture2D.h"
#include "TTFont.h"
#include "Window.h"
#include "WindowsAssertion.h"
#include "WindowsCrashUtils.h"


/**
 * @brief 게임 프레임워크 인터페이스입니다.
 * 
 * @note 게임 루프가 구현되는 클래스는 반드시 이 인터페이스를 상속받아야 합니다.
 */
class IGameFramework
{
public:
	/**
	 * @brief 게임 프레임워크의 디폴트 생성자입니다.
	 */
	IGameFramework() = default;


	/**
	 * @brief 게임 프레임워크의 가상 소멸자입니다.
	 */
	virtual ~IGameFramework();


	/**
	 * @brief 게임 프레임워크의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(IGameFramework);


	/**
	 * @brief 게임 프레임워크를 초기화합니다.
	 */
	virtual void Setup();


	/**
	 * @brief 게임 프레임워크 사용을 종료합니다.
	 */
	virtual void Shutdown();


	/**
	 * @brief 게임 프레임워크를 실행합니다.
	 */
	virtual void Run() = 0;


protected:
	/**
	 * @brief 게임 프레임워크를 초기화했는지 확인합니다.
	 */
	bool bIsSetup_ = false;


	/**
	 * @brief 게임 루프 종료가 감지되었는지 확인합니다.
	 */
	bool bIsDoneLoop_ = false;


	/**
	 * @brief 루트 경로입니다.
	 */
	std::wstring rootPath_;


	/**
	 * @brief 게임 엔진 경로입니다.
	 */
	std::wstring enginePath_;


	/**
	 * @brief 게임 윈도우입니다.
	 */
	std::unique_ptr<Window> window_ = nullptr;
};