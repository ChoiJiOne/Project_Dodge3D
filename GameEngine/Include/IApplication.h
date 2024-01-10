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
#include "FileUtils.h"
#include "GameTimer.h"
#include "GeometryGenerator.h"
#include "GLAssertion.h"
#include "InputManager.h"
#include "IManager.h"
#include "IObject.h"
#include "Macro.h"
#include "Material.h"
#include "MathUtils.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Shader.h"
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
 * @brief 애플리케이션 인터페이스입니다.
 *
 * @note 애플리케이션을 초기화 및 실행하는 클래스는 반드시 이 클래스를 상속받아야 합니다.
 */
class IApplication
{
public:
	/**
	 * @brief 애플리케이션 인터페이스의 디폴트 생성자입니다.
	 */
	IApplication() = default;


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