#pragma once
#include "Math.h"

namespace Editor
{
	class Vector3
	{
	public:
		Vector3() {}
		Vector3(float x, float y, float z) { mX = x; mY = y; mZ = z; }
		Vector3(int x, int y, int z) { mX = (float)x; mY = (float)y; mZ = (float)z; }
		explicit Vector3(const float *p) { mX = p[0]; mY = p[1]; mZ = p[2]; }
		explicit Vector3(const float s) { mX = s; mY = s; mZ = s; }

		inline float getValue(int i) const { return *(&mX + i); }
		inline void setValue(int i, float value) { *(&mX + i) = value; }
		inline void setValue(float x, float y, float z) { mX = x; mY = y; mZ = z; }

		void operator *=(const Vector3 &v) { mX *= v.mX; mY *= v.mY; mZ *= v.mZ; }
		void operator /=(const Vector3 &v) { mX /= v.mX; mY /= v.mY; mZ /= v.mZ; }
		void operator +=(const Vector3 &v) { mX += v.mX; mY += v.mY; mZ += v.mZ; }
		void operator -=(const Vector3 &v) { mX -= v.mX; mY -= v.mY; mZ -= v.mZ; }

		void operator *=(const float s) { mX *= s; mY *= s; mZ *= s; }
		void operator /=(const float s) { float temp = 1.0f / s; mX *= temp; mY *= temp; mZ *= temp; }

		bool operator ==(const Vector3 &v) { return mX == v.mX && mY == v.mY && mZ == v.mZ; }
		bool operator !=(const Vector3 &v) { return mX != v.mX || mY != v.mY || mZ != v.mZ; }
		float mX, mY, mZ;

		static inline const Vector3&  zero() { return mZeroVector3; }
		static inline const Vector3& one() { return mOneVector3; }
		inline float magSquared() const { return mX * mX + mY * mY + mZ * mZ; }
		inline float mag() const { return Sqrt(magSquared()); }
		inline Vector3 normal() const;
	private:
		static Vector3 mZeroVector3;
		static Vector3 mOneVector3;
	};

	inline Vector3 operator *(float f, const Vector3 &v) { return Vector3(v.mX*f, v.mY*f, v.mZ*f); }
	inline Vector3 operator *(const Vector3 &v, float f) { return Vector3(v.mX*f, v.mY*f, v.mZ*f); }
	inline Vector3 operator /(const Vector3 &v, float f) { return Vector3(v.mX / f, v.mY / f, v.mZ / f); }

	inline Vector3 operator *(const Vector3 &v1, const Vector3 &v2) { return Vector3(v1.mX*v2.mX, v1.mY*v2.mY, v1.mZ*v2.mZ); }
	inline Vector3 operator /(const Vector3 &v1, const Vector3 &v2) { return Vector3(v1.mX / v2.mX, v1.mY / v2.mY, v1.mZ / v2.mZ); }
	inline Vector3 operator +(const Vector3 &v1, const Vector3 &v2) { return Vector3(v1.mX + v2.mX, v1.mY + v2.mY, v1.mZ + v2.mZ); }
	inline Vector3 operator -(const Vector3 &v1, const Vector3 &v2) { return Vector3(v1.mX - v2.mX, v1.mY - v2.mY, v1.mZ - v2.mZ); }

	inline Vector3 operator -(const Vector3 &v) { return Vector3(-v.mX, -v.mY, -v.mZ); }

	inline Vector3 Cross(const Vector3 &a, const Vector3 &b)
	{
		return Vector3(a.mY*b.mZ - b.mY*a.mZ, b.mX*a.mZ - a.mX*b.mZ, a.mX*b.mY - b.mX*a.mY);
	}

	inline Vector3 Vector3::normal() const
	{
		return (*this) / mag();
	}
}
