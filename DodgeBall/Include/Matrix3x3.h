#pragma once

#include <cstdint>


/**
 * @brief 템플릿 기반의 3x3 행렬입니다.
 */
template <typename T>
struct Matrix3x3
{
	/**
	 * @brief 3x3 행렬의 기본 생성자입니다.
	 *
	 * @note 모든 원소의 값을 0으로 초기화합니다.
	 */
	Matrix3x3() noexcept
	{
		m[0][0] = static_cast<T>(0); m[0][1] = static_cast<T>(0); m[0][2] = static_cast<T>(0);
		m[1][0] = static_cast<T>(0); m[1][1] = static_cast<T>(0); m[1][2] = static_cast<T>(0);
		m[2][0] = static_cast<T>(0); m[2][1] = static_cast<T>(0); m[2][2] = static_cast<T>(0);
	}


	/**
	 * @brief 3x3 행렬의 생성자입니다.
	 *
	 * @param m00 행렬의 (0, 0) 성분입니다.
	 * @param m01 행렬의 (0, 1) 성분입니다.
	 * @param m02 행렬의 (0, 2) 성분입니다.
	 * @param m10 행렬의 (1, 0) 성분입니다.
	 * @param m11 행렬의 (1, 1) 성분입니다.
	 * @param m12 행렬의 (1, 2) 성분입니다.
	 * @param m20 행렬의 (2, 0) 성분입니다.
	 * @param m21 행렬의 (2, 1) 성분입니다.
	 * @param m22 행렬의 (2, 2) 성분입니다.
	 */
	Matrix3x3(
		T&& m00, T&& m01, T&& m02,
		T&& m10, T&& m11, T&& m12,
		T&& m20, T&& m21, T&& m22
	) noexcept
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
	}


	/**
	 * @brief 3x3 행렬의 생성자입니다.
	 *
	 * @param m00 행렬의 (0, 0) 성분입니다.
	 * @param m01 행렬의 (0, 1) 성분입니다.
	 * @param m02 행렬의 (0, 2) 성분입니다.
	 * @param m10 행렬의 (1, 0) 성분입니다.
	 * @param m11 행렬의 (1, 1) 성분입니다.
	 * @param m12 행렬의 (1, 2) 성분입니다.
	 * @param m20 행렬의 (2, 0) 성분입니다.
	 * @param m21 행렬의 (2, 1) 성분입니다.
	 * @param m22 행렬의 (2, 2) 성분입니다.
	 */
	Matrix3x3(
		const T& m00, const T& m01, const T& m02,
		const T& m10, const T& m11, const T& m12,
		const T& m20, const T& m21, const T& m22
	) noexcept
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
	}


	/**
	 * @brief 3x3 행렬의 원소를 하나의 값으로 초기화합니다.
	 *
	 * @param e 모든 원소를 초기화 할 값입니다.
	 */
	Matrix3x3(T&& e) noexcept
	{
		m[0][0] = e; m[0][1] = e; m[0][2] = e;
		m[1][0] = e; m[1][1] = e; m[1][2] = e;
		m[2][0] = e; m[2][1] = e; m[2][2] = e;
	}


	/**
	 * @brief 3x3 행렬의 원소를 하나의 값으로 초기화합니다.
	 *
	 * @param e 모든 원소를 초기화 할 값입니다.
	 */
	Matrix3x3(const T& e) noexcept
	{
		m[0][0] = e; m[0][1] = e; m[0][2] = e;
		m[1][0] = e; m[1][1] = e; m[1][2] = e;
		m[2][0] = e; m[2][1] = e; m[2][2] = e;
	}


	/**
	 * @brief 3x3 행렬의 복사 생성자입니다.
	 *
	 * @param matrix 원소를 복사할 행렬의 인스턴스입니다.
	 */
	Matrix3x3(Matrix3x3<T>&& matrix) noexcept
	{
		m[0][0] = matrix.m[0][0]; m[0][1] = matrix.m[0][1]; m[0][2] = matrix.m[0][2];
		m[1][0] = matrix.m[1][0]; m[1][1] = matrix.m[1][1]; m[1][2] = matrix.m[1][2];
		m[2][0] = matrix.m[2][0]; m[2][1] = matrix.m[2][1]; m[2][2] = matrix.m[2][2];
	}


	/**
	 * @brief 3x3 행렬의 복사 생성자입니다.
	 *
	 * @param matrix 원소를 복사할 행렬의 인스턴스입니다.
	 */
	Matrix3x3(const Matrix3x3<T>& matrix) noexcept
	{
		m[0][0] = matrix.m[0][0]; m[0][1] = matrix.m[0][1]; m[0][2] = matrix.m[0][2];
		m[1][0] = matrix.m[1][0]; m[1][1] = matrix.m[1][1]; m[1][2] = matrix.m[1][2];
		m[2][0] = matrix.m[2][0]; m[2][1] = matrix.m[2][1]; m[2][2] = matrix.m[2][2];
	}


	/**
	 * @brief 3x3 행렬의 대입 연산자입니다.
	 *
	 * @param matrix 원소를 복사할 행렬의 인스턴스입니다.
	 *
	 * @return 대입한 행렬의 참조자를 반환합니다.
	 */
	Matrix3x3<T>& operator=(Matrix3x3<T>&& matrix) noexcept
	{
		if (this == &matrix) return *this;

		m[0][0] = matrix.m[0][0]; m[0][1] = matrix.m[0][1]; m[0][2] = matrix.m[0][2];
		m[1][0] = matrix.m[1][0]; m[1][1] = matrix.m[1][1]; m[1][2] = matrix.m[1][2];
		m[2][0] = matrix.m[2][0]; m[2][1] = matrix.m[2][1]; m[2][2] = matrix.m[2][2];

		return *this;
	}


	/**
	 * @brief 3x3 행렬의 대입 연산자입니다.
	 *
	 * @param matrix 원소를 복사할 행렬의 인스턴스입니다.
	 *
	 * @return 대입한 행렬의 참조자를 반환합니다.
	 */
	Matrix3x3<T>& operator=(const Matrix3x3<T>& matrix) noexcept
	{
		if (this == &matrix) return *this;

		m[0][0] = matrix.m[0][0]; m[0][1] = matrix.m[0][1]; m[0][2] = matrix.m[0][2];
		m[1][0] = matrix.m[1][0]; m[1][1] = matrix.m[1][1]; m[1][2] = matrix.m[1][2];
		m[2][0] = matrix.m[2][0]; m[2][1] = matrix.m[2][1]; m[2][2] = matrix.m[2][2];

		return *this;
	}


	/**
	 * @brief 3x3 행렬의 모든 원소에 -부호를 취합니다.
	 *
	 * @return 모든 원소에 -부호를 취한 새로운 행렬을 반환합니다.
	 */
	Matrix3x3<T> operator-() const
	{
		return Matrix3x3<T>(
			-m[0][0], -m[0][1], -m[0][2],
			-m[1][0], -m[1][1], -m[1][2],
			-m[2][0], -m[2][1], -m[2][2]
		);
	}


	/**
	 * @brief 두 3x3 행렬의 대응하는 원소를 더합니다.
	 *
	 * @param matrix 행렬의 덧셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬의 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Matrix3x3<T> operator+(Matrix3x3<T>&& matrix) const
	{
		return Matrix3x3<T>(
			m[0][0] + matrix.m[0][0], m[0][1] + matrix.m[0][1], m[0][2] + matrix.m[0][2],
			m[1][0] + matrix.m[1][0], m[1][1] + matrix.m[1][1], m[1][2] + matrix.m[1][2],
			m[2][0] + matrix.m[2][0], m[2][1] + matrix.m[2][1], m[2][2] + matrix.m[2][2]
		);
	}


	/**
	 * @brief 두 3x3 행렬의 대응하는 원소를 더합니다.
	 *
	 * @param matrix 행렬의 덧셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬의 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Matrix3x3<T> operator+(const Matrix3x3<T>& matrix) const
	{
		return Matrix3x3<T>(
			m[0][0] + matrix.m[0][0], m[0][1] + matrix.m[0][1], m[0][2] + matrix.m[0][2],
			m[1][0] + matrix.m[1][0], m[1][1] + matrix.m[1][1], m[1][2] + matrix.m[1][2],
			m[2][0] + matrix.m[2][0], m[2][1] + matrix.m[2][1], m[2][2] + matrix.m[2][2]
		);
	}


	/**
	 * @brief 두 3x3 행렬의 대응하는 원소를 뺍니다.
	 *
	 * @param matrix 행렬의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬의 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Matrix3x3<T> operator-(Matrix3x3<T>&& matrix) const
	{
		return Matrix3x3<T>(
			m[0][0] - matrix.m[0][0], m[0][1] - matrix.m[0][1], m[0][2] - matrix.m[0][2],
			m[1][0] - matrix.m[1][0], m[1][1] - matrix.m[1][1], m[1][2] - matrix.m[1][2],
			m[2][0] - matrix.m[2][0], m[2][1] - matrix.m[2][1], m[2][2] - matrix.m[2][2]
		);
	}


	/**
	 * @brief 두 3x3 행렬의 대응하는 원소를 뺍니다.
	 *
	 * @param matrix 행렬의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬의 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Matrix3x3<T> operator-(const Matrix3x3<T>& matrix) const
	{
		return Matrix3x3<T>(
			m[0][0] - matrix.m[0][0], m[0][1] - matrix.m[0][1], m[0][2] - matrix.m[0][2],
			m[1][0] - matrix.m[1][0], m[1][1] - matrix.m[1][1], m[1][2] - matrix.m[1][2],
			m[2][0] - matrix.m[2][0], m[2][1] - matrix.m[2][1], m[2][2] - matrix.m[2][2]
		);
	}


	/**
	 * @brief 두 3x3 행렬을 곱합니다.
	 *
	 * @param matrix 행렬의 곱셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬을 곱한 결과를 반환합니다.
	 */
	Matrix3x3<T> operator*(Matrix3x3<T>&& matrix) const
	{
		return Matrix3x3(
			m[0][0] * matrix.m[0][0] + m[0][1] * matrix.m[1][0] + m[0][2] * matrix.m[2][0],
			m[0][0] * matrix.m[0][1] + m[0][1] * matrix.m[1][1] + m[0][2] * matrix.m[2][1],
			m[0][0] * matrix.m[0][2] + m[0][1] * matrix.m[1][2] + m[0][2] * matrix.m[2][2],
			m[1][0] * matrix.m[0][0] + m[1][1] * matrix.m[1][0] + m[1][2] * matrix.m[2][0],
			m[1][0] * matrix.m[0][1] + m[1][1] * matrix.m[1][1] + m[1][2] * matrix.m[2][1],
			m[1][0] * matrix.m[0][2] + m[1][1] * matrix.m[1][2] + m[1][2] * matrix.m[2][2],
			m[2][0] * matrix.m[0][0] + m[2][1] * matrix.m[1][0] + m[2][2] * matrix.m[2][0],
			m[2][0] * matrix.m[0][1] + m[2][1] * matrix.m[1][1] + m[2][2] * matrix.m[2][1],
			m[2][0] * matrix.m[0][2] + m[2][1] * matrix.m[1][2] + m[2][2] * matrix.m[2][2]
		);
	}


	/**
	 * @brief 두 3x3 행렬을 곱합니다.
	 *
	 * @param matrix 행렬의 곱셈을 수행할 피연산자입니다.
	 *
	 * @return 두 행렬을 곱한 결과를 반환합니다.
	 */
	Matrix3x3<T> operator*(const Matrix3x3<T>& matrix) const
	{
		return Matrix3x3(
			m[0][0] * matrix.m[0][0] + m[0][1] * matrix.m[1][0] + m[0][2] * matrix.m[2][0],
			m[0][0] * matrix.m[0][1] + m[0][1] * matrix.m[1][1] + m[0][2] * matrix.m[2][1],
			m[0][0] * matrix.m[0][2] + m[0][1] * matrix.m[1][2] + m[0][2] * matrix.m[2][2],
			m[1][0] * matrix.m[0][0] + m[1][1] * matrix.m[1][0] + m[1][2] * matrix.m[2][0],
			m[1][0] * matrix.m[0][1] + m[1][1] * matrix.m[1][1] + m[1][2] * matrix.m[2][1],
			m[1][0] * matrix.m[0][2] + m[1][1] * matrix.m[1][2] + m[1][2] * matrix.m[2][2],
			m[2][0] * matrix.m[0][0] + m[2][1] * matrix.m[1][0] + m[2][2] * matrix.m[2][0],
			m[2][0] * matrix.m[0][1] + m[2][1] * matrix.m[1][1] + m[2][2] * matrix.m[2][1],
			m[2][0] * matrix.m[0][2] + m[2][1] * matrix.m[1][2] + m[2][2] * matrix.m[2][2]
		);
	}


	/**
	 * @brief 두 3x3 행렬에 대응하는 원소를 더합니다.
	 *
	 * @param matrix 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 행렬의 참조자를 반환합니다.
	 */
	Matrix3x3<T>& operator+=(Matrix3x3<T>&& matrix) noexcept
	{
		m[0][0] += matrix.m[0][0]; m[0][1] += matrix.m[0][1]; m[0][2] += matrix.m[0][2];
		m[1][0] += matrix.m[1][0]; m[1][1] += matrix.m[1][1]; m[1][2] += matrix.m[1][2];
		m[2][0] += matrix.m[2][0]; m[2][1] += matrix.m[2][1]; m[2][2] += matrix.m[2][2];

		return *this;
	}


	/**
	 * @brief 두 3x3 행렬에 대응하는 원소를 더합니다.
	 *
	 * @param matrix 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 행렬의 참조자를 반환합니다.
	 */
	Matrix3x3<T>& operator+=(const Matrix3x3<T>& matrix) noexcept
	{
		m[0][0] += matrix.m[0][0]; m[0][1] += matrix.m[0][1]; m[0][2] += matrix.m[0][2];
		m[1][0] += matrix.m[1][0]; m[1][1] += matrix.m[1][1]; m[1][2] += matrix.m[1][2];
		m[2][0] += matrix.m[2][0]; m[2][1] += matrix.m[2][1]; m[2][2] += matrix.m[2][2];

		return *this;
	}


	/**
	 * @brief 두 3x3 행렬에 대응하는 원소를 뺍니다.
	 *
	 * @param matrix 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 행렬의 참조자를 반환합니다.
	 */
	Matrix3x3<T>& operator-=(Matrix3x3<T>&& matrix) noexcept
	{
		m[0][0] -= matrix.m[0][0]; m[0][1] -= matrix.m[0][1]; m[0][2] -= matrix.m[0][2];
		m[1][0] -= matrix.m[1][0]; m[1][1] -= matrix.m[1][1]; m[1][2] -= matrix.m[1][2];
		m[2][0] -= matrix.m[2][0]; m[2][1] -= matrix.m[2][1]; m[2][2] -= matrix.m[2][2];

		return *this;
	}


	/**
	 * @brief 두 3x3 행렬에 대응하는 원소를 뺍니다.
	 *
	 * @param matrix 연산을 수행할 피연산자입니다.
	 *
	 * @return 연산을 수행한 행렬의 참조자를 반환합니다.
	 */
	Matrix3x3<T>& operator-=(const Matrix3x3<T>& matrix) noexcept
	{
		m[0][0] -= matrix.m[0][0]; m[0][1] -= matrix.m[0][1]; m[0][2] -= matrix.m[0][2];
		m[1][0] -= matrix.m[1][0]; m[1][1] -= matrix.m[1][1]; m[1][2] -= matrix.m[1][2];
		m[2][0] -= matrix.m[2][0]; m[2][1] -= matrix.m[2][1]; m[2][2] -= matrix.m[2][2];

		return *this;
	}


	/**
	 * @brief 3x3 행렬 원소 배열의 포인터를 얻습니다.
	 *
	 * @return 3x3 행렬 원소 배열의 포인터를 반환합니다.
	 */
	const T* GetPtr() const { return &m[0][0]; }


	/**
	 * @brief 3x3 행렬 원소 배열의 포인터를 얻습니다.
	 *
	 * @return 3x3 행렬 원소 배열의 포인터를 반환합니다.
	 */
	T* GetPtr() { return &m[0][0]; }


	/**
	 * @brief 3x3 행렬의 단위 행렬을 얻습니다.
	 *
	 * @return 3x3 행렬의 단위 행렬를 반환합니다.
	 */
	static Matrix3x3<T> GetIdentity()
	{
		return Matrix3x3(
			static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
			static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
			static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
		);
	}


	/**
	 * @brief 3x3 행렬의 원소입니다.
	 */
	T m[3][3];
};


/**
 * @brief int32_t 타입의 3x3 행렬입니다.
 */
using Matrix3x3i = Matrix3x3<int32_t>;


/**
 * @brief float 타입의 3x3 행렬입니다.
 */
using Matrix3x3f = Matrix3x3<float>;