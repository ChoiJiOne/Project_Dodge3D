#pragma once

#include "UIPanel.h"

class Player; // 플레이어 클래스의 전방 선언입니다.


/**
 * @brief 플레이어의 정보를 표시하는 보드 UI입니다.
 */
class UIBoard : public UIPanel
{
public:
	/**
	 * @brief 플레이어의 정보를 표시하는 보드 UI 오브젝트의 디폴트 생성자입니다.
	 */
	UIBoard() = default;


	/**
	 * @brief 플레이어의 정보를 표시하는 보드 UI 오브젝트의 가상 소멸자입니다.
	 */
	virtual ~UIBoard();


	/**
	 * @brief 플레이어의 정보를 표시하는 보드 UI 오브젝트의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(UIBoard);


	/**
	 * @brief 플레이어의 정보를 표시하는 보드 UI 오브젝트를 초기화합니다.
	 */
	void Initialize();


	/**
	 * @brief 플레이어의 정보를 표시하는 보드 UI 오브젝트를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


private:
	/**
	 * @brief 윈도우 크기로 부터 UI의 중심 위치를 얻습니다.
	 * 
	 * @return 계산된 UI 중심 위치를 얻습니다.
	 */
	Vector2f GetCenterFromWindow();
};