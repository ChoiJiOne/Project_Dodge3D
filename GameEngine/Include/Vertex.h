#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


/**
 * @brief 위치 정보를 가진 정점(Vertex)입니다.
 */
struct VertexPosition
{
	/**
	 * @brief 위치 정보를 가진 정점의 기본 생성자입니다.
	 */
	VertexPosition() noexcept
		: position(0.0f, 0.0f, 0.0f) {}


	/**
	 * @brief 위치 정보를 가진 정점의 생성자입니다.
	 *
	 * @param p 정점의 위치입니다.
	 */
	VertexPosition(Vector3f&& p) noexcept
		: position(p) {}


	/**
	 * @brief 위치 정보를 가진 정점의 생성자입니다.
	 *
	 * @param p 정점의 위치입니다.
	 */
	VertexPosition(const Vector3f& p) noexcept
		: position(p) {}


	/**
	 * @brief 위치 정보를 가진 정점의 생성자입니다.
	 *
	 * @param x 위치의 X좌표입니다.
	 * @param y 위치의 Y좌표입니다.
	 * @param z 위치의 Z좌표입니다.
	 */
	VertexPosition(float x, float y, float z) noexcept
		: position(x, y, z) {}


	/**
	 * @brief 위치 정보를 가진 정점의 생성자입니다.
	 *
	 * @param instance 복사할 정점 인스턴스입니다.
	 */
	VertexPosition(VertexPosition&& instance) noexcept
		: position(instance.position) {}


	/**
	 * @brief 위치 정보를 가진 정점의 생성자입니다.
	 *
	 * @param instance 복사할 정점 인스턴스입니다.
	 */
	VertexPosition(const VertexPosition& instance) noexcept
		: position(instance.position) {}


	/**
	 * @brief 위치 정보를 가진 정점의 대입 연산자입니다.
	 *
	 * @param instance 대입할 정점 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	VertexPosition& operator=(VertexPosition&& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;

		return *this;
	}


	/**
	 * @brief 위치 정보를 가진 정점의 대입 연산자입니다.
	 *
	 * @param instance 대입할 정점 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	VertexPosition& operator=(const VertexPosition& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;

		return *this;
	}


	/**
	 * @brief 정점의 바이트 보폭 값을 얻습니다.
	 *
	 * @return 정점의 파이트 보폭(Stride) 값을 반환합니다.
	 */
	static uint32_t GetStride()
	{
		return sizeof(VertexPosition);
	}


	/**
	 * @brief 정점의 위치입니다.
	 */
	Vector3f position;
};


/**
 * @brief 위치와 색상 정보를 가진 정점(Vertex)입니다.
 */
struct VertexPositionColor
{
	/**
	 * @brief 위치와 색상 정보를 가진 정점의 기본 생성자입니다.
	 */
	VertexPositionColor() noexcept
		: position(0.0f, 0.0f, 0.0f)
		, color(0.0f, 0.0f, 0.0f, 0.0f) {}


	/**
	 * @brief 위치와 색상 정보를 가진 정점의 생성자입니다.
	 *
	 * @param p 정점의 위치입니다.
	 * @param c 정점의 색상입니다.
	 */
	VertexPositionColor(Vector3f&& p, Vector4f&& c) noexcept
		: position(p)
		, color(c) {}


	/**
	 * @brief 위치와 색상 정보를 가진 정점의 생성자입니다.
	 *
	 * @param p 정점의 위치입니다.
	 * @param c 정점의 색상입니다.
	 */
	VertexPositionColor(const Vector3f& p, const Vector4f& c) noexcept
		: position(p)
		, color(c) {}


	/**
	 * @brief 위치와 색상 정보를 가진 정점의 생성자입니다.
	 *
	 * @param x 위치의 X좌표입니다.
	 * @param y 위치의 Y좌표입니다.
	 * @param z 위치의 Z좌표입니다.
	 * @param r 정점 색상의 R입니다.
	 * @param g 정점 색상의 G입니다.
	 * @param b 정점 색상의 B입니다.
	 * @param a 정점 색상의 A입니다.
	 */
	VertexPositionColor(
		float x, float y, float z,
		float r, float g, float b, float a
	) noexcept
		: position(x, y, z)
		, color(r, g, b, a) {}


	/**
	 * @brief 위치와 색상 정보를 가진 정점의 생성자입니다.
	 *
	 * @param instance 복사할 정점 인스턴스입니다.
	 */
	VertexPositionColor(VertexPositionColor&& instance) noexcept
		: position(instance.position)
		, color(instance.color) {}


	/**
	 * @brief 위치와 색상 정보를 가진 정점의 생성자입니다.
	 *
	 * @param instance 복사할 정점 인스턴스입니다.
	 */
	VertexPositionColor(const VertexPositionColor& instance) noexcept
		: position(instance.position)
		, color(instance.color) {}


	/**
	 * @brief 위치와 색상 정보를 가진 정점의 대입 연산자입니다.
	 *
	 * @param instance 대입할 정점 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	VertexPositionColor& operator=(VertexPositionColor&& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;
		color = instance.color;

		return *this;
	}


	/**
	 * @brief 위치와 색상 정보를 가진 정점의 대입 연산자입니다.
	 *
	 * @param instance 대입할 정점 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	VertexPositionColor& operator=(const VertexPositionColor& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;
		color = instance.color;

		return *this;
	}


	/**
	 * @brief 정점의 바이트 보폭 값을 얻습니다.
	 *
	 * @return 정점의 파이트 보폭(Stride) 값을 반환합니다.
	 */
	static uint32_t GetStride()
	{
		return sizeof(VertexPositionColor);
	}


	/**
	 * @brief 정점의 위치입니다.
	 */
	Vector3f position;


	/**
	 * @brief 정점의 색상입니다.
	 */
	Vector4f color;
};


/**
 * @brief 위치와 텍스처 정보를 가진 정점(Vertex)입니다.
 */
struct VertexPositionTexture
{
	/**
	 * @brief 위치와 텍스처 정보를 가진 정점의 기본 생성자입니다.
	 */
	VertexPositionTexture() noexcept
		: position(0.0f, 0.0f, 0.0f)
		, texture(0.0f, 0.0f) {}


	/**
	 * @brief 위치와 텍스처 정보를 가진 정점의 생성자입니다.
	 *
	 * @param p 정점의 위치입니다.
	 * @param uv 정점의 텍스처 위치입니다.
	 */
	VertexPositionTexture(Vector3f&& p, Vector2f&& uv) noexcept
		: position(p)
		, texture(uv) {}


	/**
	 * @brief 위치와 텍스처 정보를 가진 정점의 생성자입니다.
	 *
	 * @param p 정점의 위치입니다.
	 * @param uv 정점의 텍스처 위치입니다.
	 */
	VertexPositionTexture(const Vector3f& p, const Vector2f& uv) noexcept
		: position(p)
		, texture(uv) {}


	/**
	 * @brief 위치와 텍스처 정보를 가진 정점의 생성자입니다.
	 *
	 * @param x 위치의 X좌표입니다.
	 * @param y 위치의 Y좌표입니다.
	 * @param z 위치의 Z좌표입니다.
	 * @param u 텍스처 위치의 U좌표입니다.
	 * @param v 텍스처 위치의 V좌표입니다.
	 */
	VertexPositionTexture(
		float x, float y, float z,
		float u, float v
	) noexcept
		: position(x, y, z)
		, texture(u, v) {}


	/**
	 * @brief 위치와 텍스처 정보를 가진 정점의 생성자입니다.
	 *
	 * @param instance 복사할 정점 인스턴스입니다.
	 */
	VertexPositionTexture(VertexPositionTexture&& instance) noexcept
		: position(instance.position)
		, texture(instance.texture) {}


	/**
	 * @brief 위치와 텍스처 정보를 가진 정점의 생성자입니다.
	 *
	 * @param instance 복사할 정점 인스턴스입니다.
	 */
	VertexPositionTexture(const VertexPositionTexture& instance) noexcept
		: position(instance.position)
		, texture(instance.texture) {}


	/**
	 * @brief 위치와 텍스처 정보를 가진 정점의 대입 연산자입니다.
	 *
	 * @param instance 대입할 정점 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	VertexPositionTexture& operator=(VertexPositionTexture&& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;
		texture = instance.texture;

		return *this;
	}


	/**
	 * @brief 위치와 텍스처 정보를 가진 정점의 대입 연산자입니다.
	 *
	 * @param instance 대입할 정점 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	VertexPositionTexture& operator=(const VertexPositionTexture& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;
		texture = instance.texture;

		return *this;
	}


	/**
	 * @brief 정점의 바이트 보폭 값을 얻습니다.
	 *
	 * @return 정점의 파이트 보폭(Stride) 값을 반환합니다.
	 */
	static uint32_t GetStride()
	{
		return sizeof(VertexPositionTexture);
	}


	/**
	 * @brief 정점의 위치입니다.
	 */
	Vector3f position;


	/**
	 * @brief 정점의 텍스처 좌표입니다.
	 */
	Vector2f texture;
};


/**
 * @brief 위치와 법선 정보를 가진 정점(Vertex)입니다.
 */
struct VertexPositionNormal
{
	/**
	 * @brief 위치와 법선 정보를 가진 정점의 기본 생성자입니다.
	 */
	VertexPositionNormal() noexcept
		: position(0.0f, 0.0f, 0.0f)
		, normal(0.0f, 0.0f, 0.0f) {}


	/**
	 * @brief 위치와 법선 정보를 가진 정점의 생성자입니다.
	 *
	 * @param p 정점의 위치입니다.
	 * @param n 정점의 법선입니다.
	 */
	VertexPositionNormal(Vector3f&& p, Vector3f&& n) noexcept
		: position(p)
		, normal(n) {}


	/**
	 * @brief 위치와 법선 정보를 가진 정점의 생성자입니다.
	 *
	 * @param p 정점의 위치입니다.
	 * @param n 정점의 법선입니다.
	 */
	VertexPositionNormal(const Vector3f& p, const Vector3f& n) noexcept
		: position(p)
		, normal(n) {}


	/**
	 * @brief 위치와 법선 정보를 가진 정점의 생성자입니다.
	 *
	 * @param x 위치의 X좌표입니다.
	 * @param y 위치의 Y좌표입니다.
	 * @param z 위치의 Z좌표입니다.
	 * @param nx 법선의 X좌표입니다.
	 * @param ny 법선의 Y좌표입니다.
	 * @param nz 법선의 Z좌표입니다.
	 */
	VertexPositionNormal(
		float x, float y, float z,
		float nx, float ny, float nz
	) noexcept
		: position(x, y, z)
		, normal(nx, ny, nz) {}


	/**
	 * @brief 위치와 법선 정보를 가진 정점의 생성자입니다.
	 *
	 * @param instance 복사할 정점 인스턴스입니다.
	 */
	VertexPositionNormal(VertexPositionNormal&& instance) noexcept
		: position(instance.position)
		, normal(instance.normal) {}


	/**
	 * @brief 위치와 법선 정보를 가진 정점의 생성자입니다.
	 *
	 * @param instance 복사할 정점 인스턴스입니다.
	 */
	VertexPositionNormal(const VertexPositionNormal& instance) noexcept
		: position(instance.position)
		, normal(instance.normal) {}


	/**
	 * @brief 위치와 법선 정보를 가진 정점의 대입 연산자입니다.
	 *
	 * @param instance 대입할 정점 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	VertexPositionNormal& operator=(VertexPositionNormal&& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;
		normal = instance.normal;

		return *this;
	}


	/**
	 * @brief 위치와 법선 정보를 가진 정점의 대입 연산자입니다.
	 *
	 * @param instance 대입할 정점 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	VertexPositionNormal& operator=(const VertexPositionNormal& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;
		normal = instance.normal;

		return *this;
	}


	/**
	 * @brief 정점의 바이트 보폭 값을 얻습니다.
	 *
	 * @return 정점의 파이트 보폭(Stride) 값을 반환합니다.
	 */
	static uint32_t GetStride()
	{
		return sizeof(VertexPositionNormal);
	}


	/**
	 * @brief 정점의 위치입니다.
	 */
	Vector3f position;


	/**
	 * @brief 정점의 법선 좌표입니다.
	 */
	Vector3f normal;
};