#pragma once

#include <cstdint>
#include <string>
#include <windows.h>

#include "Macro.h"


/**
 * @brief ������ ���ν����Դϴ�.
 */
typedef LRESULT(CALLBACK* WINDOWPROC)(HWND, uint32_t, WPARAM, LPARAM);


/**
 * @brief �����츦 �����ϰ� �����մϴ�.
 */
class Window
{
public:
	/**
	 * @brief ������ ������ ���� ����ü�Դϴ�.
	 */
	struct WindowConstructParam
	{
		std::wstring title;
		int32_t x;
		int32_t y;
		int32_t w;
		int32_t h;
		bool bIsResizable;
		bool bIsFullscreenMode;
	};


public:
	/**
	 * @brief �����츦 �����ϰ� �����ϴ� Ŭ������ ����Ʈ �������Դϴ�.
	 */
	Window() = default;


	/**
	 * @brief �����츦 �����ϰ� �����ϴ� Ŭ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Window();


	/**
	 * @brief �����츦 �����ϰ� �����ϴ� Ŭ������ ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Window);


	/**
	 * @brief �����츦 �����մϴ�.
	 * 
	 * @note Ǯ ��ũ�� ��� ���� �� �Ϻ� �ɼ��� ���õ˴ϴ�.
	 * 
	 * @param windowConstructParam ������ ���� �Ķ�����Դϴ�.
	 */
	void Create(const WindowConstructParam& windowConstructParam);


	/**
	 * @brief �����츦 �����մϴ�.
	 * 
	 * @note Ǯ ��ũ�� ��� ���� �� �Ϻ� �ɼ��� ���õ˴ϴ�.
	 * 
	 * @param title �������� Ÿ��Ʋ�Դϴ�.
	 * @param x ������ ��ġ�� X��ǥ�Դϴ�. 
	 * @param y ������ ��ġ�� Y��ǥ�Դϴ�. 
	 * @param w �������� ���� ũ���Դϴ�.
	 * @param h �������� ���� ũ���Դϴ�.
	 * @param bIsResizable �������� ũ�� ��ȯ �����Դϴ�.
	 * @param bIsFullscreenMode �����츦 Ǯ ��ũ�� ���� ������ �� �����Դϴ�.
	 */
	void Create(const std::wstring& title, int32_t x, int32_t y, int32_t w, int32_t h, bool bIsResizable, bool bIsFullscreenMode);


	/**
	 * @brief �����츦 �ı��մϴ�.
	 */
	void Destroy();

	
	/**
	 * @brief �����찡 Ǯ ��ũ��������� Ȯ���մϴ�.
	 * 
	 * @return �����찡 Ǯ ��ũ������� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsFullscreenMode() const { return bIsFullscreenMode_; }


	/**
	 * @brief �������� ũ�⸦ ������ �� �ִ��� Ȯ���մϴ�.
	 * 
	 * @return �������� ũ�⸦ ������ �� �ִٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsResizable() const { return bIsResizable_; }


	/**
	 * @brief �����찡 ǥ�õǾ� �ִ��� Ȯ���մϴ�.
	 * 
	 * @return �����찡 ǥ�õǾ� �ִٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool IsVisible() const { return IsWindowVisible(windowHandle_); }


	/**
	 * @brief ������ �ڵ��� ����ϴ�.
	 * 
	 * @return ������ �ڵ��� ��ȯ�մϴ�.
	 */
	HWND GetHandle() { return windowHandle_; }


	/**
	 * @brief �������� ũ�⸦ ����ϴ�.
	 * 
	 * @param outWidth �������� ���� ũ���Դϴ�.
	 * @param outHeight �������� ���� ũ���Դϴ�.
	 */
	void GetSize(int32_t& outWidth, int32_t& outHeight) const;


	/**
	 * @brief ������ ũ���� ����/���� ���� ����ϴ�.
	 * 
	 * @return ���� ������ ũ���� ����/���� ���� ��ȯ�մϴ�.
	 */
	float GetAspectSize() const;


	/**
	 * @brief �������� ���� ��� ��ġ�� ����ϴ�.
	 * 
	 * @param outPosX �������� ���� ��� X��ǥ�Դϴ�.
	 * @param outPosY �������� ���� ��� Y��ǥ�Դϴ�.
	 */
	void GetPosition(int32_t& outPosX, int32_t& outPosY);


	/**
	 * @brief ������ �������� �����մϴ�.
	 * 
	 * @param path ������ �������� ������ ������ �����Դϴ�.
	 */
	void SetIcon(const std::wstring& path);


	/**
	 * @brief ������ Ŭ������ ����մϴ�.
	 * 
	 * @note �� ���� �޼���� �� ���� ȣ���� �� �ֽ��ϴ�.
	 * 
	 * @param windowClassName ����� ������ Ŭ������ �̸��Դϴ�.
	 * @param windowProc ����� ������ Ŭ������ ���ν����Դϴ�.
	 */
	static void RegisterWindowClass(const std::wstring& windowClassName, WINDOWPROC windowProc);


	/**
	 * @brief ������ Ŭ������ ��� �����մϴ�.
	 */
	static void UnregisterWindowClass();


	/**
	 * @brief ������ Ŭ������ ����ߴ��� Ȯ���մϴ�.
	 * 
	 * @return ������ Ŭ������ ����ߴٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	static bool IsRegisterWindowClass() { return bIsRegisterWindowClass_; }
	

private:
	/**
	 * @brief ������ �ڵ��Դϴ�.
	 */
	HWND windowHandle_ = nullptr;


	/**
	 * @brief �������� ũ�⸦ �ٲ� �� �ִ��� Ȯ���մϴ�.
	 */
	bool bIsResizable_ = false;


	/**
	 * @brief Ǯ ��ũ�� ������� Ȯ���մϴ�.
	 */
	bool bIsFullscreenMode_ = false;


	/**
	 * @brief ������ �������Դϴ�.
	 */
	HICON icon_ = nullptr;
	

	/**
	 * @brief ������ Ŭ������ ����ߴ��� Ȯ���մϴ�.
	 */
	static bool bIsRegisterWindowClass_;


	/**
	 * @brief �ν��Ͻ��� ���� �ڵ��Դϴ�.
	 * 
	 * @note
	 * - �ν��Ͻ��� ���� �ڵ��� �޸𸮿� �ִ� ����� �⺻ �ּ��Դϴ�.
	 * - ���� : https://learn.microsoft.com/ko-kr/windows/win32/winprog/windows-data-types#:~:text=typedef%20HANDLE%20HICON%3B-,HINSTANCE,-instance%20%EB%8C%80%ED%95%9C%20%ED%95%B8%EB%93%A4%EC%9E%85%EB%8B%88%EB%8B%A4
	 */
	static HINSTANCE hInstance_;


	/**
	 * @brief ������ Ŭ������ �̸��Դϴ�.
	 * 
	 * @note 
	 * - ������ Ŭ������ ��Ÿ��, ������, Ŀ��, �޴� �� ������ ���ν����� ���� Ư���� �����մϴ�.
	 * - ���� : https://learn.microsoft.com/ko-kr/windows/win32/winmsg/about-window-classes#types-of-window-classes
	 */
	static std::wstring windowClassName_;
};