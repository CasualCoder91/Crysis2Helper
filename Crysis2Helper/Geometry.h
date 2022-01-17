#pragma once

#include <stdint.h>
#include <imgui.h>

static const float PI = 3.14159265358979323846264338327950288419716939937510;
static const float PI2 = 3.14159265358979323846264338327950288419716939937510 * 2.0;

struct Vec4 {
	float x, y, z, w;

	Vec4(float x = 0, float y = 0, float z = 0, float w = 0) : x(x), y(y), z(z), w(w) { }
};

struct Matrix44 {
	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;
	float m30, m31, m32, m33;
};

inline Vec4 operator*(const Matrix44& m, const Vec4& v)
{
	return Vec4(v.x * m.m00 + v.y * m.m01 + v.z * m.m02 + v.w * m.m03,
		v.x * m.m10 + v.y * m.m11 + v.z * m.m12 + v.w * m.m13,
		v.x * m.m20 + v.y * m.m21 + v.z * m.m22 + v.w * m.m23,
		v.x * m.m30 + v.y * m.m31 + v.z * m.m32 + v.w * m.m33);
}

inline Matrix44 operator * (const Matrix44& l, const Matrix44& r)
{
	Matrix44 res;
	res.m00 = l.m00 * r.m00 + l.m01 * r.m10 + l.m02 * r.m20 + l.m03 * r.m30;
	res.m10 = l.m10 * r.m00 + l.m11 * r.m10 + l.m12 * r.m20 + l.m13 * r.m30;
	res.m20 = l.m20 * r.m00 + l.m21 * r.m10 + l.m22 * r.m20 + l.m23 * r.m30;
	res.m30 = l.m30 * r.m00 + l.m31 * r.m10 + l.m32 * r.m20 + l.m33 * r.m30;
	res.m01 = l.m00 * r.m01 + l.m01 * r.m11 + l.m02 * r.m21 + l.m03 * r.m31;
	res.m11 = l.m10 * r.m01 + l.m11 * r.m11 + l.m12 * r.m21 + l.m13 * r.m31;
	res.m21 = l.m20 * r.m01 + l.m21 * r.m11 + l.m22 * r.m21 + l.m23 * r.m31;
	res.m31 = l.m30 * r.m01 + l.m31 * r.m11 + l.m32 * r.m21 + l.m33 * r.m31;
	res.m02 = l.m00 * r.m02 + l.m01 * r.m12 + l.m02 * r.m22 + l.m03 * r.m32;
	res.m12 = l.m10 * r.m02 + l.m11 * r.m12 + l.m12 * r.m22 + l.m13 * r.m32;
	res.m22 = l.m20 * r.m02 + l.m21 * r.m12 + l.m22 * r.m22 + l.m23 * r.m32;
	res.m32 = l.m30 * r.m02 + l.m31 * r.m12 + l.m32 * r.m22 + l.m33 * r.m32;
	res.m03 = l.m00 * r.m03 + l.m01 * r.m13 + l.m02 * r.m23 + l.m03 * r.m33;
	res.m13 = l.m10 * r.m03 + l.m11 * r.m13 + l.m12 * r.m23 + l.m13 * r.m33;
	res.m23 = l.m20 * r.m03 + l.m21 * r.m13 + l.m22 * r.m23 + l.m23 * r.m33;
	res.m33 = l.m30 * r.m03 + l.m31 * r.m13 + l.m32 * r.m23 + l.m33 * r.m33;
	return res;
}


struct Vector2 {
	float x, y;
};

struct Vec3 {
	float x, y, z;

	Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) { }

	void Normalize()
	{
		float len = sqrtf(x * x + y * y + z * z);
		if (len != 0) {
			x /= len;
			y /= len;
			z /= len;
		}
	}

	Vec3 cross(const Vec3& other) {
		return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
	}

	Vec3 Abs() 
	{
		return Vec3(abs(x), abs(y), abs(z));
	}

	const float GetLength() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	Vec3 operator + (const Vec3& v1) const
	{
		return Vec3(x + v1.x, y + v1.y, z + v1.z);
	}


	Vec3 operator - (const Vec3& v1) const
	{
		return Vec3(x - v1.x, y - v1.y, z - v1.z);
	}

	Vec3 operator * (const float k) const
	{
		return Vec3(k * x, k * y, k * z);
	}

	Vec3 operator / (const float k) const
	{
		return Vec3(x / k, y / k, z / k);
	}

	operator ImVec2() const { return ImVec2(x,y); }

};

struct Matrix34 {
	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;

	Vec3 GetColumn0() {
		return(Vec3(m00, m10, m20));
	}

	Vec3 GetColumn1() {
		return(Vec3(m01, m11, m21));
	}

	Vec3 GetColumn2() {
		return(Vec3(m02, m12, m22));
	}

	Vec3 GetColumn3() {
		return(Vec3(m03, m13, m23));
	}
};

struct AABB
{
	Vec3 min;
	Vec3 max;

	AABB() {}

	AABB(const Vec3& vmin, const Vec3& vmax)
	{
		min = vmin; max = vmax;
	}

	inline Vec3 GetCenter() const
	{
		return (min + max) * 0.5f;
	}

	inline Vec3 GetSize() const
	{
		return (max - min).Abs();
	}


};

struct ColorB //[0, 255]
{
	uint8_t r, g, b, a;
};

struct ColorF
{
	float r, g, b, a;
};