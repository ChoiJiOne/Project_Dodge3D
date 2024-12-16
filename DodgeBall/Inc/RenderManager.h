#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>
#include <windows.h>

#include "IManager.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"

class Camera3D;
class Window;
class Shader;
class Skybox;
class StaticMesh;
class Texture2D;
class TTFont;


/**
 * @brief ������ ó���� �����ϴ� �Ŵ����Դϴ�.
 * 
 * @note �� Ŭ������ �̱����Դϴ�.
 */
class RenderManager : public IManager
{
public:
	/**
	 * @brief ������ ó���� �����ϴ� �Ŵ����� ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(RenderManager);


	/**
	 * @brief ������ ó���� �����ϴ� �Ŵ����� ���� �ν��Ͻ��� ����ϴ�.
	 * 
	 * @return ������ ó���� �����ϴ� �Ŵ����� �����ڸ� ��ȯ�մϴ�.
	 */
	static RenderManager& Get()
	{
		static RenderManager instance;
		return instance;
	}


	/**
	 * @brief ������ ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 * 
	 * @note 
	 * - �� �޼��� ȣ�� ���� ������ ����� �Ǵ� ������ �����͸� �����ؾ� �մϴ�.
	 * - �� �޼���� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Startup() override;


	/**
	 * @brief ������ ó���� �����ϴ� �Ŵ����� ����� �����մϴ�.
	 * 
	 * @note
	 * - ���ø����̼� ���� ���� �� �޼��带 �ݵ�� ȣ���Ͽ� ���� ���ҽ��� �����ؾ� �մϴ�.
	 * - �� �޼���� �ݵ�� �� ���� ȣ��Ǿ�� �մϴ�.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief ������ ����� �Ǵ� �����츦 �����մϴ�.
	 * 
	 * @param window ������ ����� �Ǵ� �������Դϴ�.
	 */
	void SetRenderTargetWindow(Window* window) { renderTargetWindow_ = window; }


	/**
	 * @brief ������ ����� �Ǵ� �����츦 ����ϴ�.
	 * 
	 * @return ������ ����� �Ǵ� �������� �����͸� ��ȯ�մϴ�.
	 */
	Window* GetRenderTargetWindow() const { return renderTargetWindow_; }


	/**
	 * @brief ������ �������� �����մϴ�.
	 * 
	 * @param red ���� ������ R ���Դϴ�.
	 * @param green ���� ������ G ���Դϴ�.
	 * @param blue ���� ������ B ���Դϴ�.
	 * @param alpha ���� ������ A ���Դϴ�.
	 * @param depth ���� ������ �ʱ�ȭ ���Դϴ�.
	 * @param stencil ���ٽ� ������ �ʱ�ȭ ���Դϴ�.
	 */
	void BeginFrame(float red, float green, float blue, float alpha, float depth = 1.0f, uint8_t stencil = 0);


	/**
	 * @brief ����ۿ� ����Ʈ ���۸� �����մϴ�.
	 */
	void EndFrame();


	/**
	 * @brief �� ��Ʈ�� �����մϴ�.
	 * 
	 * @param x ����Ʈ �簢���� ���� �Ʒ� �𼭸�(�ȼ�)�Դϴ�. �⺻���� (0,0)�Դϴ�.
	 * @param y ����Ʈ �簢���� ���� �Ʒ� �𼭸�(�ȼ�)�Դϴ�. �⺻���� (0,0)�Դϴ�.
	 * @param width ����Ʈ�� �ʺ��Դϴ�. OpenGL ���ؽ�Ʈ�� â�� ó�� ����Ǹ� �ʺ� �� ���� �� �ش� â�� ũ��� �����˴ϴ�.
	 * @param height ����Ʈ�� �����Դϴ�. OpenGL ���ؽ�Ʈ�� â�� ó�� ����Ǹ� �ʺ� �� ���� �� �ش� â�� ũ��� �����˴ϴ�.
	 */
	void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);


	/**
	 * @brief ������ ����Ʈ�� �����մϴ�.
	 * 
	 * @note ������ ���� Ÿ�� ������ �����Դϴ�.
	 */
	void SetWindowViewport();


	/**
	 * @brief ���� ����ȭ �ɼ��� �����մϴ�.
	 * 
	 * @param bIsEnable ���� ����ȭ �ɼ��� Ȱ��ȭ�Ϸ��� true, ��Ȱ��ȭ�Ϸ��� false�Դϴ�.
	 */
	void SetVsyncMode(bool bIsEnable);


	/**
	 * @brief ���� �׽�Ʈ �ɼ��� �����մϴ�.
	 * 
	 * @param bIsEnable ���� �׽�Ʈ �ɼ��� Ȱ��ȭ�Ϸ��� true, ��Ȱ��ȭ�Ϸ��� false�Դϴ�.
	 */
	void SetDepthMode(bool bIsEnable);


	/**
	 * @brief ���ٽ� �׽�Ʈ �ɼ��� �����մϴ�.
	 * 
	 * @param bIsEnable ���ٽ� �׽�Ʈ �ɼ��� Ȱ��ȭ�Ϸ��� true, ��Ȱ��ȭ�Ϸ��� false�Դϴ�.
	 */
	void SetStencilMode(bool bIsEnable);


	/**
	 * @brief ���� ������ �ɼ��� �����մϴ�.
	 * 
	 * @param bIsEnable ���� ������ �ɼ��� Ȱ��ȭ�Ϸ��� true, ��Ȱ��ȭ�Ϸ��� false�Դϴ�.
	 */
	void SetAlphaBlendMode(bool bIsEnable);


	/**
	 * @brief ImGui ���̺귯�� Ȱ��ȭ ���θ� �����մϴ�.
	 *
	 * @param bIsEnable ImGui ���̺귯�� Ȱ��ȭ �����Դϴ�.
	 */
	void SetEnableImGui(bool bIsEnable) { bIsEnableImGui_ = bIsEnable; }


	/**
	 * @brief ������ ���̴� ��θ� �����մϴ�.
	 * 
	 * @param shaderPath ������ ���̴� ����Դϴ�.
	 */
	void SetShaderPath(const std::wstring& shaderPath) { shaderPath_ = shaderPath; }


	/**
	 * @brief ������ ũ�� ���� �� ���ο��� ������ ũ��� ���õ� ��Ҹ� ������Ʈ�մϴ�.
	 */
	void Resize();


	/**
	 * @brief ȭ�鿡 2D ������ �׸��ϴ�.
	 *
	 * @note 2D ������ ������ MAX_VERTEX_SIZE(10000)�� ũ�⸦ ���� �� �����ϴ�.
	 *
	 * @param positions ȭ�� ���� 2D �����Դϴ�.
	 * @param color ������ RGB �����Դϴ�.
	 * @param pointSize ���� ũ���Դϴ�. �⺻ ���� 1.0f�Դϴ�.
	 */
	void RenderPoints2D(const std::vector<Vector2f>& positions, const Vector4f& color, float pointSize = 1.0f);


	/**
	 * @brief ȭ�鿡 ������ ������ 2D ���� �׸��ϴ�.
	 *
	 * @note 2D ������ ������ MAX_VERTEX_SIZE(10000)�� ũ�⸦ ���� �� �����ϴ�.
	 *
	 * @param positions ȭ�� ���� 2D �����Դϴ�.
	 * @param color ������ RGB �����Դϴ�.
	 */
	void RenderConnectPoints2D(const std::vector<Vector2f>& positions, const Vector4f& color);


	/**
	 * @brief ȭ�鿡 2D ���� �׸��ϴ�.
	 *
	 * @param fromPosition ���� �������Դϴ�.
	 * @param toPosition ���� �����Դϴ�.
	 * @param color ���� RGBA�����Դϴ�.
	 */
	void RenderLine2D(const Vector2f& fromPosition, const Vector2f& toPosition, const Vector4f& color);


	/**
	 * @brief ȭ�鿡 2D ���� �׸��ϴ�.
	 *
	 * @param fromPosition ���� �������Դϴ�.
	 * @param fromColor ���� ������ �����Դϴ�.
	 * @param toPosition ���� �����Դϴ�.
	 * @param toColor ���� ���� �����Դϴ�.
	 */
	void RenderLine2D(const Vector2f& fromPosition, const Vector4f& fromColor, const Vector2f& toPosition, const Vector4f& toColor);


	/**
	 * @brief ȭ�鿡 2D �ﰢ���� �׸��ϴ�.
	 *
	 * @param fromPosition �ﰢ�� ���� ���Դϴ�.
	 * @param byPosition �ﰢ�� �߰� ���Դϴ�.
	 * @param toPosition �ﰢ�� �� ���Դϴ�.
	 * @param color �ﰢ���� RGBA�����Դϴ�.
	 */
	void RenderTriangle2D(const Vector2f& fromPosition, const Vector2f& byPosition, const Vector2f& toPosition, const Vector4f& color);


	/**
	 * @brief ȭ�鿡 2D �ﰢ���� �׸��ϴ�.
	 *
	 * @param ortho ���� ���� ����Դϴ�.
	 * @param fromPosition �ﰢ�� ���� ���Դϴ�.
	 * @param fromColor �ﰢ�� ���� ���� �����Դϴ�.
	 * @param byPosition �ﰢ�� �߰� ���Դϴ�.
	 * @param byColor �ﰢ�� �߰� ���� �����Դϴ�.
	 * @param toPosition �ﰢ�� �� ���Դϴ�.
	 * @param toColor �ﰢ�� �� ���� �����Դϴ�.
	 */
	void RenderTriangle2D(
		const Vector2f& fromPosition, const Vector4f& fromColor,
		const Vector2f& byPosition, const Vector4f& byColor,
		const Vector2f& toPosition, const Vector4f& toColor
	);


	/**
	 * @brief ȭ�鿡 2D ���̾� ������ �ﰢ���� �׸��ϴ�.
	 *
	 * @param ortho ���� ���� ����Դϴ�.
	 * @param fromPosition �ﰢ�� ���� ���Դϴ�.
	 * @param byPosition �ﰢ�� �߰� ���Դϴ�.
	 * @param toPosition �ﰢ�� �� ���Դϴ�.
	 * @param color �ﰢ���� RGBA�����Դϴ�.
	 */
	void RenderWireframeTriangle2D(const Vector2f& fromPosition, const Vector2f& byPosition, const Vector2f& toPosition, const Vector4f& color);


	/**
	 * @brief ȭ�鿡 2D ���̾� ������ �ﰢ���� �׸��ϴ�.
	 *
	 * @param ortho ���� ���� ����Դϴ�.
	 * @param fromPosition �ﰢ�� ���� ���Դϴ�.
	 * @param fromColor �ﰢ�� ���� ���� �����Դϴ�.
	 * @param byPosition �ﰢ�� �߰� ���Դϴ�.
	 * @param byColor �ﰢ�� �߰� ���� �����Դϴ�.
	 * @param toPosition �ﰢ�� �� ���Դϴ�.
	 * @param toColor �ﰢ�� �� ���� �����Դϴ�.
	 */
	void RenderWireframeTriangle2D(
		const Vector2f& fromPosition, const Vector4f& fromColor,
		const Vector2f& byPosition, const Vector4f& byColor,
		const Vector2f& toPosition, const Vector4f& toColor
	);


	/**
	 * @brief ȭ�鿡 2D ���簢���� �׸��ϴ�.
	 *
	 * @param ortho ���� ���� ����Դϴ�.
	 * @param center ���簢���� �߽� ��ǥ�Դϴ�.
	 * @param width ���簢���� ���� ũ���Դϴ�.
	 * @param heigt ���簢���� ���� ũ���Դϴ�.
	 * @param rotate ���簢���� ���� ȸ�� �����Դϴ�.
	 * @param color ���簢���� �����Դϴ�.
	 */
	void RenderRectangle2D(const Vector2f& center, float width, float height, float rotate, const Vector4f& color);


	/**
	 * @brief ȭ�鿡 2D ���̾� ������ ���簢���� �׸��ϴ�.
	 *
	 * @param center ���簢���� �߽� ��ǥ�Դϴ�.
	 * @param width ���簢���� ���� ũ���Դϴ�.
	 * @param heigt ���簢���� ���� ũ���Դϴ�.
	 * @param rotate ���簢���� ���� ȸ�� �����Դϴ�.
	 * @param color ���簢���� �����Դϴ�.
	 */
	void RenderWireframeRectangle2D(const Vector2f& center, float width, float height, float rotate, const Vector4f& color);


	/**
	 * @brief ȭ�鿡 2D ���� �׸��ϴ�.
	 *
	 * @param center ���� �߽� ��ǥ�Դϴ�.
	 * @param radius ���� ������ �����Դϴ�.
	 * @param color ���� �����Դϴ�.
	 * @param sliceCount ���� �ѷ� ���� Ƚ���Դϴ�. �⺻ ���� 300�Դϴ�.
	 */
	void RenderCircle2D(const Vector2f& center, float radius, const Vector4f& color, int32_t sliceCount = 300);


	/**
	 * @brief ȭ�鿡 2D ���̾� ������ ���� �׸��ϴ�.
	 *
	 * @param center ���� �߽� ��ǥ�Դϴ�.
	 * @param radius ���� ������ �����Դϴ�.
	 * @param color ���� �����Դϴ�.
	 * @param sliceCount �� �ѷ��� ���� Ƚ���Դϴ�. �⺻ ���� 300�Դϴ�.
	 */
	void RenderWireframeCircle2D(const Vector2f& center, float radius, const Vector4f& color, int32_t sliceCount = 300);


	/**
	 * @brief ȭ�鿡 2D Ÿ���� �׸��ϴ�.
	 *
	 * @param center Ÿ���� �߽� ��ǥ�Դϴ�.
	 * @param xAxis Ÿ���� x�� �����Դϴ�. ����, �� ���̰� y�� ���̺��� ũ�ٸ� ������ �ǰ�, �׷��� ������ ������ �˴ϴ�.
	 * @param yAxis Ÿ���� y�� �����Դϴ�. ����, �� ���̰� x�� ���̺��� ũ�ٸ� ������ �ǰ�, �׷��� ������ ������ �˴ϴ�.
	 * @param color Ÿ���� �����Դϴ�.
	 * @param sliceCount Ÿ�� �ѷ��� ���� Ƚ���Դϴ�. �⺻ ���� 300�Դϴ�.
	 */
	void RenderEllipse2D(const Vector2f& center, float xAxis, float yAxis, const Vector4f& color, int32_t sliceCount = 300);


	/**
	 * @brief ȭ�鿡 2D ���̾� ������ Ÿ���� �׸��ϴ�.
	 *
	 * @param center Ÿ���� �߽� ��ǥ�Դϴ�.
	 * @param xAxis Ÿ���� x�� �����Դϴ�. ����, �� ���̰� y�� ���̺��� ũ�ٸ� ������ �ǰ�, �׷��� ������ ������ �˴ϴ�.
	 * @param yAxis Ÿ���� y�� �����Դϴ�. ����, �� ���̰� x�� ���̺��� ũ�ٸ� ������ �ǰ�, �׷��� ������ ������ �˴ϴ�.
	 * @param color Ÿ���� �����Դϴ�.
	 * @param sliceCount Ÿ�� �ѷ��� ���� Ƚ���Դϴ�. �⺻ ���� 300�Դϴ�.
	 */
	void RenderWireframeEllipse2D(const Vector2f& center, float xAxis, float yAxis, const Vector4f& color, int32_t sliceCount = 300);


	/**
	 * @brief ȭ�鿡 2D �ؽ�ó�� �׸��ϴ�.
	 * 
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param center �ؽ�ó�� �߽� ��ǥ�Դϴ�.
	 * @param width �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param height �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param rotate �ؽ�ó�� ���� ȸ�� �����Դϴ�.
	 * @param transparent �ؽ�ó�� �������Դϴ�. �⺻ ���� 1.0f(������)�Դϴ�.
	 */
	void RenderTexture2D(
		const Texture2D* texture,
		const Vector2f& center,
		float width,
		float height,
		float rotate,
		float transparent = 1.0f
	);


	/**
	 * @brief ȭ�鿡 2D �ؽ�ó�� �׸��ϴ�.
	 *
	 * @note 2D �ؽ�ó�� ������ ��ü�� ä�������� �׸��ϴ�.
	 *
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param transparent �ؽ�ó�� �������Դϴ�. �⺻ ���� 1.0f(������)�Դϴ�.
	 */
	void RenderTexture2D(const Texture2D* texture, float transparent = 1.0f);


	/**
	 * @brief ���η� ��ũ�ѵ� 2D �ؽ�ó�� �׸��ϴ�.
	 *
	 * @note
	 * - 2D �ؽ�ó�� ������ ��ü�� ä�������� �׸��ϴ�.
	 * - �ؽ�ó ���� ������ ������ �����ϴ�.
	 * ������������������������������������������������������������������
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * �� 1.0f - rate��       rate       ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ������������������������������������������������������������������
	 *
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param rate ���� �����Դϴ�. ���� ������ 0.0f ~ 1.0f �Դϴ�.
	 * @param transparent �ؽ�ó�� �������Դϴ�. �⺻ ���� 1.0f(������)�Դϴ�.
	 */
	void RenderHorizonScrollTexture2D(const Texture2D* texture, float rate, float transparent = 1.0f);


	/**
	 * @brief ���η� ��ũ�ѵ� 2D �ؽ�ó�� �׸��ϴ�.
	 *
	 * @note
	 * - �ؽ�ó ���� ������ ������ �����ϴ�.
	 * ������������������������������������������������������������������
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * �� 1.0f - rate��       rate       ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ������������������������������������������������������������������
	 *
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param center �ؽ�ó�� �߽� ��ǥ�Դϴ�.
	 * @param width �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param height �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param rotate �ؽ�ó�� ȸ�� �����Դϴ�. ������ �����Դϴ�.
	 * @param rate ���� �����Դϴ�. ���� ������ 0.0f ~ 1.0f �Դϴ�.
	 * @param transparent �ؽ�ó�� �������Դϴ�. �⺻ ���� 1.0f(������)�Դϴ�.
	 */
	void RenderHorizonScrollTexture2D(
		const Texture2D* texture,
		const Vector2f& center,
		float width,
		float height,
		float rotate,
		float rate,
		float transparent = 1.0f
	);


	/**
	 * @brief ���η� ��ũ�ѵ� 2D �ؽ�ó�� �׸��ϴ�.
	 *
	 * @note
	 * - 2D �ؽ�ó�� ������ ��ü�� ä�������� �׸��ϴ�.
	 * - �ؽ�ó ���� ������ ������ �����ϴ�.
	 * ��������������������������������������������������������������
	 * ��                             ��
	 * ��                             ��
	 * ��              rate           ��
	 * ��                             ��
	 * ��������������������������������������������������������������
	 * ��                             ��
	 * ��          1.0f - rate        ��
	 * ��                             ��
	 * ��������������������������������������������������������������
	 *
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param rate ���� �����Դϴ�. ���� ������ 0.0f ~ 1.0f �Դϴ�.
	 * @param transparent �ؽ�ó�� �������Դϴ�. �⺻ ���� 1.0f(������)�Դϴ�.
	 */
	void RenderVerticalScrollTexture2D(const Texture2D* texture, float rate, float transparent = 1.0f);


	/**
	 * @brief ���η� ��ũ�ѵ� 2D �ؽ�ó�� �׸��ϴ�.
	 *
	 * @note
	 * - �ؽ�ó ���� ������ ������ �����ϴ�.
	 * ��������������������������������������������������������������
	 * ��                             ��
	 * ��                             ��
	 * ��              rate           ��
	 * ��                             ��
	 * ��������������������������������������������������������������
	 * ��                             ��
	 * ��          1.0f - rate        ��
	 * ��                             ��
	 * ��������������������������������������������������������������
	 * 
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param center �ؽ�ó�� �߽� ��ǥ�Դϴ�.
	 * @param width �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param height �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param rotate �ؽ�ó�� ȸ�� �����Դϴ�. ������ �����Դϴ�.
	 * @param rate ���� �����Դϴ�. ���� ������ 0.0f ~ 1.0f �Դϴ�.
	 * @param transparent �ؽ�ó�� �������Դϴ�. �⺻ ���� 1.0f(������)�Դϴ�.
	 */
	void RenderVerticalScrollTexture2D(
		const Texture2D* texture,
		const Vector2f& center,
		float width,
		float height,
		float rotate,
		float rate,
		float transparent = 1.0f
	);


	/**
	 * @brief 2D �ؽ�ó�� �ܰ����� ȭ�鿡 �׸��ϴ�.
	 *
	 * @param ortho ���� ���� ����Դϴ�.
	 * @param texture �ؽ�ó ���ҽ��Դϴ�.
	 * @param center �ؽ�ó�� �߽� ��ǥ�Դϴ�.
	 * @param width �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param height �ؽ�ó�� ���� ũ���Դϴ�.
	 * @param rotate �ؽ�ó�� ���� ȸ�� �����Դϴ�.
	 * @param silhouetteRGB �ؽ�ó �Ƿ翧�� �����Դϴ�.
	 * @param transparent �ؽ�ó�� �������Դϴ�. �⺻ ���� 1.0f �Դϴ�.
	 */
	void RenderOutlineTexture2D(
		const Texture2D* texture,
		const Vector2f& center,
		float width,
		float height,
		float rotate,
		const Vector4f& outline,
		float transparent = 1.0f
	);


	/**
	 * @brief ȭ�鿡 2D ���ڸ� �׸��ϴ�.
	 *
	 * @param minX X��ǥ�� �ּҰ��Դϴ�.
	 * @param maxX X��ǥ�� �ִ��Դϴ�.
	 * @param strideX ������ X�� ���������� �����Դϴ�.
	 * @param minY Y��ǥ�� �ּҰ��Դϴ�.
	 * @param maxY Y��ǥ�� �ִ��Դϴ�.
	 * @param strideY ������ Y�� ���������� �����Դϴ�.
	 * @param color ������ �����Դϴ�.
	 */
	void RenderGrid2D(float minX, float maxX, float strideX, float minY, float maxY, float strideY, const Vector4f& color);


	/**
	 * @brief 2D �ؽ�Ʈ�� ȭ�鿡 �׸��ϴ�.
	 *
	 * @param font ��Ʈ ���ҽ��Դϴ�.
	 * @param text �������� �ؽ�Ʈ�Դϴ�.
	 * @param center �ؽ�Ʈ�� �߽� ��ǥ�Դϴ�.
	 * @param color �ؽ�Ʈ�� RGBA �����Դϴ�.
	 */
	void RenderText2D(const TTFont* font, const std::wstring& text, const Vector2f& center, const Vector4f& color);


	/**
	 * @brief ī�޶� �������� 3D ������ �׸��ϴ�.
	 * 
	 * @param camera 3D ī�޶��Դϴ�.
	 * @param positions ȭ�� ���� 3D �����Դϴ�.
	 * @param color ������ �����Դϴ�.
	 * 
	 * @note 3D ������ ������ 10000���� ���� �� �����ϴ�.
	 */
	void RenderPoints3D(const Camera3D* camera, const std::vector<Vector3f>& positions, const Vector4f& color);


	/**
	 * @brief ī�޶� �������� ������ ������ 3D ���� �׸��ϴ�.
	 *
	 * @param camera 3D ī�޶��Դϴ�.
	 * @param positions ȭ�� ���� 3D �����Դϴ�.
	 * @param color ������ �����Դϴ�.
	 *
	 * @note 3D ������ ������ 10000���� ���� �� �����ϴ�.
	 */
	void RenderConnectPoints3D(const Camera3D* camera, const std::vector<Vector3f>& positions, const Vector4f& color);


	/**
	 * @brief ī�޶� �������� 3D ���� �׸��ϴ�.
	 *
	 * @param camera 3D ī�޶��Դϴ�.
	 * @param fromPosition ���� �������Դϴ�.
	 * @param toPosition ���� �����Դϴ�.
	 * @param color ���� �����Դϴ�.
	 */
	void RenderLine3D(const Camera3D* camera, const Vector3f& fromPosition, const Vector3f& toPosition, const Vector4f& color);


	/**
	 * @brief ī�޶� �������� 3D ���� ȭ�鿡 �׸��ϴ�.
	 *
	 * @param camera 3D ī�޶��Դϴ�.
	 * @param fromPosition ���� �������Դϴ�.
	 * @param fromColor ���� ������ �����Դϴ�.
	 * @param toPosition ���� �����Դϴ�.
	 * @param toColor ���� ���� �����Դϴ�.
	 */
	void RenderLine3D(const Camera3D* camera, const Vector3f& fromPosition, const Vector4f& fromColor, const Vector3f& toPosition, const Vector4f& toColor);


	/**
	 * @brief ī�޶� �������� 3D ���带 ȭ�鿡 �׸��ϴ�.
	 *
	 * @param world ���� ����Դϴ�.
	 * @param camera 3D ī�޶��Դϴ�.
	 * @param width ������ ���� ũ���Դϴ�.
	 * @param height ������ ���� ũ���Դϴ�.
	 * @param color ������ �����Դϴ�.
	 *
	 * @note 3D ����� XY ��� �����Դϴ�.
	 */
	void RenderQuad3D(const Matrix4x4f& world, const Camera3D* camera, float width, float height, const Vector4f& color);


	/**
	 * @brief ȭ�鿡 ���ҵ� 3D ���带 �׸��ϴ�.
	 *
	 * @param world ���� ����Դϴ�.
	 * @param camera 3D ī�޶��Դϴ�.
	 * @param width ������ ���� ũ���Դϴ�.
	 * @param height ������ ���� ũ���Դϴ�.
	 * @param rate ������ ���� �����Դϴ�. ���� ������ 0.0f ~ 1.0f�Դϴ�.
	 * @param color ������ rate ���� �κ��� �����Դϴ�.
	 * @param bgColor ������ 1.0f - rate ���� �κ��� �����Դϴ�.
	 *
	 * @note
	 * - 3D ����� XY ��� �����Դϴ�.
	 * - ���� �����Դϴ�.
	 * ������������������������������������������������������������������
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��    rate    ��   1.0f - rate    ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ��            ��                  ��
	 * ������������������������������������������������������������������
	 */
	void RenderHorizonDividQuad3D(const Matrix4x4f& world, const Camera3D* camera, float width, float height, float rate, const Vector4f& color, const Vector4f& bgColor);


	/**
	 * @brief ȭ�鿡 ���ҵ� 3D ���带 �׸��ϴ�.
	 *
	 * @param world ���� ����Դϴ�.
	 * @param view �þ� ����Դϴ�.
	 * @param projection ���� ����Դϴ�.
	 * @param width ������ ���� ũ���Դϴ�.
	 * @param height ������ ���� ũ���Դϴ�.
	 * @param rate ������ ���� �����Դϴ�. ���� ������ 0.0f ~ 1.0f�Դϴ�.
	 * @param color ������ rate ���� �κ��� �����Դϴ�.
	 * @param bgColor ������ 1.0f - rate ���� �κ��� �����Դϴ�.
	 *
	 * @note
	 * - 3D ����� XY ��� �����Դϴ�.
	 * - ���� �����Դϴ�.
	 * ��������������������������������������������������������������
	 * ��                             ��
	 * ��                             ��
	 * ��         1.0f - rate         ��
	 * ��                             ��
	 * ��������������������������������������������������������������
	 * ��                             ��
	 * ��            rate             ��
	 * ��                             ��
	 * ��������������������������������������������������������������
	 */
	void RenderVerticalDividQuad3D(const Matrix4x4f& world, const Camera3D* camera, float width, float height, float rate, const Vector4f& color, const Vector4f& bgColor);


	/**
	 * @brief ī�޶� �������� 3D �� ���� ��� ���ڸ� �׸��ϴ�.
	 * 
	 * @param camera 3D ī�޶��Դϴ�.
	 * @param center �� ��� ������ �߽� ��ǥ�Դϴ�.
	 * @param extents �� ��� ������ X/Y/Z �� ���������� ũ���Դϴ�.
	 * @param color ��� ������ �����Դϴ�.
	 */
	void RenderAxisAlignedBoundingBox3D(const Camera3D* camera, const Vector3f& center, const Vector3f& extents, const Vector4f& color);
	

	/**
	 * @brief ī�޶� �������� 3D ���̾� ������ ��(Sphere)�� �׸��ϴ�.
	 *
	 * @param camera 3D ī�޶��Դϴ�.
	 * @param center ���� �߽� ��ǥ�Դϴ�.
	 * @param radius ���� ������ �����Դϴ�.
	 * @param color ���� �����Դϴ�.
	 * @param sliceCount �� ��鿡 �����ϴ� ���� �ѷ� ���� Ƚ���Դϴ�. �⺻ ���� 300�Դϴ�.
	 */
	void RenderWireframeSphere3D(const Camera3D* camera, const Vector3f& center, float radius, const Vector4f& color, int32_t sliceCount = 300);


	/**
	 * @brief ī�޶� �������� 3D ��ǥ ������ �׸��ϴ�.
	 * 
	 * @param camera 3D ī�޶��Դϴ�.
	 * @param minX X��ǥ�� �ּҰ��Դϴ�.
	 * @param maxX X��ǥ�� �ִ��Դϴ�.
	 * @param strideX X�� ���������� �����Դϴ�.
	 * @param minZ Z��ǥ�� �ּҰ��Դϴ�.
	 * @param maxZ Z��ǥ�� �ִ��Դϴ�.
	 * @param strideZ Z�� ���������� �����Դϴ�.
	 * @param color ������ �����Դϴ�.
	 */
	void RenderGrid3D(const Camera3D* camera, float minX, float maxX, float strideX, float minZ, float maxZ, float strideZ, const Vector4f& color);


	/**
	 * @brief ī�޶� �������� ��ī�� �ڽ��� �׸��ϴ�.
	 * 
	 * @param camera 3D ī�޶��Դϴ�.
	 * @param skybox ȭ�鿡 �׸� ��ī�� �ڽ��Դϴ�.
	 */
	void RenderSkybox3D(const Camera3D* camera, const Skybox* skybox);

	
private:
	/**
	 * @brief ������ ó���� �����ϴ� �Ŵ����� ����Ʈ �����ڿ� �� ���� �Ҹ��ڸ� �����մϴ�.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(RenderManager);


private:
	/**
	 * @brief ������ ����� �Ǵ� ������ �������Դϴ�.
	 */
	Window* renderTargetWindow_ = nullptr;


	/**
	 * @brief IMGUI�� Ȱ��ȭ �Ǿ����� Ȯ���մϴ�.
	 */
	bool bIsEnableImGui_ = false;


	/**
	 * @brief ���� ����ȭ Ȱ��ȭ �����Դϴ�. �⺻ ���� ��Ȱ��ȭ�Դϴ�.
	 */
	bool bIsEnableVsync_ = false;


	/**
	 * @brief ���� �׽�Ʈ Ȱ��ȭ �����Դϴ�. �⺻ ���� Ȱ��ȭ�Դϴ�.
	 */
	bool bIsEnableDepth_ = true;


	/**
	 * @brief ���ٽ� �׽�Ʈ Ȱ��ȭ �����Դϴ�. �⺻ ���� ��Ȱ��ȭ�Դϴ�.
	 */
	bool bIsEnableStencil_ = false;


	/**
	 * @brief ���� ������ Ȱ��ȭ �����Դϴ�. �⺻ ���� Ȱ��ȭ�Դϴ�.
	 */
	bool bIsEnableAlphaBlend_ = true;


	/**
	 * @brief �������� ����� ����̽� ���ؽ�Ʈ�� �ڵ��Դϴ�.
	 */
	HDC deviceContext_ = nullptr;


	/**
	 * @brief �������� ����� OpenGL ���ؽ�Ʈ�� �ڵ��Դϴ�.
	 */
	HGLRC glRenderContext_ = nullptr;


	/**
	 * @brief ���̴� ���ҽ��� ����Դϴ�.
	 */
	std::wstring shaderPath_;

	
	/**
	 * @brief ���� �Ŵ������� ����� ���̴� ĳ���Դϴ�.
	 */
	std::unordered_map<std::wstring, Shader*> shaderCache_;


	/**
	 * @brief ���� ��ũ���� �����ϴ� ���� ���� ����Դϴ�.
	 */
	Matrix4x4f screenOrtho_;
};