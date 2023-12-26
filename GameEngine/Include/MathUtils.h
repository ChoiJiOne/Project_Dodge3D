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
 */
class MathUtils
{
public:
};