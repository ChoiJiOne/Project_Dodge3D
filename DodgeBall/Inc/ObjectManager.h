#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <unordered_map>

#include "Assertion.h"
#include "IManager.h"
#include "IObject.h"


/**
 * @brief 오브젝트 관리를 수행하는 매니저입니다.
 *
 * @note 이 클래스는 싱글턴입니다.
 */
class ObjectManager : public IManager
{
public:
	/**
	 * @brief 오브젝트 관리를 수행하는 매니저의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(ObjectManager);


	/**
	 * @brief 오브젝트 관리를 수행하는 매니저의 참조 인스턴스를 얻습니다.
	 *
	 * @return 오브젝트 관리를 수행하는 매니저의 참조자를 반환합니다.
	 */
	static ObjectManager& Get()
	{
		static ObjectManager instance;
		return instance;
	}


	/**
	 * @brief 오브젝트 관리를 수행하는 매니저의 사용을 시작합니다.
	 *
	 * @note 이 메서드는 한 번만 호출되어야 합니다.
	 */
	virtual void Startup() override;


	/**
	 * @brief 오브젝트 관리를 수행하는 매니저의 사용을 종료합니다.
	 *
	 * @note
	 * - 애플리케이션 종료 전에 이 메서드를 반드시 호출하여 내부 오브젝트를 정리해야 합니다.
	 * - 이 메서드는 반드시 한 번만 호출되어야 합니다.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief 빈 오브젝트를 생성합니다.
	 *
	 * @note
	 * - 오브젝트 매니저는 초기화를 수행하지 않으므로, 반환하는 포인터 변수를 이용해서 초기화를 따로 수행해야 합니다.
	 * - 오브젝트의 시그니처 값은 중복을 허용하지 않습니다.
	 *
	 * @param signature 매니저 내부에서 오브젝트들을 구분할 시그니처 값입니다.
	 *
	 * @return 생성된 오브젝트의 포인터를 반환합니다.
	 */
	template <typename TObject>
	TObject* CreateObject(const std::string& signature)
	{
		ASSERT(!IsValidObjectKey(signature), "already exist object signature %s key...", signature.c_str());

		std::unique_ptr<TObject> object = std::make_unique<TObject>();
		objectCache_.insert({ signature, std::move(object) });

		return reinterpret_cast<TObject*>(objectCache_.at(signature).get());
	}


	/**
	 * @brief 오브젝트 매니저가 관리하는 오브젝트를 얻습니다.
	 *
	 * @param signature 매니저 내부에서 오브젝트들을 구분할 시그니처 값입니다.
	 *
	 * @return 시그니처에 대응하는 오브젝트의 포인터를 얻습니다. 시그니처 값에 대응하는 오브젝트가 없으면 널 포인터를 반환합니다.
	 */
	template <typename TObject>
	TObject* GetObject(const std::string& signature)
	{
		if (!IsValidObjectKey(signature))
		{
			return nullptr;
		}

		return reinterpret_cast<TObject*>(objectCache_.at(signature).get());
	}


	/**
	 * @brief 오브젝트 매니저가 관리하는 오브젝트를 삭제합니다.
	 *
	 * @param signature 삭제할 오브젝트의 시그니처 값입니다.
	 */
	void DestroyObject(const std::string& signature);


private:
	/**
	 * @brief 오브젝트 관리를 수행하는 매니저에 디폴트 생성자와 빈 가상 소멸자를 삽입합니다.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(ObjectManager);


	/**
	 * @brief 키 값이 유효한지 확인합니다.
	 *
	 * @param key 유효한지 확인할 키 값입니다.
	 *
	 * @return 키 값에 대응하는 오브젝트가 존재하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsValidObjectKey(const std::string& key);


private:
	/**
	 * @brief 오브젝트 매니저 내의 오브젝트 캐시입니다.
	 */
	std::unordered_map<std::string, std::unique_ptr<IObject>> objectCache_;
};