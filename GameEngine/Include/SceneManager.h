#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#include "IManager.h"
#include "IScene.h"


/**
 * @brief 게임 내의 씬을 관리하는 매니저입니다.
 *
 * @note 이 클래스는 싱글턴입니다.
 */
class SceneManager : public IManager
{
public:
	/**
	 * @brief 씬 관리를 수행하는 매니저의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(SceneManager);


	/**
	 * @brief 씬 관리를 수행하는 매니저의 참조 인스턴스를 얻습니다.
	 *
	 * @return 씬 관리를 수행하는 매니저의 참조자를 반환합니다.
	 */
	static SceneManager& Get()
	{
		static SceneManager instance;
		return instance;
	}


	/**
	 * @brief 씬 관리를 수행하는 매니저의 사용을 시작합니다.
	 *
	 * @note 이 메서드는 한 번만 호출되어야 합니다.
	 */
	virtual void Startup() override;


	/**
	 * @brief 씬 관리를 수행하는 매니저의 사용을 종료합니다.
	 *
	 * @note
	 * - 애플리케이션 종료 전에 이 메서드를 반드시 호출하여 내부 씬을 정리해야 합니다.
	 * - 이 메서드는 반드시 한 번만 호출되어야 합니다.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief 씬을 생성합니다.
	 *
	 * @param signature 매니저 내부에서 씬을 구분할 시그니처 값입니다.
	 *
	 * @return 생성된 씬의 포인터를 반환합니다.
	 *
	 * @note 씬의 시그니처 값은 중복을 허용하지 않습니다.
	 */
	template <typename TScene>
	TScene* CreateScene(const std::string& signature)
	{
		ASSERT(!IsValidSceneKey(signature), "already exist scene signature key : %s", signature.c_str());

		std::unique_ptr<TScene> scene = std::make_unique<TScene>();
		scenes_.insert({ signature, std::move(scene) });

		return reinterpret_cast<TScene*>(scenes_.at(signature).get());
	}


	/**
	 * @brief 씬 매니저가 관리하는 리소스를 얻습니다.
	 *
	 * @param signature 매니저 내부에서 씬들을 구분할 시그니처 값입니다.
	 *
	 * @return 시그니처에 대응하는 씬 포인터를 얻습니다. 시그니처 값에 대응하는 씬이 없으면 널 포인터를 반환합니다.
	 */
	template <typename TScene>
	TScene* GetScene(const std::string& signature)
	{
		if (!IsValidSceneKey(signature))
		{
			return nullptr;
		}

		return reinterpret_cast<TScene*>(scenes_.at(signature).get());
	}


	/**
	 * @brief 씬 매니저가 관리하는 씬을 삭제합니다.
	 *
	 * @param signature 삭제할 씬의 시그니처 값입니다.
	 */
	void DestroyScene(const std::string& signature);
	

private:
	/**
	 * @brief 씬 관리를 수행하는 매니저에 디폴트 생성자와 빈 가상 소멸자를 삽입합니다.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(SceneManager);


	/**
	 * @brief 시그니처 값에 대응하는 씬이 존재하는지 확인합니다.
	 *
	 * @param signature 씬이 존재하는 지 확인할 시그니처 값입니다.
	 *
	 * @return 시그니처 값이 유효하다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsValidSceneKey(const std::string& signature);


private:
	/**
	 * @brief 씬 매니저가 관리하는 씬입니다.
	 */
	std::unordered_map<std::string, std::unique_ptr<IScene>> scenes_;
};