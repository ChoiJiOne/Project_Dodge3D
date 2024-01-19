#pragma once

#include "UIPanel.h"


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
	 * @brief 플레이어의 정보를 표시하는 보드 UI 오브젝트를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;
};