#pragma once

#include <string>
#include <vector>

#include "IObject.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

class TTFont; // 트루 타입 폰트 리소스를 사용하기 위한 전방 선언입니다.


/**
 * @brief 플레이 로그를 관리하는 오브젝트입니다.
 */
class PlayLogger : public IObject
{
public:
	/**
	 * @brief 플레이 로그를 관리하는 오브젝트의 기본 생성자입니다.
	 *
	 * @note 생성자 이외의 메서드에서 적절한 초기화를 수행해야 합니다.
	 */
	PlayLogger() = default;


	/**
	 * @brief 플레이 로그를 관리하는 오브젝트의 가상 소멸자입니다.
	 */
	virtual ~PlayLogger();


	/**
	 * @brief 플레이 로그를 관리하는 오브젝트의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(PlayLogger);


	/**
	 * @brief 플레이 로그를 관리하는 오브젝트를 초기화합니다.
	 */
	void Initialize();


	/**
	 * @brief 플레이 로그를 관리하는 오브젝트를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief 플레이 로그를 관리하는 오브젝트를 화면에 그립니다.
	 */
	void Render();


	/**
	 * @brief 플레이 로그를 관리하는 오브젝트 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


	/**
	 * @brief 플레이 로그를 기록합니다.
	 * 
	 * @param day 플레이 날짜입니다.
	 * @param time 플레이 시간입니다.
	 */
	void RecordPlayLog(const std::wstring& day, const float& time);


private:
	/**
	 * @brief 플레이 로그의 문자열 최대 길이입니다.
	 */
	static const int32_t MAX_LOG_SIZE = 40;


	/**
	 * @brief 플레이 로그입니다.
	 */
	struct PlayLog
	{
		std::wstring day;
		float time;
	};


	/**
	 * @brief 플레이 로그 청크입니다.
	 *
	 * @note 이 구조체는 파일을 읽고 쓸 때 사용합니다.
	 */
	struct PlayLogChunk
	{
		wchar_t day[MAX_LOG_SIZE];
		float time;
	};


	/**
	 * @brief 로그 파일을 읽습니다.
	 */
	void ReadLogFile();


	/**
	 * @brief 로그 파일을 씁니다.
	 */
	void WriteLogFile();


private:
	/**
	 * @brief 로그 파일 경로입니다.
	 */
	std::wstring logFilePath_;


	/**
	 * @brief 플레이 로거가 관리 중인 기록입니다.
	 */
	std::vector<PlayLog> playLog_;


	/**
	 * @brief 최근에 등록된 기록입니다.
	 */
	PlayLog recentPlayLog;


	/**
	 * @brief 플레이 로거가 표시할 텍스트의 폰트입니다.
	 */
	TTFont* font32_ = nullptr;


	/**
	 * @brief 플레이 로거가 표시할 텍스트의 폰트입니다.
	 */
	TTFont* font64_ = nullptr;


	/**
	 * @brief 랭크 타이틀 위치입니다.
	 */
	Vector2f rankCenter_;


	/**
	 * @brief 랭크 타이틀 색상입니다.
	 */
	Vector4f rankColor_;


	/**
	 * @brief 로그 시작 위치입니다.
	 */
	Vector2f logCenter_;


	/**
	 * @brief 로그 색상입니다.
	 */
	Vector4f logColor_;


	/**
	 * @brief 로그의 최근 색상입니다.
	 */
	Vector4f logRecentColor_;


	/**
	 * @brief 로그 간의 간격입니다.
	 */
	float logStride_ = 0.0f;


	/**
	 * @brief 화면에 표시할 최대 로그 수입니다.
	 */
	int32_t maxLogCount_ = 0;
};