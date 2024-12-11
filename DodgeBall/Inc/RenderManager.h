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
 * @brief 렌더링 처리를 수행하는 매니저입니다.
 * 
 * @note 이 클래스는 싱글턴입니다.
 */
class RenderManager : public IManager
{
public:
	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(RenderManager);


	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 참조 인스턴스를 얻습니다.
	 * 
	 * @return 렌더링 처리를 수행하는 매니저의 참조자를 반환합니다.
	 */
	static RenderManager& Get()
	{
		static RenderManager instance;
		return instance;
	}


	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 사용을 시작합니다.
	 * 
	 * @note 
	 * - 이 메서드 호출 전에 렌더링 대상이 되는 윈도우 포인터를 설정해야 합니다.
	 * - 이 메서드는 한 번만 호출되어야 합니다.
	 */
	virtual void Startup() override;


	/**
	 * @brief 렌더링 처리를 수행하는 매니저의 사용을 종료합니다.
	 * 
	 * @note
	 * - 애플리케이션 종료 전에 이 메서드를 반드시 호출하여 내부 리소스를 정리해야 합니다.
	 * - 이 메서드는 반드시 한 번만 호출되어야 합니다.
	 */
	virtual void Shutdown() override;


	/**
	 * @brief 렌더링 대상이 되는 윈도우를 설정합니다.
	 * 
	 * @param window 렌더링 대상이 되는 윈도우입니다.
	 */
	void SetRenderTargetWindow(Window* window) { renderTargetWindow_ = window; }


	/**
	 * @brief 렌더링 대상이 되는 윈도우를 얻습니다.
	 * 
	 * @return 렌더링 대상이 되는 윈도우의 포인터를 반환합니다.
	 */
	Window* GetRenderTargetWindow() const { return renderTargetWindow_; }


	/**
	 * @brief 프레임 렌더링을 시작합니다.
	 * 
	 * @param red 색상 버퍼의 R 값입니다.
	 * @param green 색상 버퍼의 G 값입니다.
	 * @param blue 색상 버퍼의 B 값입니다.
	 * @param alpha 색상 버퍼의 A 값입니다.
	 * @param depth 깊이 버퍼의 초기화 값입니다.
	 * @param stencil 스텐실 버퍼의 초기화 값입니다.
	 */
	void BeginFrame(float red, float green, float blue, float alpha, float depth = 1.0f, uint8_t stencil = 0);


	/**
	 * @brief 백버퍼와 프론트 버퍼를 스왑합니다.
	 */
	void EndFrame();


	/**
	 * @brief 뷰 포트를 설정합니다.
	 * 
	 * @param x 뷰포트 사각형의 왼쪽 아래 모서리(픽셀)입니다. 기본값은 (0,0)입니다.
	 * @param y 뷰포트 사각형의 왼쪽 아래 모서리(픽셀)입니다. 기본값은 (0,0)입니다.
	 * @param width 뷰포트의 너비입니다. OpenGL 컨텍스트가 창에 처음 연결되면 너비 와 높이 가 해당 창의 크기로 설정됩니다.
	 * @param height 뷰포트의 높이입니다. OpenGL 컨텍스트가 창에 처음 연결되면 너비 와 높이 가 해당 창의 크기로 설정됩니다.
	 */
	void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);


	/**
	 * @brief 윈도우 뷰포트를 설정합니다.
	 * 
	 * @note 기준은 렌더 타켓 윈도우 기준입니다.
	 */
	void SetWindowViewport();


	/**
	 * @brief 수직 동기화 옵션을 설정합니다.
	 * 
	 * @param bIsEnable 수직 동기화 옵션을 활성화하려면 true, 비활성화하려면 false입니다.
	 */
	void SetVsyncMode(bool bIsEnable);


	/**
	 * @brief 깊이 테스트 옵션을 설정합니다.
	 * 
	 * @param bIsEnable 깊이 테스트 옵션을 활성화하려면 true, 비활성화하려면 false입니다.
	 */
	void SetDepthMode(bool bIsEnable);


	/**
	 * @brief 스텐실 테스트 옵션을 설정합니다.
	 * 
	 * @param bIsEnable 스텐실 테스트 옵션을 활성화하려면 true, 비활성화하려면 false입니다.
	 */
	void SetStencilMode(bool bIsEnable);


	/**
	 * @brief 알파 블랜딩 옵션을 설정합니다.
	 * 
	 * @param bIsEnable 알파 블랜딩 옵션을 활성화하려면 true, 비활성화하려면 false입니다.
	 */
	void SetAlphaBlendMode(bool bIsEnable);


	/**
	 * @brief ImGui 라이브러리 활성화 여부를 설정합니다.
	 *
	 * @param bIsEnable ImGui 라이브러리 활성화 여부입니다.
	 */
	void SetEnableImGui(bool bIsEnable) { bIsEnableImGui_ = bIsEnable; }


	/**
	 * @brief 엔진의 셰이더 경로를 설정합니다.
	 * 
	 * @param shaderPath 엔진의 셰이더 경로입니다.
	 */
	void SetShaderPath(const std::wstring& shaderPath) { shaderPath_ = shaderPath; }


	/**
	 * @brief 윈도우 크기 변경 시 내부에서 윈도우 크기와 관련된 요소를 업데이트합니다.
	 */
	void Resize();


	/**
	 * @brief 화면에 2D 점들을 그립니다.
	 *
	 * @note 2D 점들의 개수는 MAX_VERTEX_SIZE(10000)의 크기를 넘을 수 없습니다.
	 *
	 * @param positions 화면 상의 2D 점들입니다.
	 * @param color 점들의 RGB 색상입니다.
	 * @param pointSize 점의 크기입니다. 기본 값은 1.0f입니다.
	 */
	void RenderPoints2D(const std::vector<Vector2f>& positions, const Vector4f& color, float pointSize = 1.0f);


	/**
	 * @brief 화면에 점들을 연결한 2D 선을 그립니다.
	 *
	 * @note 2D 점들의 개수는 MAX_VERTEX_SIZE(10000)의 크기를 넘을 수 없습니다.
	 *
	 * @param positions 화면 상의 2D 점들입니다.
	 * @param color 점들의 RGB 색상입니다.
	 */
	void RenderConnectPoints2D(const std::vector<Vector2f>& positions, const Vector4f& color);


	/**
	 * @brief 화면에 2D 선을 그립니다.
	 *
	 * @param fromPosition 선의 시작점입니다.
	 * @param toPosition 선의 끝점입니다.
	 * @param color 선의 RGBA색상입니다.
	 */
	void RenderLine2D(const Vector2f& fromPosition, const Vector2f& toPosition, const Vector4f& color);


	/**
	 * @brief 화면에 2D 선을 그립니다.
	 *
	 * @param fromPosition 선의 시작점입니다.
	 * @param fromColor 선의 시작점 색상입니다.
	 * @param toPosition 선의 끝점입니다.
	 * @param toColor 선의 끝점 색상입니다.
	 */
	void RenderLine2D(const Vector2f& fromPosition, const Vector4f& fromColor, const Vector2f& toPosition, const Vector4f& toColor);


	/**
	 * @brief 화면에 2D 삼각형을 그립니다.
	 *
	 * @param fromPosition 삼각형 시작 점입니다.
	 * @param byPosition 삼각형 중간 점입니다.
	 * @param toPosition 삼각형 끝 점입니다.
	 * @param color 삼각형의 RGBA색상입니다.
	 */
	void RenderTriangle2D(const Vector2f& fromPosition, const Vector2f& byPosition, const Vector2f& toPosition, const Vector4f& color);


	/**
	 * @brief 화면에 2D 삼각형을 그립니다.
	 *
	 * @param ortho 직교 투영 행렬입니다.
	 * @param fromPosition 삼각형 시작 점입니다.
	 * @param fromColor 삼각형 시작 점의 색상입니다.
	 * @param byPosition 삼각형 중간 점입니다.
	 * @param byColor 삼각형 중간 점의 색상입니다.
	 * @param toPosition 삼각형 끝 점입니다.
	 * @param toColor 삼각형 끝 점의 색상입니다.
	 */
	void RenderTriangle2D(
		const Vector2f& fromPosition, const Vector4f& fromColor,
		const Vector2f& byPosition, const Vector4f& byColor,
		const Vector2f& toPosition, const Vector4f& toColor
	);


	/**
	 * @brief 화면에 2D 와이어 프레임 삼각형을 그립니다.
	 *
	 * @param ortho 직교 투영 행렬입니다.
	 * @param fromPosition 삼각형 시작 점입니다.
	 * @param byPosition 삼각형 중간 점입니다.
	 * @param toPosition 삼각형 끝 점입니다.
	 * @param color 삼각형의 RGBA색상입니다.
	 */
	void RenderWireframeTriangle2D(const Vector2f& fromPosition, const Vector2f& byPosition, const Vector2f& toPosition, const Vector4f& color);


	/**
	 * @brief 화면에 2D 와이어 프레임 삼각형을 그립니다.
	 *
	 * @param ortho 직교 투영 행렬입니다.
	 * @param fromPosition 삼각형 시작 점입니다.
	 * @param fromColor 삼각형 시작 점의 색상입니다.
	 * @param byPosition 삼각형 중간 점입니다.
	 * @param byColor 삼각형 중간 점의 색상입니다.
	 * @param toPosition 삼각형 끝 점입니다.
	 * @param toColor 삼각형 끝 점의 색상입니다.
	 */
	void RenderWireframeTriangle2D(
		const Vector2f& fromPosition, const Vector4f& fromColor,
		const Vector2f& byPosition, const Vector4f& byColor,
		const Vector2f& toPosition, const Vector4f& toColor
	);


	/**
	 * @brief 화면에 2D 직사각형을 그립니다.
	 *
	 * @param ortho 직교 투영 행렬입니다.
	 * @param center 직사각형의 중심 좌표입니다.
	 * @param width 직사각형의 가로 크기입니다.
	 * @param heigt 직사각형의 세로 크기입니다.
	 * @param rotate 직사각형의 라디안 회전 각도입니다.
	 * @param color 직사각형의 색상입니다.
	 */
	void RenderRectangle2D(const Vector2f& center, float width, float height, float rotate, const Vector4f& color);


	/**
	 * @brief 화면에 2D 와이어 프레임 직사각형을 그립니다.
	 *
	 * @param center 직사각형의 중심 좌표입니다.
	 * @param width 직사각형의 가로 크기입니다.
	 * @param heigt 직사각형의 세로 크기입니다.
	 * @param rotate 직사각형의 라디안 회전 각도입니다.
	 * @param color 직사각형의 색상입니다.
	 */
	void RenderWireframeRectangle2D(const Vector2f& center, float width, float height, float rotate, const Vector4f& color);


	/**
	 * @brief 화면에 2D 원을 그립니다.
	 *
	 * @param center 원의 중심 좌표입니다.
	 * @param radius 원의 반지름 길이입니다.
	 * @param color 원의 색상입니다.
	 * @param sliceCount 원의 둘레 절단 횟수입니다. 기본 값은 300입니다.
	 */
	void RenderCircle2D(const Vector2f& center, float radius, const Vector4f& color, int32_t sliceCount = 300);


	/**
	 * @brief 화면에 2D 와이어 프레임 원을 그립니다.
	 *
	 * @param center 원의 중심 좌표입니다.
	 * @param radius 원의 반지름 길이입니다.
	 * @param color 원의 색상입니다.
	 * @param sliceCount 원 둘레의 절단 횟수입니다. 기본 값은 300입니다.
	 */
	void RenderWireframeCircle2D(const Vector2f& center, float radius, const Vector4f& color, int32_t sliceCount = 300);


	/**
	 * @brief 화면에 2D 타원을 그립니다.
	 *
	 * @param center 타원의 중심 좌표입니다.
	 * @param xAxis 타원의 x축 길이입니다. 만약, 이 길이가 y축 길이보다 크다면 장축이 되고, 그렇지 않으면 단축이 됩니다.
	 * @param yAxis 타원의 y축 길이입니다. 만약, 이 길이가 x축 길이보다 크다면 장축이 되고, 그렇지 않으면 단축이 됩니다.
	 * @param color 타원의 색상입니다.
	 * @param sliceCount 타원 둘레의 절단 횟수입니다. 기본 값은 300입니다.
	 */
	void RenderEllipse2D(const Vector2f& center, float xAxis, float yAxis, const Vector4f& color, int32_t sliceCount = 300);


	/**
	 * @brief 화면에 2D 와이어 프레임 타원을 그립니다.
	 *
	 * @param center 타원의 중심 좌표입니다.
	 * @param xAxis 타원의 x축 길이입니다. 만약, 이 길이가 y축 길이보다 크다면 장축이 되고, 그렇지 않으면 단축이 됩니다.
	 * @param yAxis 타원의 y축 길이입니다. 만약, 이 길이가 x축 길이보다 크다면 장축이 되고, 그렇지 않으면 단축이 됩니다.
	 * @param color 타원의 색상입니다.
	 * @param sliceCount 타원 둘레의 절단 횟수입니다. 기본 값은 300입니다.
	 */
	void RenderWireframeEllipse2D(const Vector2f& center, float xAxis, float yAxis, const Vector4f& color, int32_t sliceCount = 300);


	/**
	 * @brief 화면에 2D 텍스처를 그립니다.
	 * 
	 * @param texture 텍스처 리소스입니다.
	 * @param center 텍스처의 중심 좌표입니다.
	 * @param width 텍스처의 가로 크기입니다.
	 * @param height 텍스처의 세로 크기입니다.
	 * @param rotate 텍스처의 라디안 회전 각도입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
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
	 * @brief 화면에 2D 텍스처를 그립니다.
	 *
	 * @note 2D 텍스처를 윈도우 전체에 채워지도록 그립니다.
	 *
	 * @param texture 텍스처 리소스입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void RenderTexture2D(const Texture2D* texture, float transparent = 1.0f);


	/**
	 * @brief 가로로 스크롤된 2D 텍스처를 그립니다.
	 *
	 * @note
	 * - 2D 텍스처를 윈도우 전체에 채워지도록 그립니다.
	 * - 텍스처 분할 비율은 다음과 같습니다.
	 * ┌────────────┬──────────────────┐
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * │ 1.0f - rate│       rate       │
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * └────────────┴──────────────────┘
	 *
	 * @param texture 텍스처 리소스입니다.
	 * @param rate 분할 비율입니다. 값의 범위는 0.0f ~ 1.0f 입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void RenderHorizonScrollTexture2D(const Texture2D* texture, float rate, float transparent = 1.0f);


	/**
	 * @brief 가로로 스크롤된 2D 텍스처를 그립니다.
	 *
	 * @note
	 * - 텍스처 분할 비율은 다음과 같습니다.
	 * ┌────────────┬──────────────────┐
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * │ 1.0f - rate│       rate       │
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * └────────────┴──────────────────┘
	 *
	 * @param texture 텍스처 리소스입니다.
	 * @param center 텍스처의 중심 좌표입니다.
	 * @param width 텍스처의 가로 크기입니다.
	 * @param height 텍스처의 세로 크기입니다.
	 * @param rotate 텍스처의 회전 각도입니다. 단위는 라디안입니다.
	 * @param rate 분할 비율입니다. 값의 범위는 0.0f ~ 1.0f 입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
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
	 * @brief 세로로 스크롤된 2D 텍스처를 그립니다.
	 *
	 * @note
	 * - 2D 텍스처를 윈도우 전체에 채워지도록 그립니다.
	 * - 텍스처 분할 비율은 다음과 같습니다.
	 * ┌─────────────────────────────┐
	 * │                             │
	 * │                             │
	 * │              rate           │
	 * │                             │
	 * ├─────────────────────────────┤
	 * │                             │
	 * │          1.0f - rate        │
	 * │                             │
	 * └─────────────────────────────┘
	 *
	 * @param texture 텍스처 리소스입니다.
	 * @param rate 분할 비율입니다. 값의 범위는 0.0f ~ 1.0f 입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
	 */
	void RenderVerticalScrollTexture2D(const Texture2D* texture, float rate, float transparent = 1.0f);


	/**
	 * @brief 세로로 스크롤된 2D 텍스처를 그립니다.
	 *
	 * @note
	 * - 텍스처 분할 비율은 다음과 같습니다.
	 * ┌─────────────────────────────┐
	 * │                             │
	 * │                             │
	 * │              rate           │
	 * │                             │
	 * ├─────────────────────────────┤
	 * │                             │
	 * │          1.0f - rate        │
	 * │                             │
	 * └─────────────────────────────┘
	 * 
	 * @param texture 텍스처 리소스입니다.
	 * @param center 텍스처의 중심 좌표입니다.
	 * @param width 텍스처의 가로 크기입니다.
	 * @param height 텍스처의 세로 크기입니다.
	 * @param rotate 텍스처의 회전 각도입니다. 단위는 라디안입니다.
	 * @param rate 분할 비율입니다. 값의 범위는 0.0f ~ 1.0f 입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f(불투명)입니다.
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
	 * @brief 2D 텍스처의 외곽선을 화면에 그립니다.
	 *
	 * @param ortho 직교 투영 행렬입니다.
	 * @param texture 텍스처 리소스입니다.
	 * @param center 텍스처의 중심 좌표입니다.
	 * @param width 텍스처의 가로 크기입니다.
	 * @param height 텍스처의 세로 크기입니다.
	 * @param rotate 텍스처의 라디안 회전 각도입니다.
	 * @param silhouetteRGB 텍스처 실루엣의 색상입니다.
	 * @param transparent 텍스처의 투명도입니다. 기본 값은 1.0f 입니다.
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
	 * @brief 화면에 2D 격자를 그립니다.
	 *
	 * @param minX X좌표의 최소값입니다.
	 * @param maxX X좌표의 최댓값입니다.
	 * @param strideX 격차의 X축 방향으로의 간격입니다.
	 * @param minY Y좌표의 최소값입니다.
	 * @param maxY Y좌표의 최댓값입니다.
	 * @param strideY 격차의 Y축 방향으로의 간격입니다.
	 * @param color 격자의 색상입니다.
	 */
	void RenderGrid2D(float minX, float maxX, float strideX, float minY, float maxY, float strideY, const Vector4f& color);


	/**
	 * @brief 2D 텍스트를 화면에 그립니다.
	 *
	 * @param font 폰트 리소스입니다.
	 * @param text 렌더링할 텍스트입니다.
	 * @param center 텍스트의 중심 좌표입니다.
	 * @param color 텍스트의 RGBA 색상입니다.
	 */
	void RenderText2D(const TTFont* font, const std::wstring& text, const Vector2f& center, const Vector4f& color);


	/**
	 * @brief 카메라를 기준으로 3D 점들을 그립니다.
	 * 
	 * @param camera 3D 카메라입니다.
	 * @param positions 화면 상의 3D 점들입니다.
	 * @param color 점들의 색상입니다.
	 * 
	 * @note 3D 점들의 개수는 10000개를 넘을 수 없습니다.
	 */
	void RenderPoints3D(const Camera3D* camera, const std::vector<Vector3f>& positions, const Vector4f& color);


	/**
	 * @brief 카메라를 기준으로 점들을 연결한 3D 선을 그립니다.
	 *
	 * @param camera 3D 카메라입니다.
	 * @param positions 화면 상의 3D 점들입니다.
	 * @param color 점들의 색상입니다.
	 *
	 * @note 3D 점들의 개수는 10000개를 넘을 수 없습니다.
	 */
	void RenderConnectPoints3D(const Camera3D* camera, const std::vector<Vector3f>& positions, const Vector4f& color);


	/**
	 * @brief 카메라를 기준으로 3D 선을 그립니다.
	 *
	 * @param camera 3D 카메라입니다.
	 * @param fromPosition 선의 시작점입니다.
	 * @param toPosition 선의 끝점입니다.
	 * @param color 선의 색상입니다.
	 */
	void RenderLine3D(const Camera3D* camera, const Vector3f& fromPosition, const Vector3f& toPosition, const Vector4f& color);


	/**
	 * @brief 카메라를 기준으로 3D 선을 화면에 그립니다.
	 *
	 * @param camera 3D 카메라입니다.
	 * @param fromPosition 선의 시작점입니다.
	 * @param fromColor 선의 시작점 색상입니다.
	 * @param toPosition 선의 끝점입니다.
	 * @param toColor 선의 끝점 색상입니다.
	 */
	void RenderLine3D(const Camera3D* camera, const Vector3f& fromPosition, const Vector4f& fromColor, const Vector3f& toPosition, const Vector4f& toColor);


	/**
	 * @brief 카메라를 기준으로 3D 쿼드를 화면에 그립니다.
	 *
	 * @param world 월드 행렬입니다.
	 * @param camera 3D 카메라입니다.
	 * @param width 쿼드의 가로 크기입니다.
	 * @param height 쿼드의 세로 크기입니다.
	 * @param color 쿼드의 색상입니다.
	 *
	 * @note 3D 쿼드는 XY 평면 기준입니다.
	 */
	void RenderQuad3D(const Matrix4x4f& world, const Camera3D* camera, float width, float height, const Vector4f& color);


	/**
	 * @brief 화면에 분할된 3D 쿼드를 그립니다.
	 *
	 * @param world 월드 행렬입니다.
	 * @param camera 3D 카메라입니다.
	 * @param width 쿼드의 가로 크기입니다.
	 * @param height 쿼드의 세로 크기입니다.
	 * @param rate 쿼드의 분할 비율입니다. 값의 범위는 0.0f ~ 1.0f입니다.
	 * @param color 쿼드의 rate 비율 부분의 색상입니다.
	 * @param bgColor 쿼드의 1.0f - rate 비율 부분의 색상입니다.
	 *
	 * @note
	 * - 3D 쿼드는 XY 평면 기준입니다.
	 * - 분할 기준입니다.
	 * ┌────────────┬──────────────────┐
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * │    rate    │   1.0f - rate    │
	 * │            │                  │
	 * │            │                  │
	 * │            │                  │
	 * └────────────┴──────────────────┘
	 */
	void RenderHorizonDividQuad3D(const Matrix4x4f& world, const Camera3D* camera, float width, float height, float rate, const Vector4f& color, const Vector4f& bgColor);


	/**
	 * @brief 화면에 분할된 3D 쿼드를 그립니다.
	 *
	 * @param world 월드 행렬입니다.
	 * @param view 시야 행렬입니다.
	 * @param projection 투영 행렬입니다.
	 * @param width 쿼드의 가로 크기입니다.
	 * @param height 쿼드의 세로 크기입니다.
	 * @param rate 쿼드의 분할 비율입니다. 값의 범위는 0.0f ~ 1.0f입니다.
	 * @param color 쿼드의 rate 비율 부분의 색상입니다.
	 * @param bgColor 쿼드의 1.0f - rate 비율 부분의 색상입니다.
	 *
	 * @note
	 * - 3D 쿼드는 XY 평면 기준입니다.
	 * - 분할 기준입니다.
	 * ┌─────────────────────────────┐
	 * │                             │
	 * │                             │
	 * │         1.0f - rate         │
	 * │                             │
	 * ├─────────────────────────────┤
	 * │                             │
	 * │            rate             │
	 * │                             │
	 * └─────────────────────────────┘
	 */
	void RenderVerticalDividQuad3D(const Matrix4x4f& world, const Camera3D* camera, float width, float height, float rate, const Vector4f& color, const Vector4f& bgColor);


	/**
	 * @brief 카메라를 기준으로 3D 축 정렬 경계 상자를 그립니다.
	 * 
	 * @param camera 3D 카메라입니다.
	 * @param center 축 경계 상자의 중심 좌표입니다.
	 * @param extents 축 경계 상자의 X/Y/Z 축 방향으로의 크기입니다.
	 * @param color 경계 상자의 색상입니다.
	 */
	void RenderAxisAlignedBoundingBox3D(const Camera3D* camera, const Vector3f& center, const Vector3f& extents, const Vector4f& color);
	

	/**
	 * @brief 카메라를 기준으로 3D 와이어 프레임 구(Sphere)를 그립니다.
	 *
	 * @param camera 3D 카메라입니다.
	 * @param center 구의 중심 좌표입니다.
	 * @param radius 구의 반지름 길이입니다.
	 * @param color 구의 색상입니다.
	 * @param sliceCount 각 평면에 평행하는 원의 둘레 절단 횟수입니다. 기본 값은 300입니다.
	 */
	void RenderWireframeSphere3D(const Camera3D* camera, const Vector3f& center, float radius, const Vector4f& color, int32_t sliceCount = 300);


	/**
	 * @brief 카메라를 기준으로 3D 좌표 공간을 그립니다.
	 * 
	 * @param camera 3D 카메라입니다.
	 * @param minX X좌표의 최소값입니다.
	 * @param maxX X좌표의 최댓값입니다.
	 * @param strideX X축 방향으로의 간격입니다.
	 * @param minZ Z좌표의 최소값입니다.
	 * @param maxZ Z좌표의 최댓값입니다.
	 * @param strideZ Z축 방향으로의 간격입니다.
	 * @param color 격자의 색상입니다.
	 */
	void RenderGrid3D(const Camera3D* camera, float minX, float maxX, float strideX, float minZ, float maxZ, float strideZ, const Vector4f& color);


	/**
	 * @brief 카메라를 기준으로 스카이 박스를 그립니다.
	 * 
	 * @param camera 3D 카메라입니다.
	 * @param skybox 화면에 그릴 스카이 박스입니다.
	 */
	void RenderSkybox3D(const Camera3D* camera, const Skybox* skybox);

	
private:
	/**
	 * @brief 렌더링 처리를 수행하는 매니저에 디폴트 생성자와 빈 가상 소멸자를 삽입합니다.
	 */
	DEFAULT_CONSTRUCTOR_AND_VIRTUAL_DESTRUCTOR(RenderManager);


private:
	/**
	 * @brief 렌더링 대상이 되는 윈도우 포인터입니다.
	 */
	Window* renderTargetWindow_ = nullptr;


	/**
	 * @brief IMGUI가 활성화 되었는지 확인합니다.
	 */
	bool bIsEnableImGui_ = false;


	/**
	 * @brief 수직 동기화 활성화 여부입니다. 기본 값은 비활성화입니다.
	 */
	bool bIsEnableVsync_ = false;


	/**
	 * @brief 깊이 테스트 활성화 여부입니다. 기본 값은 활성화입니다.
	 */
	bool bIsEnableDepth_ = true;


	/**
	 * @brief 스텐실 테스트 활성화 여부입니다. 기본 값은 비활성화입니다.
	 */
	bool bIsEnableStencil_ = false;


	/**
	 * @brief 알파 블랜딩 활성화 여부입니다. 기본 값은 활성화입니다.
	 */
	bool bIsEnableAlphaBlend_ = true;


	/**
	 * @brief 렌더링이 수행될 디바이스 컨텍스트의 핸들입니다.
	 */
	HDC deviceContext_ = nullptr;


	/**
	 * @brief 렌더링이 수행될 OpenGL 컨텍스트의 핸들입니다.
	 */
	HGLRC glRenderContext_ = nullptr;


	/**
	 * @brief 셰이더 리소스의 경로입니다.
	 */
	std::wstring shaderPath_;

	
	/**
	 * @brief 렌더 매니저에서 사용할 셰이더 캐시입니다.
	 */
	std::unordered_map<std::wstring, Shader*> shaderCache_;


	/**
	 * @brief 현재 스크린에 대응하는 직교 투영 행렬입니다.
	 */
	Matrix4x4f screenOrtho_;
};