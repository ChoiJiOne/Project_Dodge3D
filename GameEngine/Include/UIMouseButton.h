#pragma once

#include <functional>
#include <string>

#include "IObject.h"
#include "InputManager.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

class TTFont; // 트루 타입 폰트 리소스를 사용하기 위한 전방 선언입니다.


/**
 * @brief UI 마우스 버튼 오브젝트입니다.
 */
class UIMouseButton : public IObject
{
public:
    /**
     * @brief 마우스 버튼의 종류입니다.
     */
    enum class EType : int32_t
    {
        LButton = 0x01,
        RButton = 0x02,
    };


    /**
     * @brief 마우스 버튼의 상태입니다.
     */
    enum class EState : int32_t
    {
        Disabled = 0x00,
        Enabled = 0x01,
        Pressed = 0x02,
        Released = 0x03,
    };


	/**
	 * @brief UI 버튼 오브젝트의 생성 파라미터입니다.
	 */
	struct UIButtonConstructParam
	{
		float width;
		float height;
		Vector2f center;
		std::wstring text;
		TTFont* font;
		Vector4f outlineColor;
        Vector4f textColor;
		Vector4f disableColor;
		Vector4f enableColor;
		Vector4f pressColor;
		Vector4f releaseColor;
        EType type;
		std::function<void()> clickEvent;
	};


public:
	/**
	 * @brief UI 버튼 오브젝트의 디폴트 생성자입니다.
	 */
	UIMouseButton() = default;


	/**
	 * @brief UI 버튼 오브젝트의 가상 소멸자입니다.
	 */
	virtual ~UIMouseButton();


	/**
	 * @brief UI 버튼 오브젝트의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(UIMouseButton);


	/**
	 * @brief UI 버튼 오브젝트를 초기화합니다.
	 *
	 * @param uiConstructParam UI 버튼 오브젝트를 초기화하기 위한 파라미터입니다.
	 */
	virtual void Initialize(const UIButtonConstructParam& uiConstructParam);


	/**
	 * @brief UI 버튼 오브젝트를 업데이트합니다.
	 *
	 * @param deltaSeconds 델타 시간 값입니다.
	 */
	virtual void Tick(float deltaSeconds) override;


	/**
	 * @brief UI 버튼 오브젝트를 화면에 그립니다.
	 */
	virtual void Render();


	/**
	 * @brief UI 버튼 오브젝트 내의 리소스를 할당 해제합니다.
	 */
	virtual void Release() override;


    /**
     * @brief UI 버튼 오브젝트의 가로 크기를 반환합니다.
     *
     * @return UI 버튼 오브젝트의 가로 크기입니다.
     */
    float GetWidth() { return width_; }


    /**
	 * @brief UI 버튼 오브젝트의 가로 크기를 반환합니다.
	 *
	 * @return UI 버튼 오브젝트의 가로 크기입니다.
	 */
    const float& GetWidth() const { return width_; }


    /**
     * @brief UI 버튼 오브젝트의 세로 크기를 반환합니다.
     *
     * @return UI 버튼 오브젝트의 세로 크기입니다.
     */
    float GetHeight() { return height_; }


    /**
     * @brief UI 버튼 오브젝트의 세로 크기를 반환합니다.
     *
     * @return UI 버튼 오브젝트의 세로 크기입니다.
     */
    const float& GetHeight() const { return height_; }


    /**
     * @brief UI 버튼 오브젝트의 중심 좌표를 반환합니다.
     *
     * @return UI 버튼 오브젝트의 중심 좌표입니다.
     */
    Vector2f GetCenter() { return center_; }


    /**
     * @brief UI 버튼 오브젝트의 중심 좌표를 반환합니다.
     *
     * @return UI 버튼 오브젝트의 중심 좌표입니다.
     */
    const Vector2f& GetCenter() const { return center_; }


    /**
     * @brief UI 버튼 오브젝트에 표시된 텍스트를 반환합니다.
     *
     * @return UI 버튼 오브젝트에 표시된 텍스트입니다.
     */
    std::wstring GetText() { return text_; }


    /**
     * @brief UI 버튼 오브젝트에 표시된 텍스트를 반환합니다.
     *
     * @return UI 버튼 오브젝트에 표시된 텍스트입니다.
     */
    const std::wstring& GetText() const { return text_; }


    /**
     * @brief UI 버튼 오브젝트의 외곽선 색상을 반환합니다.
     *
     * @return UI 버튼 오브젝트의 외곽선 색상입니다.
     */
    Vector4f GetOutlineColor() { return outlineColor_; }


    /**
     * @brief UI 버튼 오브젝트의 외곽선 색상을 반환합니다.
     *
     * @return UI 버튼 오브젝트의 외곽선 색상입니다.
     */
    const Vector4f& GetOutlineColor() const { return outlineColor_; }


    /**
     * @brief UI 버튼 오브젝트의 비활성화 색상을 반환합니다.
     *
     * @return UI 버튼 오브젝트의 비활성화 색상입니다.
     */
    Vector4f GetDisableColor() { return disableColor_; }


    /**
     * @brief UI 버튼 오브젝트의 비활성화 색상을 반환합니다.
     *
     * @return UI 버튼 오브젝트의 비활성화 색상입니다.
     */
    const Vector4f& GetDisableColor() const { return disableColor_; }


    /**
     * @brief UI 버튼 오브젝트의 활성화 색상을 반환합니다.
     *
     * @return UI 버튼 오브젝트의 활성화 색상입니다.
     */
    Vector4f GetEnableColor() { return enableColor_; }


    /**
     * @brief UI 버튼 오브젝트의 활성화 색상을 반환합니다.
     *
     * @return UI 버튼 오브젝트의 활성화 색상입니다.
     */
    const Vector4f& GetEnableColor() const { return enableColor_; }


    /**
     * @brief UI 버튼을 눌렀을 때의 색상을 반환합니다.
     *
     * @return UI 버튼을 눌렀을 때의 색상입니다.
     */
    Vector4f GetPressColor() { return pressColor_; }


    /**
     * @brief UI 버튼을 눌렀을 때의 색상을 반환합니다.
     *
     * @return UI 버튼을 눌렀을 때의 색상입니다.
     */
    const Vector4f& GetPressColor() const { return pressColor_; }


    /**
     * @brief UI 버튼을 누르고 땠을 때의 색상을 반환합니다.
     *
     * @return UI 버튼을 누르고 땠을 때의 색상입니다.
     */
    Vector4f GetReleaseColor() { return releaseColor_; }


    /**
     * @brief UI 버튼을 누르고 땠을 때의 색상을 반환합니다.
     *
     * @return UI 버튼을 누르고 땠을 때의 색상입니다.
     */
    const Vector4f& GetReleaseColor() const { return releaseColor_; }


    /**
     * @brief UI 버튼 오브젝트의 가로 크기를 설정합니다.
     *
     * @param width UI 버튼 오브젝트에 설정할 가로 크기입니다.
     */
    void SetWidth(float width) { width_ = width; }


    /**
     * @brief UI 버튼 오브젝트의 세로 크기를 설정합니다.
     *
     * @param height UI 버튼 오브젝트에 설정할 세로 입니다.
     */
    void SetHeight(float height) { height_ = height; }


    /**
     * @brief UI 버튼 오브젝트의 중심 좌표를 설정합니다.
     *
     * @param center UI 버튼 오브젝트에 설정할 중심 좌표입니다.
     */
    void SetCenter(const Vector2f& center) { center_ = center; }


    /**
     * @brief UI 버튼 오브젝트에 표시할 텍스트를 설정합니다.
     *
     * @param text UI 버튼 오브젝트에 설정할 텍스트입니다.
     */
    void SetText(const std::wstring& text) { text_ = text; }


    /**
     * @brief UI 버튼 오브젝트의 외곽선 색상을 설정합니다.
     *
     * @param outlineColor UI 버튼 오브젝트에 설정할 외곽선 색상입니다.
     */
    void SetOutlineColor(const Vector4f& outlineColor) { outlineColor_ = outlineColor; }


    /**
     * @brief UI 버튼 오브젝트의 비활성화 색상을 설정합니다.
     *
     * @param disableColor UI 버튼 오브젝트에 설정할 비활성화 색상입니다.
     */
    void SetDisableColor(const Vector4f& disableColor) { disableColor_ = disableColor; }


    /**
     * @brief UI 버튼 오브젝트의 활성화 색상을 설정합니다.
     *
     * @param enableColor UI 버튼 오브젝트에 설정할 활성화 색상입니다.
     */
    void SetEnableColor(const Vector4f& enableColor) { enableColor_ = enableColor; }


    /**
     * @brief UI 버튼을 눌렀을 때의 색상을 설정합니다.
     *
     * @param pressColor UI 버튼에 설정할 눌렀을 때의 색상입니다.
     */
    void SetPressColor(const Vector4f& pressColor) { pressColor_ = pressColor; }


    /**
     * @brief UI 버튼을 누르고 땠을 때의 색상을 설정합니다.
     *
     * @param releaseColor UI 버튼에 설정할 누르고 땠을 때의 색상입니다.
     */
    void SetReleaseColor(const Vector4f& releaseColor) { releaseColor_ = releaseColor; }


private:
    /**
     * @brief 마우스 버튼의 상태를 얻습니다.
     * 
     * @param keyPressState 키 입력 상태입니다.
     * @param state 이전 버튼의 상태입니다.
     * 
     * @return 새롭게 업데이트된 버튼의 상태를 얻습니다.
     */
    EState GetMouseButtonState(const EPressState& keyPressState, const EState& state);


    /**
     * @brief 마우스가 UI 버튼 내에 있는지 확인합니다.
     * 
     * @return 마우스가 UI 버튼 내에 있다면 true, 그렇지 않으면 false를 반환합니다.
     */
    bool DetectMouseCursorInButton();


private:
	/**
	 * @brief UI 버튼 오브젝트의 가로 크기입니다.
	 */
	float width_;


	/**
	 * @brief UI 버튼 오브젝트의 세로 크기입니다.
	 */
	float height_;


	/**
	 * @brief UI 버튼 오브젝트의 중심 좌표입니다.
	 * 
	 * @note 이때, UI 패널 오브젝트의 좌표계는 윈도우 좌표계 기준입니다.
	 */
	Vector2f center_;


	/**
	 * @brief UI 버튼 오브젝트에 표시할 텍스트입니다.
	 */
	std::wstring text_;


	/**
	 * @brief UI 버튼 오브젝트에 표시할 텍스트의 폰트입니다.
	 */
	TTFont* font_;


	/**
	 * @brief UI 버튼 오브젝트의 외곽선 색상입니다.
	 */
	Vector4f outlineColor_;


    /**
     * @brief UI 버튼 텍스트의 색상입니다.
     */
    Vector4f textColor_;


	/**
	 * @brief UI 버튼 오브젝트의 비활성화 색상입니다.
	 */
	Vector4f disableColor_;


	/**
	 * @brief UI 버튼의 활성화 색상입니다.
	 */
	Vector4f enableColor_;


	/**
	 * @brief UI 버튼을 눌렀을 때의 색상입니다.
	 */
	Vector4f pressColor_;


	/**
	 * @brief UI 버튼을 누르고 땠을 때의 색상입니다.
	 */
	Vector4f releaseColor_;
    

	/**
	 * @brief UI 버튼의 가상 키 값입니다.
	 */
	EType type_ = EType::LButton;


	/**
	 * @brief UI 버튼을 클릭했을 때 실행할 이벤트입니다.
	 */
	std::function<void()> clickEvent_;


    /**
     * @brief 현재 마우스 버튼의 상태입니다.
     */
    EState state_ = EState::Disabled;
};