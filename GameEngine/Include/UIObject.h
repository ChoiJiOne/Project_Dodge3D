#pragma once

#include "IObject.h"


/**
 * @brief UI 오브젝트입니다.
 */
class UIObject : public IObject
{
public:
	/**
	 * @brief UI 오브젝트의 디폴트 생성자입니다.
	 */
	UIObject() = default;


	/**
	 * @brief UI 오브젝트의 가상 소멸자입니다.
	 */
	virtual ~UIObject() {}


	/**
	 * @brief UI 오브젝트의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(UIObject);


	/**
	 * @brief UI를 화면에 그립니다.
	 */
	virtual void Render() = 0;
};