#pragma once

#include <string>

#include "UIObject.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

class TTFont; // 트루 타입 폰트 리소스를 사용하기 위한 전방 선언입니다.


/**
 * @brief UI 패널 오브젝트입니다.
 */
class UIPanel : public UIObject
{
public:
	/**
	 * @brief UI 패널 오브젝트의 디폴트 생성자입니다.
	 */
	UIPanel() = default;


	/**
	 * @brief UI 패널 오브젝트의 가상 소멸자입니다.
	 */
	virtual ~UIPanel();


	/**
	 * @brief UI 패널 오브젝트의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(UIPanel);


	/**
	 * @brief 2D 패널 UI 오브젝트를 초기화합니다.
	 *
	 * @param width 패널의 가로 크기입니다.
	 * @param height 패널의 세로 크기입니다.
	 * @param center 패널의 중심 좌표입니다.
	 * @param text 패널 내에 표시될 텍스트입니다.
	 * @param font 텍스트의 폰트입니다.
	 * @param outlineRGB 패널 외곽선의 색상입니다.
	 * @param backgroundRGB 패널 내의 백그라운드 색상입니다.
	 * @param textRGB 패널 내의 텍스트 색상입니다.
	 * @param transparent 패널의 투명도입니다. 이때, 투명도 값의 범위는 0.0에서 1.0입니다.
	 */
	virtual void Initialize(
		float width,
		float height,
		const Vector2f& center,
		const std::wstring& text,
		TTFont* font,
		const Vector3f& outlineRGB,
		const Vector3f& backgroundRGB,
		const Vector3f& textRGB,
		float transparent = 1.0f
	);


	/**
	 * @brief UI 패널 오브젝트를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief UI 패널 오브젝트를 화면에 그립니다.
	 */
	virtual void Render() override;


	/**
	 * @brief UI 패널 오브젝트 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


protected:
	/**
	 * @brief 패널의 가로 크기입니다.
	 */
	float width_ = 0.0f;


	/**
	 * @brief 패널의 세로 크기입니다.
	 */
	float height_ = 0.0f;


	/**
	 * @brief 패널의 중심 크기입니다.
	 */
	Vector2f center_;


	/**
	 * @brief 패널에 표시될 텍스트입니다.
	 */
	std::wstring text_;


	/**
	 * @brief 텍스트의 폰트입니다.
	 */
	TTFont* font_ = nullptr;


	/**
	 * @brief 패널의 외곽선 색상입니다.
	 */
	Vector3f outlineRGB_;


	/**
	 * @brief 패널 백그라운드의 색상입니다.
	 */
	Vector3f backgroundRGB_;


	/**
	 * @brief 텍스트의 색상입니다.
	 */
	Vector3f textRGB_;


	/**
	 * @brief 패널의 투명도입니다.
	 */
	float transparent_ = 1.0f;
};