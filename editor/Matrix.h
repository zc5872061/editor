#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace Editor
{
	class Matrix
	{
	public:
		Matrix() {}
		Matrix(const Vector4& vX, const Vector4& vY, const Vector4& vZ, const Vector4& vT) { mX = vX; mY = vY; mZ = vZ; mT = vT; }
		
		inline void setAxis(int i,const Vector3& v) { (&mX + i)->mX = v.mX; (&mX + i)->mY = v.mY; (&mZ + i)->mZ = v.mZ; }
		inline void setAxisX(const Vector3& v) { mX.mX = v.mX; mX.mY = v.mY; mX.mZ = v.mZ; }
		inline void setAxisY(const Vector3& v) { mY.mX = v.mX; mY.mY = v.mY; mY.mZ = v.mZ; }
		inline void setAxisZ(const Vector3& v) { mZ.mX = v.mX; mZ.mY = v.mY; mZ.mZ = v.mZ; }
		inline void setTrans(const Vector3& v) { mT.mX = v.mX; mT.mY = v.mY; mT.mZ = v.mZ; }

		inline const Vector3& getAxis(int i) const { return (const Vector3&)*(&mX + i); }

		inline void loadIdentity();
		inline void transpose();
		inline void invert();

		static inline const Matrix& identity() { return mIdentityMatrix; }

		inline Matrix			operator *(const Matrix &mat) const;
		inline void				operator *=(const Matrix &mat);
	public:
		Vector4 mX;
		Vector4 mY;
		Vector4 mZ;
		Vector4 mT;
	private:
		static Matrix mIdentityMatrix;
	};
}

#include "Matrix.inl"