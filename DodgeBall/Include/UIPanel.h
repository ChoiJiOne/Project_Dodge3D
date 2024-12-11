#pragma once

#include <string>

#include "IObject.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

class TTFont; // 트루 타입 폰트 리소스를 사용하기 위한 전방 선언입니다.


/**
 * @brief UI 패널 오브젝트입니다.
 * 
 * @note UI 패널 오브젝트의 좌표계는 윈도우 좌표계 기준입니다.
 */
class UIPanel : public IObject
{
public:
	/**
	 * @brief UI 패널 오브젝트의 생성 파라미터입니다.
	 */
	struct UIPanelConstructParam
	{
		float width;
		float height;
		Vector2f center;
		std::wstring text;
		TTFont* font;
		Vector4f outlineColor;
		Vector4f backgroundColor;
		Vector4f textColor;
	};


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
	 * @brief UI 패널 오브젝트를 초기화합니다.
	 * 
	 * @param uiConstructParam UI 패널 오브젝트를 초기화하기 위한 파라미터입니다.
	 */
	virtual void Initialize(const UIPanelConstructParam& uiConstructParam);


	/**
	 * @brief UI 패널 오브젝트를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief UI 패널 오브젝트를 화면에 그립니다.
	 */
	virtual void Render();


	/**
	 * @brief UI 패널 오브젝트 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


    /**
     * @brief UI 패널 오브젝트의 가로 크기를 반환합니다.
     *
     * @return UI 패널 오브젝트의 가로 크기입니다.
     */
    float GetWidth() { return width_; }


    /**
     * @brief UI 패널 오브젝트의 가로 크기를 반환합니다.
     *
     * @return UI 패널 오브젝트의 가로 크기입니다.
     */
    const float& GetWidth() const { return width_; }


    /**
     * @brief UI 패널 오브젝트의 세로 크기를 반환합니다.
     *
     * @return UI 패널 오브젝트의 세로 크기입니다.
     */
    float GetHeight() { return height_; }


    /**
     * @brief UI 패널 오브젝트의 세로 크기를 반환합니다.
     *
     * @return UI 패널 오브젝트의 세로 크기입니다.
     */
    const float& GetHeight() const { return height_; }


    /**
     * @brief UI 패널 오브젝트의 중심 좌표를 반환합니다.
     *
     * @return UI 패널 오브젝트의 중심 좌표입니다.
     */
    Vector2f GetCenter() { return center_; }


    /**
     * @brief UI 패널 오브젝트의 중심 좌표를 반환합니다.
     *
     * @return UI 패널 오브젝트의 중심 좌표입니다.
     */
    const Vector2f& GetCenter() const { return center_; }


    /**
     * @brief UI 패널 오브젝트에 표시된 텍스트를 반환합니다.
     *
     * @return UI 패널 오브젝트에 표시된 텍스트입니다.
     */
    std::wstring GetText() { return text_; }


    /**
     * @brief UI 패널 오브젝트에 표시된 텍스트를 반환합니다.
     *
     * @return UI 패널 오브젝트에 표시된 텍스트입니다.
     */
    const std::wstring& GetText() const { return text_; }


    /**
     * @brief UI 패널 오브젝트에 사용된 폰트를 반환합니다.
     *
     * @return UI 패널 오브젝트에 사용된 폰트입니다.
     */
    TTFont* GetFont() { return font_; }


    /**
     * @brief UI 패널 오브젝트에 사용된 폰트를 반환합니다.
     *
     * @return UI 패널 오브젝트에 사용된 폰트입니다.
     */
    const TTFont* GetFont() const { return font_; }


    /**
     * @brief UI 패널 오브젝트의 외곽선 색상을 반환합니다.
     *
     * @return UI 패널 오브젝트의 외곽선 색상입니다.
     */
    Vector4f GetOutlineColor() { return outlineColor_; }


    /**
     * @brief UI 패널 오브젝트의 외곽선 색상을 반환합니다.
     *
     * @return UI 패널 오브젝트의 외곽선 색상입니다.
     */
    const Vector4f& GetOutlineColor() const { return outlineColor_; }
	

    /**
     * @brief UI 패널 오브젝트의 배경 색상을 반환합니다.
     *
     * @return UI 패널 오브젝트의 배경 색상입니다.
     */
    Vector4f GetBackgroundColor() { return backgroundColor_; }


    /**
     * @brief UI 패널 오브젝트의 배경 색상을 반환합니다.
     *
     * @return UI 패널 오브젝트의 배경 색상입니다.
     */
    const Vector4f& GetBackgroundColor() const { return backgroundColor_; }


    /**
     * @brief UI 패널 오브젝트의 텍스트 색상을 반환합니다.
     *
     * @return UI 패널 오브젝트의 텍스트 색상입니다.
     */
    Vector4f GetTextColor() { return textColor_; }


    /**
     * @brief UI 패널 오브젝트의 텍스트 색상을 반환합니다.
     *
     * @return UI 패널 오브젝트의 텍스트 색상입니다.
     */
    const Vector4f& GetTextColor() const { return textColor_; }
    

    /**
     * @brief UI 패널 오브젝트의 가로 크기를 설정합니다.
     *
     * @param width UI 패널 오브젝트에 설정할 가로 크기입니다.
     */
    void SetWidth(float width) { width_ = width; }


    /**
     * @brief UI 패널 오브젝트의 세로 크기를 설정합니다.
     *
     * @param height UI 패널 오브젝트에 설정할 세로 크기입니다.
     */
    void SetHeight(float height) { height_ = height; }


    /**
     * @brief UI 패널 오브젝트의 중심 좌표를 설정합니다.
     *
     * @param center UI 패널 오브젝트에 설정할 중심 좌표입니다.
     */
    void SetCenter(const Vector2f& center) { center_ = center; }


    /**
     * @brief UI 패널 오브젝트에 표시할 텍스트를 설정합니다.
     *
     * @param text UI 패널 오브젝트에 설정할 텍스트입니다.
     */
    void SetText(const std::wstring& text) { text_ = text; }


    /**
     * @brief UI 패널 오브젝트에 사용할 폰트를 설정합니다.
     *
     * @param font UI 패널 오브젝트에 설정할 폰트입니다.
     */
    void SetFont(TTFont* font) { font_ = font; }


    /**
     * @brief UI 패널 오브젝트의 외곽선 색상을 설정합니다.
     *
     * @param outlineColor UI 패널 오브젝트에 설정할 외곽선 색상입니다.
     */
    void SetOutlineColor(const Vector4f& outlineColor) { outlineColor_ = outlineColor; }


    /**
     * @brief UI 패널 오브젝트의 배경 색상을 설정합니다.
     *
     * @param backgroundColor UI 패널 오브젝트에 설정할 배경 색상입니다.
     */
    void SetBackgroundColor(const Vector4f& backgroundColor) { backgroundColor_ = backgroundColor; }


    /**
     * @brief UI 패널 오브젝트의 텍스트 색상을 설정합니다.
     *
     * @param textColor UI 패널 오브젝트에 설정할 텍스트 색상입니다.
     */
    void SetTextColor(const Vector4f& textColor) { textColor_ = textColor; }
    

protected:
	/**
	 * @brief UI 패널 오브젝트의 가로 크기입니다.
	 */
	float width_;


	/**
	 * @brief UI 패널 오브젝트의 세로 크기입니다.
	 */
	float height_;


	/**
	 * @brief UI 패널 오브젝트의 중심 좌표입니다.
	 * 
	 * @note 이때, UI 패널 오브젝트의 좌표계는 윈도우 좌표계 기준입니다.
	 */
	Vector2f center_;


	/**
	 * @brief UI 패널 오브젝트에 표시할 텍스트입니다.
	 */
	std::wstring text_;


	/**
	 * @brief UI 패널 오브젝트에 표시할 텍스트의 폰트입니다.
	 */
	TTFont* font_;


	/**
	 * @brief UI 패널 오브젝트의 외곽선 색상입니다.
	 */
	Vector4f outlineColor_;


	/**
	 * @brief UI 패널 오브젝트의 백그라운드 색상입니다.
	 */
	Vector4f backgroundColor_;


	/**
	 * @brief UI 패널 오브젝트의 텍스트 색상입니다.
	 */
	Vector4f textColor_;
};