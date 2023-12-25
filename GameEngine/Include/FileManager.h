#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <windows.h>

#include <json/json.h>

#include "IManager.h"


/**
 * @brief 파일 및 디렉토리 관련 처리를 수행하는 매니저입니다.
 * 
 * @note 이 클래스는 싱글턴입니다.
 */
class FileManager : public IManager
{
public:
	/**
	 * @brief 파일 및 디렉토리 처리를 수행하는 매니저의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(FileManager);


	/**
	 * @brief 파일 및 디렉토리 처리를 수행하는 매니저의 참조 인스턴스를 얻습니다.
	 *
	 * @return 파일 및 디렉토리 처리를 수행하는 매니저의 참조자를 반환합니다.
	 */
	static FileManager& Get()
	{
		static FileManager instance;
		return instance;
	}


	/**
	 * @brief 파일 및 디렉토리 처리를 수행하는 매니저의 사용을 시작합니다.
	 *
	 * @note 이 메서드는 한 번만 호출되어야 합니다.
	 */
	virtual void Startup() override;


	/**
	 * @brief 파일 및 디렉토리 처리를 수행하는 매니저의 사용을 종료합니다.
	 *
	 * @note
	 * - 애플리케이션 종료 전에 이 메서드를 반드시 호출하여 내부 리소스를 정리해야 합니다.
	 * - 이 메서드는 반드시 한 번만 호출되어야 합니다.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief 실행 파일 경로를 얻습니다.
	 * 
	 * @return 실행 파일 경로를 반환합니다.
	 */
	const std::wstring& GetExecutePath() const { return executePath_; }


	/**
	 * @brief 파일을 읽고 버퍼에 저장합니다.
	 * 
	 * @param path 파일의 경로입니다.
	 * 
	 * @return 파일의 버퍼 벡터를 반환합니다.
	 * 
	 * @see 
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createfilea
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-readfile
	 */
	std::vector<uint8_t> ReadBufferFromFile(const std::string& path);


	/**
	 * @brief 파일을 읽고 버퍼에 저장합니다.
	 * 
	 * @param path 파일의 경로입니다.
	 * 
	 * @return 파일의 버퍼 벡터를 반환합니다.
	 * 
	 * @see
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createfilew
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-readfile
	 */
	std::vector<uint8_t> ReadBufferFromFile(const std::wstring& path);


	/**
	 * @brief 버퍼를 파일에 씁니다.
	 * 
	 * @param path 버퍼를 쓸 파일의 경로입니다.
	 * @param buffer 파일에 쓸 버퍼입니다.
	 * 
	 * @see
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createfilea
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-writefile
	 */
	void WriteBufferToFile(const std::string& path, const std::vector<uint8_t>& buffer);


	/**
	 * @brief 버퍼를 파일에 씁니다.
	 *
	 * @param path 버퍼를 쓸 파일의 경로입니다.
	 * @param buffer 파일에 쓸 버퍼입니다.
	 *
	 * @see
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-createfilew
	 * - https://learn.microsoft.com/ko-kr/windows/win32/api/fileapi/nf-fileapi-writefile
	 */
	void WriteBufferToFile(const std::wstring& path, const std::vector<uint8_t>& buffer);


	/**
	 * @brief 파일 혹은 디렉토리가 유효한지 확인합니다.
	 * 
	 * @param path 유효한지 확인할 파일 혹은 디렉토리 경로입니다.
	 * 
	 * @return 파일 혹은 디렉토리가 유효하다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsValidPath(const std::string& path);
	

	/**
	 * @brief 파일 혹은 디렉토리가 유효한지 확인합니다.
	 *
	 * @param path 유효한지 확인할 파일 혹은 디렉토리 경로입니다.
	 *
	 * @return 파일 혹은 디렉토리가 유효하다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsValidPath(const std::wstring& path);


	/**
	 * @brief 경로에서 파일이나 디렉토리 이름을 제외한 경로를 얻습니다.
	 *
	 * @param path 파일이나 디렉토리 경로입니다.
	 *
	 * @return 파일이나 디렉토리 이름을 제외한 경로를 반환합니다.
	 *
	 * @example
	 * - 파일 경로가 "D:\\AAA\\BBB\\CCC.a"라면, 반환하는 값은 "D:\\AAA\\BBB\\" 입니다.
	 * - 디렉토리 경로가 "D:\\AAA\\BBB\\CCC"라면, 반환하는 값은 "D:\\AAA\\BBB\\" 입니다.
	 */
	std::string GetBasePath(const std::string& path);


	/**
	 * @brief 경로에서 파일이나 디렉토리 이름을 제외한 경로를 얻습니다.
	 *
	 * @param path 파일이나 디렉토리 경로입니다.
	 *
	 * @return 파일이나 디렉토리 이름을 제외한 경로를 반환합니다.
	 *
	 * @example
	 * - 파일 경로가 "D:\\AAA\\BBB\\CCC.a"라면, 반환하는 값은 "D:\\AAA\\BBB\\" 입니다.
	 * - 디렉토리 경로가 "D:\\AAA\\BBB\\CCC"라면, 반환하는 값은 "D:\\AAA\\BBB\\" 입니다.
	 */
	std::wstring GetBasePath(const std::wstring& path);


	/**
	 * @brief 전체 파일이나 디렉토리 경로에서 베이스 경로를 삭제합니다.
	 *
	 * @param path 베이스 경로를 삭제할 전체 파일이나 디렉토리 경로입니다.
	 *
	 * @return 베이스 경로가 삭제된 파일 경로를 반환합니다.
	 *
	 * @example
	 * - 파일 경로가 "D:\\AAA\\BBB\\CCC.a"라면, 반환하는 값은 "CCC.a" 입니다.
	 * - 디렉토리 경로가 "D:\\AAA\\BBB\\CCC"라면, 반환하는 값은 "CCC" 입니다.
	 */
	std::string RemoveBasePath(const std::string& path);


	/**
	 * @brief 전체 파일이나 디렉토리 경로에서 베이스 경로를 삭제합니다.
	 *
	 * @param path 베이스 경로를 삭제할 전체 파일이나 디렉토리 경로입니다.
	 *
	 * @return 베이스 경로가 삭제된 파일 경로를 반환합니다.
	 *
	 * @example
	 * - 파일 경로가 "D:\\AAA\\BBB\\CCC.a"라면, 반환하는 값은 "CCC.a" 입니다.
	 * - 디렉토리 경로가 "D:\\AAA\\BBB\\CCC"라면, 반환하는 값은 "CCC" 입니다.
	 */
	std::wstring RemoveBasePath(const std::wstring& path);


	/**
	 * @brief 전체 파일 경로에서 파일 확장자를 얻습니다.
	 *
	 * @param path 파일 확장자를 얻을 전체 파일 경로입니다.
	 *
	 * @return 전체 파일 경로의 파일 확장자를 반환합니다.
	 *
	 * @example
	 * - 파일 경로가 "D:\\AAA\\BBB\\CCC.a"라면, 반환하는 값은 "a" 입니다.
	 * - 파일 경로가 "D:/AAA/BBB/CCC.a"라면, 반환하는 값은 "a" 입니다.
	 */
	std::string GetFileExtension(const std::string& path);


	/**
	 * @brief 전체 파일 경로에서 파일 확장자를 얻습니다.
	 *
	 * @param path 파일 확장자를 얻을 전체 파일 경로입니다.
	 *
	 * @return 전체 파일 경로의 파일 확장자를 반환합니다.
	 *
	 * @example
	 * - 파일 경로가 "D:\\AAA\\BBB\\CCC.a"라면, 반환하는 값은 "a" 입니다.
	 * - 파일 경로가 "D:/AAA/BBB/CCC.a"라면, 반환하는 값은 "a" 입니다.
	 */
	std::wstring GetFileExtension(const std::wstring& path);


	/**
	 * @brief Json 파일의 Json 객체를 얻습니다.
	 * 
	 * @param path 파일의 경로입니다.
	 * 
	 * @return Json 객체를 반환합니다.
	 */
	Json::Value ReadJsonFromFile(const std::string& path);


	/**
	 * @brief Json 파일의 Json 객체를 얻습니다.
	 *
	 * @param path 파일의 경로입니다.
	 *
	 * @return Json 객체를 반환합니다.
	 */
	Json::Value ReadJsonFromFile(const std::wstring& path);


private:
	/**
	 * @brief 파일 및 디렉토리 처리를 수행하는 매니저에 디폴트 생성자와 빈 가상 소멸자를 삽입합니다.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(FileManager);


private:
	/**
	 * @brief 실행 파일 경로입니다.
	 */
	std::wstring executePath_;
};