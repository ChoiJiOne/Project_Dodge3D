#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <unordered_map>

#include "IManager.h"
#include "IResource.h"


/**
 * @brief 리소스 관리를 수행하는 매니저입니다.
 * 
 * @note 이 클래스는 싱글턴입니다.
 */
class ResourceManager : public IManager
{
public:
	/**
	 * @brief 리소스 관리를 수행하는 매니저의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(ResourceManager);


	/**
	 * @brief 리소스 관리를 수행하는 매니저의 참조 인스턴스를 얻습니다.
	 *
	 * @return 리소스 관리를 수행하는 매니저의 참조자를 반환합니다.
	 */
	static ResourceManager& Get()
	{
		static ResourceManager instance;
		return instance;
	}


	/**
	 * @brief 리소스 관리를 수행하는 매니저의 사용을 시작합니다.
	 *
	 * @note 이 메서드는 한 번만 호출되어야 합니다.
	 */
	virtual void Startup() override;


	/**
	 * @brief 리소스 관리를 수행하는 매니저의 사용을 종료합니다.
	 *
	 * @note
	 * - 애플리케이션 종료 전에 이 메서드를 반드시 호출하여 내부 리소스를 정리해야 합니다.
	 * - 이 메서드는 반드시 한 번만 호출되어야 합니다.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief 빈 리소스를 생성합니다.
	 *
	 * @note
	 * - 리소스 매니저는 초기화를 수행하지 않으므로, 반환하는 포인터 변수를 이용해서 초기화를 따로 수행해야 합니다.
	 * - 리소스의 시그니처 값은 중복을 허용하지 않습니다.
	 *
	 * @param signature 매니저 내부에서 리소스들을 구분할 시그니처 값입니다.
	 *
	 * @return 생성된 리소스의 포인터를 반환합니다.
	 */
	template <typename TResource>
	TResource* CreateResource(const std::string& signature)
	{
		ASSERT(!IsValidResourceKey(signature), "already exist resource signature %s key...", signature.c_str());

		std::unique_ptr<TResource> resource = std::make_unique<TResource>();
		resourceCache_.insert({ signature, std::move(resource) });

		return reinterpret_cast<TResource*>(resourceCache_.at(signature).get());
	}


	/**
	 * @brief 리소스 매니저가 관리하는 리소스를 얻습니다.
	 *
	 * @param signature 매니저 내부에서 리소스들을 구분할 시그니처 값입니다.
	 *
	 * @return 시그니처에 대응하는 리소스의 포인터를 얻습니다. 시그니처 값에 대응하는 리소스가 없으면 널 포인터를 반환합니다.
	 */
	template <typename TResource>
	TResource* GetResource(const std::string& signature)
	{
		if (!IsValidResourceKey(signature))
		{
			return nullptr;
		}

		return reinterpret_cast<TResource*>(resourceCache_.at(signature).get());
	}


	/**
	 * @brief 리소스 매니저가 관리하는 리소스를 삭제합니다.
	 *
	 * @param signature 삭제할 리소스의 시그니처 값입니다.
	 */
	void DestroyResource(const std::string& signature);


private:
	/**
	 * @brief 리소스 관리를 수행하는 매니저에 디폴트 생성자와 빈 가상 소멸자를 삽입합니다.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(ResourceManager);


	/**
	 * @brief 키 값이 유효한지 확인합니다.
	 * 
	 * @param key 유효한지 확인할 키 값입니다.
	 * 
	 * @return 키 값에 대응하는 리소스가 존재하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsValidResourceKey(const std::string& key);


private:
	/**
	 * @brief 리소스 매니저 내의 리소스 캐시입니다.
	 */
	std::unordered_map<std::string, std::unique_ptr<IResource>> resourceCache_;
};