#pragma once

#include <string>
#include <unordered_map>


/**
 * @brief 커맨드 라인(명령행)에 대한 확장 기능을 제공합니다.
 * 
 * @note
 * - 이 클래스의 기능은 "<key>=<value>" 기반으로 동작합니다.
 * - 이 확장 기능은 std::wstring 표준 문자열을 기반으로 동작합니다.
 * - 이 클래스의 모든 멤버 변수와 메서드는 모두 static입니다.
 */
class CommandLineUtils
{
public:
	/**
	 * @brief 커맨드 라인(명령행)을 파싱합니다.
	 * 
	 * @note
	 * - 이 메서드는 프로그램 시작 후 단 한 번만 호출할 수 있습니다.
	 * - 내부에서 전체 명령행을 찾아 파싱을 수행합니다.
	 */
	static void Parse();


	/**
	 * @brief 키 값에 대응하는 불리언 타입 값을 얻습니다.
	 * 
	 * @param key 값에 대응하는 키 값입니다.
	 * @param value 키 값에 대응하는 불리언 값입니다.
	 * 
	 * @return 키 값에 대응하는 불리언 타입 값을 얻는 데 성공했다면 true, 그렇지 않으면 false를 반환합니다.
	 * 
	 * @note boolean 값으로 true, True, TRUE, false, False, FALSE 모두 가능합니다.
	 */
	static bool GetBoolValue(const std::string& key, bool& value);


	/**
	 * @brief 키 값에 대응하는 불리언 타입 값을 얻습니다.
	 *
	 * @param key 값에 대응하는 키 값입니다.
	 * @param value 키 값에 대응하는 불리언 값입니다.
	 *
	 * @return 키 값에 대응하는 불리언 타입 값을 얻는 데 성공했다면 true, 그렇지 않으면 false를 반환합니다.
	 * 
	 * @note boolean 값으로 true, True, TRUE, false, False, FALSE 모두 가능합니다.
	 */
	static bool GetBoolValue(const std::wstring& key, bool& value);


	/**
	 * @brief 키 값에 대응하는 정수 타입 값을 얻습니다.
	 * 
	 * @param key 값에 대응하는 키 값입니다.
	 * @param value 키 값에 대응하는 정수 값입니다.
	 * 
	 * @return 키 값에 대응하는 정수 타입 값을 얻는 데 성공했다면 true, 그렇지 않다면 false를 반환합니다.
	 * 
	 * @note 음의 정수도 가능합니다.
	 */
	static bool GetIntValue(const std::string& key, int32_t& value);


	/**
	 * @brief 키 값에 대응하는 정수 타입 값을 얻습니다.
	 *
	 * @param key 값에 대응하는 키 값입니다.
	 * @param value 키 값에 대응하는 정수 값입니다.
	 *
	 * @return 키 값에 대응하는 정수 타입 값을 얻는 데 성공했다면 true, 그렇지 않다면 false를 반환합니다.
	 *
	 * @note 음의 정수도 가능합니다.
	 */
	static bool GetIntValue(const std::wstring& key, int32_t& value);


	/**
	 * @brief 키 값에 대응하는 부동 소수점 타입 값을 얻습니다.
	 *
	 * @param key 값에 대응하는 키 값입니다.
	 * @param value 키 값에 대응하는 부동 소수점 값입니다.
	 *
	 * @return 키 값에 대응하는 부동 소수점 타입 값을 얻는 데 성공했다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	static bool GetFloatValue(const std::string& key, float& value);


	/**
	 * @brief 키 값에 대응하는 부동 소수점 타입 값을 얻습니다.
	 *
	 * @param key 값에 대응하는 키 값입니다.
	 * @param value 키 값에 대응하는 부동 소수점 값입니다.
	 *
	 * @return 키 값에 대응하는 부동 소수점 타입 값을 얻는 데 성공했다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	static bool GetFloatValue(const std::wstring& key, float& value);


	/**
	 * @brief 키 값에 대응하는 문자열 타입 값을 얻습니다.
	 *
	 * @param key 값에 대응하는 키 값입니다.
	 * @param value 키 값에 대응하는 문자열 값입니다.
	 *
	 * @return 키 값에 대응하는 문자열 타입 값을 얻는 데 성공했다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	static bool GetStringValue(const std::string& key, std::string& value);


	/**
	 * @brief 키 값에 대응하는 문자열 타입 값을 얻습니다.
	 *
	 * @param key 값에 대응하는 키 값입니다.
	 * @param value 키 값에 대응하는 문자열 값입니다.
	 *
	 * @return 키 값에 대응하는 문자열 타입 값을 얻는 데 성공했다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	static bool GetStringValue(const std::string& key, std::wstring& value);


	/**
	 * @brief 키 값에 대응하는 문자열 타입 값을 얻습니다.
	 *
	 * @param key 값에 대응하는 키 값입니다.
	 * @param value 키 값에 대응하는 문자열 값입니다.
	 *
	 * @return 키 값에 대응하는 문자열 타입 값을 얻는 데 성공했다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	static bool GetStringValue(const std::wstring& key, std::string& value);


	/**
	 * @brief 키 값에 대응하는 문자열 타입 값을 얻습니다.
	 *
	 * @param key 값에 대응하는 키 값입니다.
	 * @param value 키 값에 대응하는 문자열 값입니다.
	 *
	 * @return 키 값에 대응하는 문자열 타입 값을 얻는 데 성공했다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	static bool GetStringValue(const std::wstring& key, std::wstring& value);


private:
	/**
	 * @brief 키 값이 유효한지 확인합니다.
	 * 
	 * @param key 유효한지 확인할 키 값입니다.
	 * 
	 * @return 키 값이 유효하다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	static bool IsValid(const std::wstring& key);

	
private:
	/**
	 * @brief 초기화된 적이 있는지 확인합니다.
	 */
	static bool bIsInitialized_;


	/**
	 * @brief 명령행 인자의 키-값 쌍입니다.
	 */
	static std::unordered_map<std::wstring, std::wstring> argumentMaps_;
};