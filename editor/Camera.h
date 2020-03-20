#pragma once
#include "Vector3.h"
#include "Matrix.h"
#include "Math.h"

namespace Editor
{
	class Camera
	{
	public:
		Camera();

		void		setProjMatrixHorz(float fFovHorz, float fAspectRatio,float fNear,float fFar,bool bUpdateFrustum = true);
		void		setProjMatrixVert(float fFovVert, float fAspectRatio, float fNear, float fFar, bool bUpdateFrustum = true);
		void		setViewMatrix(const Vector3 &vEye, const Vector3 &vTarget, const Vector3 &vUp);
	public:
		Vector3		mEyePosition;
		Vector3		mTargetPosition;
		Matrix		mProjMatrix;
		Matrix		mViewMatrix;
		Matrix		mViewProjMatrix;
		Matrix		mInverseViewMatrix;
		float		mFovHorz;
		float		mFovVert;
		float		mAspectRatio;
		float		mNearPlane;
		float		mFarPlane;
		float		mTanHalfFovHorz;
		float		mTanHalfFovVert;
	};
}