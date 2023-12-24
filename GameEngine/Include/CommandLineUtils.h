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
	 * - 전체 커맨드 라인은 실행 파일 경로가 제외된 문자열을 전달해야 합니다.
	 * 
	 * @param commandLine 전체 명령행 문자열의 포인터입니다.
	 */
	static void Parse(const wchar_t* commandLine);


	/**
	 * @brief 커맨드 라인(명령행 인자)를 파싱합니다.
	 * 
	 * @note
	 * - 이 메서드는 프로그램 시작 후 단 한 번만 호출할 수 있습니다.
	 * - 전체 명령행의 인자를 벡터로 전달해야 합니다.
	 * - 인자 형식은 "<key>=<value>" 형식만 지원합니다.
	 * 
	 * @param arguments 실행 파일 경로를 제외한 명령행 인자입니다.
	 */
	static void ParseArguments(const std::vector<std::wstring>& arguments);


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