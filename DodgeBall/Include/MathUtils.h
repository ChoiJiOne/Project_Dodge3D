#pragma once

#include <algorithm>
#include <cmath>
#include <chrono>
#include <random>

#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief 파이(π) 값입니다.
 */
const float Pi = 3.141592654f;


/**
 * @brief 2파이(2π) 값입니다.
 */
const float TwoPi = 6.283185307f;


/**
 * @brief 파이(π) 의 역수 값입니다.
 */
const float OneDivPi = 0.318309886f;


/**
 * @brief 2파이(2π) 의 역수 값입니다.
 */
const float OneDivTwoPi = 0.159154943f;


/**
 * @brief 파이(π) 의 반값(π/2)입니다.
 */
const float PiDiv2 = 1.570796327f;


/**
 * @brief 파이(π) 의 반의 반 값(π/4)입니다.
 */
const float PiDiv4 = 0.785398163f;


/**
 * @brief 양의 무한대 값입니다.
 */
const float Infinity = std::numeric_limits<float>::infinity();


/**
 * @brief 음의 무한대 값입니다.
 */
const float NInfinity = -std::numeric_limits<float>::infinity();


/**
 * @brief 엡실론(ε) 값입니다.
 */
const float Epsilon = std::numeric_limits<float>::epsilon();


/**
 * @brief 수학 관련 확장 기능을 제공합니다.
 * 
 * @note 행렬 관련 기능은 OpenGL 기준입니다.
 */
namespace MathUtils
{
	/**
	 * @brief 라디안 각을 육십분법 각으로 변환합니다.
	 *
	 * @param radian 변환할 라디안 각입니다.
	 *
	 * @return 변환된 육십분법 각입니다.
	 */
	inline float ToDegree(float radian)
	{
		return (radian * 180.0f) / Pi;
	}


	/**
	 * @brief 육십분법 각을 라디안 각으로 변환합니다.
	 *
	 * @param degree 변환할 육십분법 각입니다.
	 *
	 * @return 변환된 라디안 각입니다.
	 */
	inline float ToRadian(float degree)
	{
		return (degree * Pi) / 180.0f;
	}


	/**
	 * @brief 부동 소수점 값이 0에 가까운지 확인합니다.
	 *
	 * @param value 0에 가까운지 확인할 값입니다.
	 * @param epsilon 값 확인을 위한 엡실론 값입니다.
	 *
	 * @return 부동 소수점 값이 0에 가깝다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	inline bool NearZero(float value, float epsilon = Epsilon)
	{
		return (std::fabs(value) <= epsilon);
	}


	/**
	 * @brief 두 값중 큰 값을 반환합니다.
	 *
	 * @param lhs 크기를 비교할 값 중 왼쪽 값입니다.
	 * @param rhs 크기를 비교할 값 중 오른쪽 값입니다.
	 *
	 * @return 두 값 중 큰 값을 반환합니다.
	 */
	template <typename T>
	inline T Max(const T& lhs, const T& rhs)
	{
		return (lhs < rhs ? rhs : lhs);
	}


	/**
	 * @brief 두 값중 작은 값을 반환합니다.
	 *
	 * @param lhs 크기를 비교할 값 중 왼쪽 값입니다.
	 * @param rhs 크기를 비교할 값 중 오른쪽 값입니다.
	 *
	 * @return 두 값 중 작은 값을 반환합니다.
	 */
	template <typename T>
	inline T Min(const T& lhs, const T& rhs)
	{
		return (lhs < rhs ? lhs : rhs);
	}


	/**
	 * @brief 라디안 각도에 대응하는 사인 값을 얻습니다.
	 * 
	 * @param radian 사인 값을 얻을 라디안 각도입니다.
	 * 
	 * @return 라디안 각도에 대응하는 사인값을 반환합니다.
	 * 
	 * @note
	 * - DirectXMath의 XMScalarSin 참조
	 * - 알고리즘은 11차원 미니맥스(Minimax) 근사치(1th-degree Minimax approximation) 사용
	 * - https://gist.github.com/publik-void/067f7f2fef32dbe5c27d6e215f824c91
	 */
	inline float Sin(float radian)
	{
		float quotient = OneDivTwoPi * radian;
		if (radian >= 0.0f)
		{
			quotient = static_cast<float>(static_cast<int>(quotient + 0.5f));
		}
		else
		{
			quotient = static_cast<float>(static_cast<int>(quotient - 0.5f));
		}

		float y = radian - TwoPi * quotient;

		if (y > PiDiv2)
		{
			y = Pi - y;
		}
		else if (y < -PiDiv2)
		{
			y = -Pi - y;
		}

		float y2 = y * y;
		return (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;
	}


	/**
	 * @brief 라디안 각도에 대응하는 코사인 값을 반환합니다.
	 *
	 * @param radian 코사인 값을 얻을 라디안 각도입니다.
	 *
	 * @return 라디안 각도에 대응하는 코사인값을 반환합니다.
	 *
	 * @note
	 * - DirectXMath의 XMScalarCos 참조
	 * - 알고리즘은 10차원 미니맥스(Minimax) 근사치(1th-degree Minimax approximation) 사용
	 * - https://gist.github.com/publik-void/067f7f2fef32dbe5c27d6e215f824c91
	 */
	inline float Cos(float radian)
	{
		float quotient = OneDivTwoPi * radian;
		if (radian >= 0.0f)
		{
			quotient = static_cast<float>(static_cast<int>(quotient + 0.5f));
		}
		else
		{
			quotient = static_cast<float>(static_cast<int>(quotient - 0.5f));
		}

		float y = radian - TwoPi * quotient;
		float sign = 1.0f;

		if (y > PiDiv2)
		{
			y = Pi - y;
			sign = -1.0f;
		}
		else if (y < -PiDiv2)
		{
			y = -Pi - y;
			sign = -1.0f;
		}

		float y2 = y * y;
		float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;

		return sign * p;
	}


	/**
	 * @brief 값을 [lower, upper] 범위로 자릅니다.
	 *
	 * @param value 범위로 자를 값입니다.
	 * @param lower 범위의 최소값입니다.
	 * @param upper 범위의 최대값입니다.
	 *
	 * @return 범위로 잘려 나간 값을 반환합니다.
	 */
	template <typename T>
	inline T Clamp(const T& value, const T& lower, const T& upper)
	{
		return Min(upper, Max(lower, value));
	}


	/**
	 * @brief 2차원 백터의 내적 연산을 수행합니다.
	 *
	 * @param lhs 백터의 내적 연산을 수행할 좌측 피연산자입니다.
	 * @param rhs 백터의 내적 연산을 수행할 우측 피연산자입니다.
	 *
	 * @return 내적 연산 결과를 반환합니다.
	 */
	template <typename T>
	inline T DotProduct(const Vector2<T>& lhs, const Vector2<T>& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}


	/**
	 * @brief 3차원 백터의 내적 연산을 수행합니다.
	 *
	 * @param lhs 백터의 내적 연산을 수행할 좌측 피연산자입니다.
	 * @param rhs 백터의 내적 연산을 수행할 우측 피연산자입니다.
	 *
	 * @return 내적 연산 결과를 반환합니다.
	 */
	template <typename T>
	inline T DotProduct(const Vector3<T>& lhs, const Vector3<T>& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}


	/**
	 * @brief 4차원 백터의 내적 연산을 수행합니다.
	 *
	 * @param lhs 백터의 내적 연산을 수행할 좌측 피연산자입니다.
	 * @param rhs 백터의 내적 연산을 수행할 우측 피연산자입니다.
	 *
	 * @return 내적 연산 결과를 반환합니다.
	 */
	template <typename T>
	inline T DotProduct(const Vector4<T>& lhs, const Vector4<T>& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
	}


	/**
	 * @brief 2차원 백터의 외적 연산을 수행합니다.
	 *
	 * @param lhs 백터의 외적 연산을 수행할 좌측 피연산자입니다.
	 * @param rhs 백터의 외적 연산을 수행할 우측 피연산자입니다.
	 *
	 * @return 외적 연산 결과를 반환합니다.
	 *
	 * @note 일반적인 3차원 외적 연산과 다릅니다.
	 */
	template <typename T>
	inline T CrossProduct(const Vector2<T>& lhs, const Vector2<T>& rhs)
	{
		return lhs.x * rhs.y - lhs.y * rhs.x;
	}


	/**
	 * @brief 3차원 벡터의 외적 연산을 수행합니다.
	 * 
	 * @param lhs 백터의 외적 연산을 수행할 좌측 피연산자입니다.
	 * @param rhs 백터의 외적 연산을 수행할 우측 피연산자입니다.
	 * 
	 * @return 외적 연산 결과를 반환합니다.
	 */
	template <typename T>
	inline Vector3<T> CrossProduct(const Vector3<T>& lhs, const Vector3<T>& rhs)
	{
		return Vector3<T>(
			lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x
		);
	}


	/**
	 * @brief 2차원 백터의 크기 제곱 값을 계산합니다.
	 *
	 * @param v 크기 제곱을 계산할 벡터입니다.
	 *
	 * @return 계산된 크기 제곱 값을 반환합니다.
	 */
	template <typename T>
	inline T LengthSquare(const Vector2<T>& v)
	{
		return v.x * v.x + v.y * v.y;
	}


	/**
	 * @brief 3차원 백터의 크기 제곱 값을 계산합니다.
	 *
	 * @param v 크기 제곱을 계산할 벡터입니다.
	 *
	 * @return 계산된 크기 제곱 값을 반환합니다.
	 */
	template <typename T>
	inline T LengthSquare(const Vector3<T>& v)
	{
		return v.x * v.x + v.y * v.y + v.z * v.z;
	}


	/**
	 * @brief 4차원 백터의 크기 제곱 값을 계산합니다.
	 *
	 * @param v 크기 제곱을 계산할 벡터입니다.
	 *
	 * @return 계산된 크기 제곱 값을 반환합니다.
	 */
	template <typename T>
	inline T LengthSquare(const Vector4<T>& v)
	{
		return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
	}


	/**
	 * @brief 2차원 벡터의 크기를 얻습니다.
	 *
	 * @param v 크기를 계산할 벡터입니다.
	 *
	 * @return 계산된 크기 값을 반환합니다.
	 */
	template <typename T>
	inline float Length(const Vector2<T>& v)
	{
		float lengthSquare = static_cast<float>(LengthSquare<T>(v));
		return std::sqrtf(lengthSquare);
	}


	/**
	 * @brief 3차원 벡터의 크기를 얻습니다.
	 *
	 * @param v 크기를 계산할 벡터입니다.
	 *
	 * @return 계산된 크기 값을 반환합니다.
	 */
	template <typename T>
	inline float Length(const Vector3<T>& v)
	{
		float lengthSquare = static_cast<float>(LengthSquare<T>(v));
		return std::sqrtf(lengthSquare);
	}


	/**
	 * @brief 4차원 벡터의 크기를 얻습니다.
	 *
	 * @param v 크기를 계산할 벡터입니다.
	 *
	 * @return 계산된 크기 값을 반환합니다.
	 */
	template <typename T>
	inline float Length(const Vector4<T>& v)
	{
		float lengthSquare = static_cast<float>(LengthSquare<T>(v));
		return std::sqrtf(lengthSquare);
	}


	/**
	 * @brief 2차원 벡터를 정규화합니다.
	 *
	 * @param v 정규화 할 벡터입니다.
	 *
	 * @return 정규화된 벡터를 반환합니다.
	 */
	inline Vector2f Normalize(const Vector2f& v)
	{
		float length = Length(v);
		return Vector2f(v.x / length, v.y / length);
	}


	/**
	 * @brief 3차원 벡터를 정규화합니다.
	 *
	 * @param v 정규화 할 벡터입니다.
	 *
	 * @return 정규화된 벡터를 반환합니다.
	 */
	inline Vector3f Normalize(const Vector3f& v)
	{
		float length = Length(v);
		return Vector3f(v.x / length, v.y / length, v.z / length);
	}


	/**
	 * @brief 4차원 벡터를 정규화합니다.
	 *
	 * @param v 정규화 할 벡터입니다.
	 *
	 * @return 정규화된 벡터를 반환합니다.
	 */
	inline Vector4f Normalize(const Vector4f& v)
	{
		float length = Length(v);
		return Vector4f(v.x / length, v.y / length, v.z / length, v.w / length);
	}


	/**
	 * @brief 임의의 정수를 생성합니다.
	 *
	 * @param minValue 생성할 난수 범위의 최솟값입니다.
	 * @param maxValue 생성할 난수 범위의 최댓값입니다.
	 *
	 * @return 생성된 임의의 정수를 반환합니다.
	 */
	inline int32_t GenerateRandomInt(int32_t minValue, int32_t maxValue)
	{
		std::random_device randomDevice;
		std::mt19937 generator(randomDevice());
		std::uniform_int_distribution<int32_t> distribution(Min<int32_t>(minValue, maxValue), Max<int32_t>(minValue, maxValue));

		return distribution(generator);
	}


	/**
	 * @brief 임의의 실수를 생성합니다.
	 *
	 * @param minValue 생성할 난수 범위의 최솟값입니다.
	 * @param maxValue 생성할 난수 범위의 최댓값입니다.
	 *
	 * @return 생성된 임의의 실수를 반환합니다.
	 */
	inline float GenerateRandomFloat(float minValue, float maxValue)
	{
		std::random_device randomDevice;
		std::mt19937 generator(randomDevice());
		std::uniform_real_distribution<float> distribution(Min<float>(minValue, maxValue), Max<float>(minValue, maxValue));

		return distribution(generator);
	}


	/**
	 * @brief 이동 변환 행렬을 생성합니다.
	 *
	 * @param x 이동할 x 좌표값입니다.
	 * @param y 이동할 y 좌표값입니다.
	 * @param z 이동할 z 좌표값입니다.
	 *
	 * @return 생성된 이동 변환 행렬을 반환합니다.
	 */
	inline Matrix4x4f CreateTranslation(float x, float y, float z)
	{
		return Matrix4x4f(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			   x,    y,    z, 1.0f
		);
	}


	/**
	 * @brief 이동 변환 행렬을 생성합니다.
	 *
	 * @param p 이동할 위치 좌표입니다.
	 *
	 * @return 생성된 이동 변환 행렬을 반환합니다.
	 */
	inline Matrix4x4f CreateTranslation(const Vector3f& p)
	{
		return Matrix4x4f(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			 p.x,  p.y,  p.z, 1.0f
		);
	}


	/**
	 * @brief 스케일 변환 행렬을 생성합니다.
	 *
	 * @param xScale 변환할 x축 방향의 스케일입니다.
	 * @param yScale 변환할 y축 방향의 스케일입니다.
	 * @param zScale 변환할 z축 방향의 스케일입니다.
	 *
	 * @return 생성된 스케일 변환 행렬을 반환합니다.
	 */
	inline Matrix4x4f CreateScale(float xScale, float yScale, float zScale)
	{
		return Matrix4x4f(
			xScale, 0.0f, 0.0f, 0.0f,
			0.0f, yScale, 0.0f, 0.0f,
			0.0f, 0.0f, zScale, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}


	/**
	 * @brief 스케일 변환 행렬을 생성합니다.
	 *
	 * @param scale 변환할 스케일 벡터입니다.
	 *
	 * @return 생성된 스케일 변환 행렬을 반환합니다.
	 */
	inline Matrix4x4f CreateScale(const Vector3f& scale)
	{
		return Matrix4x4f(
			scale.x, 0.0f, 0.0f, 0.0f,
			0.0f, scale.y, 0.0f, 0.0f,
			0.0f, 0.0f, scale.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}


	/**
	 * @brief X축으로 회전시키는 회전 행렬을 생성합니다.
	 *
	 * @param radian 회전할 라디안 각도입니다.
	 *
	 * @return 생성된 회전 행렬을 반환합니다.
	 */
	inline Matrix4x4f CreateRotateX(float radian)
	{
		float s = Sin(radian);
		float c = Cos(radian);

		return Matrix4x4f(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f,    c,    s, 0.0f,
			0.0f,   -s,    c, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}


	/**
	 * @brief Y축으로 회전시키는 회전 행렬을 생성합니다.
	 *
	 * @param radian 회전할 라디안 각도입니다.
	 *
	 * @return 생성된 회전 행렬을 반환합니다.
	 */
	inline Matrix4x4f CreateRotateY(float radian)
	{
		float s = Sin(radian);
		float c = Cos(radian);

		return Matrix4x4f(
			   c, 0.0f,   -s, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			   s, 0.0f,    c, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}


	/**
	 * @brief Z축으로 회전시키는 회전 행렬을 생성합니다.
	 *
	 * @param radian 회전할 라디안 각도입니다.
	 *
	 * @return 생성된 회전 행렬을 반환합니다.
	 */
	inline Matrix4x4f CreateRotateZ(float radian)
	{
		float s = Sin(radian);
		float c = Cos(radian);

		return Matrix4x4f(
			   c,    s, 0.0f, 0.0f,
			  -s,    c, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}


	/**
	 * @brief 임의의 벡터를 기준으로 회전 행렬을 생성합니다.
	 * 
	 * @param radian 회전할 회전 각도입니다.
	 * @param axis 회전축입니다.
	 * 
	 * @return 생성된 회전 행렬을 반환합니다.
	 * 
	 * @see 
	 * - 로드리게스 회전 공식 참조
	 * - https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula
	 */
	inline Matrix4x4f CreateRotate(float radian, const Vector3f& axis)
	{
		float s = Sin(radian);
		float c = Cos(radian);
		Vector3f r = Normalize(axis);

		return Matrix4x4f(
		  	      c + r.x * r.x * (1.0f - c), r.y * r.x * (1.0f - c) + r.z * s, r.z * r.x * (1.0f - c) - r.y * s, 0.0f,
			r.x * r.y * (1.0f - c) - r.z * s,       c + r.y * r.y * (1.0f - c), r.z * r.y * (1.0f - c) + r.x * s, 0.0f,
			r.x * r.z * (1.0f - c) + r.y * s, r.y * r.z * (1.0f - c) - r.x * s,       c + r.z * r.z * (1.0f - c), 0.0f,
			                            0.0f,                             0.0f,                             0.0f, 1.0f
		);
	}


	/**
	 * @brief 직교 투영 행렬을 생성합니다.
	 *
	 * @param left   투영 공간의 좌측 경계 평면 값
	 * @param right  투영 공간의 우측 경계 평면 값
	 * @param bottom 투영 공간의 하단 경계 평면 값
	 * @param top    투영 공간의 상단 경계 평면 값
	 * @param zNear  투영 공간의 전방 경계 평면 값
	 * @param zFar   투영 공간의 후방 경계 평면 값
	 *
	 * @return 생성된 직교 투영 행렬을 반환합니다.
	 */
	inline Matrix4x4f CreateOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		float width = (right - left);
		float sumLR = (right + left);
		float height = (top - bottom);
		float sumTB = (top + bottom);
		float depth = (zFar - zNear);
		float sumNF = (zFar + zNear);

		return Matrix4x4f(
			  2.0f / width,            0.0f,           0.0f, 0.0f,
			          0.0f,   2.0f / height,           0.0f, 0.0f,
			          0.0f,            0.0f,  -2.0f / depth, 0.0f,
			-sumLR / width, -sumTB / height, -sumNF / depth, 1.0f
		);
	}


	/**
	 * @brief 원근 투영 행렬을 생성합니다.
	 * 
	 * @param fov 라디안 단위의 시야 각도입니다.
	 * @param aspect 뷰 공간의 가로/세로 비율입니다.
	 * @param nearZ 가까운 클리핑 평면 사이의 거리입니다. 0보다 커야 합니다.
	 * @param farZ 원거리 클리핑 평면 사이의 거리입니다. 0보다 커야 합니다.
	 * 
	 * @return 생성된 원근 투영 행렬을 반환합니다.
	 */
	inline Matrix4x4f CreatePerspective(float fov, float aspect, float nearZ, float farZ)
	{
		float halfFov = fov / 2.0f;
		float tanHalfFovy = Sin(halfFov) / Cos(halfFov);
		
		return Matrix4x4f(
			1.0f / (aspect * tanHalfFovy),                 0.0f,                                    0.0f,  0.0f,
			                         0.0f, 1.0f / (tanHalfFovy),                                    0.0f,  0.0f,
			                         0.0f,                 0.0f,        -(farZ + nearZ) / (farZ - nearZ), -1.0f,
			                         0.0f,                 0.0f, -(2.0f * farZ * nearZ) / (farZ - nearZ),  1.0f
		);
	}


	/**
	 * @brief 시야 행렬을 생성합니다.
	 * 
	 * @param eyePosition 카메라의 위치입니다.
	 * @param focusPosition 초점의 위치입니다.
	 * @param upDirection 카메라의 위쪽 방향입니다. 일반적으로 <0.0f, 1.0f, 0.0f> 입니다.
	 * 
	 * @return 생성된 시야 행렬을 반환합니다.
	 */
	inline Matrix4x4f CreateLookAt(const Vector3f& eyePosition, const Vector3f& focusPosition, const Vector3f& upDirection)
	{
		Vector3f f = Normalize(focusPosition - eyePosition);
		Vector3f s = Normalize(CrossProduct(f, upDirection));
		Vector3f u = CrossProduct(s, f);

		return Matrix4x4f(
			                        s.x,                         u.x,                       -f.x, 0.0f,
			                        s.y,                         u.y,                       -f.y, 0.0f,
			                        s.z,                         u.z,                       -f.z, 0.0f,
			-DotProduct(s, eyePosition), -DotProduct(u, eyePosition), DotProduct(f, eyePosition), 1.0f
		);
	}
};