#pragma once

namespace Editor
{
	class Vector4
	{
	public:
		Vector4() {}
		Vector4(float x, float y, float z, float w) { mX = x; mY = y; mZ = z; mW = w; }
		Vector4(int x, int y, int z,int w) { mX = (float)x; mY = (float)y; mZ = (float)z; mW = (float)w; }
		explicit Vector4(const float *p) { mX = p[0]; mY = p[1]; mZ = p[2]; mW = p[3]; }
		explicit Vector4(const float s) { mX = s; mY = s; mZ = s; mW = s; }

		inline float getValue(int i) const { return *(&mX + i); }
		inline void setValue(int i, float value) { *(&mX + i) = value; }
		inline void setValue(float x, float y, float z,float w) { mX = x; mY = y; mZ = z; mW = w; }

		void operator *=(const Vector4 &v) { mX *= v.mX; mY *= v.mY; mZ *= v.mZ;  mW *= v.mW; }
		void operator /=(const Vector4 &v) { mX /= v.mX; mY /= v.mY; mZ /= v.mZ; mW /= v.mW; }
		void operator +=(const Vector4 &v) { mX += v.mX; mY += v.mY; mZ += v.mZ;  mW += v.mW; }
		void operator -=(const Vector4 &v) { mX -= v.mX; mY -= v.mY; mZ -= v.mZ; mW -= v.mW; }

		void operator *=(const float s) { mX *= s; mY *= s; mZ *= s; mW *= s; }
		void operator /=(const float s) { float temp = 1.0f / s; mX *= temp; mY *= temp; mZ *= temp; mW *= temp; }

		bool operator ==(const Vector4 &v) { return mX == v.mX && mY == v.mY && mZ == v.mZ && mW == v.mW; }
		bool operator !=(const Vector4 &v) { return mX != v.mX || mY != v.mY || mZ != v.mZ || mW != v.mW; }
		float mX, mY, mZ, mW;

		static inline const Vector4&  zero() { return mZeroVector4; }
		static inline const Vector4& one() { return mOneVector4; }
		
	private:
		static Vector4 mZeroVector4;
		static Vector4 mOneVector4;
	};

	inline Vector4 operator *(float f, const Vector4 &v) { return Vector4(v.mX*f, v.mY*f, v.mZ*f, v.mW*f); }
	inline Vector4 operator +(const Vector4 &v1, const Vector4 &v2) { return Vector4(v1.mX + v2.mX, v1.mY + v2.mY, v1.mZ + v2.mZ, v1.mW + v2.mW); }
}
