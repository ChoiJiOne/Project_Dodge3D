#pragma once

#include "IGameFramework.h"


/**
 * @brief 클라이언트 애플리케이션입니다.
 */
class ClientApplication : public IGameFramework
{
public:
	/**
	 * @brief 클라이언트 애플리케이션의 디폴트 생성자입니다.
	 */
	ClientApplication() = default;


	/**
	 * @brief 클라이언트 애플리케이션의 가상 소멸자입니다.
	 */
	virtual ~ClientApplication();


	/**
	 * @brief 클라이언트 애플리케이션의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(ClientApplication);


	/**
	 * @brief 게임 프레임워크를 초기화합니다.
	 */
	virtual void Setup() override;


	/**
	 * @brief 게임 프레임워크 사용을 종료합니다.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief 게임 프레임워크를 실행합니다.
	 */
	virtual void Run() override;


private:
	/**
	 * @brief 클라이언트 경로입니다.
	 */
	std::wstring clientPath_;


	/**
	 * @brief 게임 타이머입니다.
	 */
	GameTimer timer_;


	/**
	 * @brief 아래의 멤버 변수는 기능 구현을 위한 멤버 변수입니다.
	 */
	Matrix4x4f view_;
	Matrix4x4f projection_;
};