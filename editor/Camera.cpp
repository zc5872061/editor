#include "Camera.h"

namespace Editor
{
	Camera::Camera():
		mEyePosition(0,0,0),
		mTargetPosition(0,0,0),
		mFovHorz(0),
		mFovVert(0),
		mAspectRatio(1),
		mNearPlane(1),
		mFarPlane(2)
	{
		mProjMatrix.loadIdentity();
		mViewMatrix.loadIdentity();
		mViewProjMatrix.loadIdentity();
		mInverseViewMatrix.loadIdentity();
	}

	void Camera::setProjMatrixHorz(float fFovHorz, float fAspectRatio, float fNear, float fFar, bool bUpdateFrustum )
	{
		mFovHorz = fFovHorz;
		mAspectRatio = fAspectRatio;
		mNearPlane = fNear;
		mFarPlane = fFar;

		mTanHalfFovHorz = Tan(0.5f * mFovHorz);
		mTanHalfFovVert = mTanHalfFovHorz / fAspectRatio;

		mFovVert = 2.0f*ATan(mTanHalfFovVert);

		float fScaleX = 1.0f / mTanHalfFovHorz;
		float fScaleY = 1.0f / mTanHalfFovVert;
		float fQ = fFar / (fNear - fFar);

		mProjMatrix = Matrix(
			Vector4(fScaleX, 0.0f, 0.0f, 0.0f),
			Vector4(0.0f, fScaleY, 0.0, 0.0),
			Vector4(0.0f, 0.0f, fQ, -1.0f),
			Vector4(0.0f, 0.0f, fNear*fQ, 0.0f)
		);

		mViewProjMatrix = mViewMatrix * mProjMatrix;

		if (bUpdateFrustum)
		{
			//updateFrustum();
		}

		//mScreenShotScale = 1.0f;
	}

	void Camera::setProjMatrixVert(float fFovVert, float fAspectRatio, float fNear, float fFar, bool bUpdateFrustum)
	{
		mFovVert = fFovVert;
		mAspectRatio = fAspectRatio;
		mNearPlane = fNear;
		mFarPlane = fFar;

		mTanHalfFovVert = Tan(0.5f*fFovVert);
		mTanHalfFovHorz = mTanHalfFovVert * fAspectRatio;

		mFovHorz = 2.0f*ATan(mTanHalfFovHorz);

		float fScaleX = 1.0f / mTanHalfFovHorz;
		float fScaleY = 1.0f / mTanHalfFovVert;
		float fQ = fFar / (fNear - fFar);

		mProjMatrix = Matrix(
			Vector4(fScaleX, .0f, .0, .0),
			Vector4(.0, fScaleY, .0, .0),
			Vector4(.0, .0, fQ, -1.0),
			Vector4(.0, .0, fNear*fQ, .0)
		);

		mViewProjMatrix = mViewMatrix * mProjMatrix;

		/*if (bUpdateFrustum)
		{
			updateFrustum();
		}

		mScreenShotScale = 1.0f;*/
	}

	void Camera::setViewMatrix(const Vector3 &vEye, const Vector3 &vTarget, const Vector3 &vUp)
	{
		Vector3 vAxisForward = (vTarget - vEye);
		Vector3 vAxisRight = Cross(vAxisForward, vUp);
		Vector3 vAxisUp = Cross(vAxisRight, vAxisForward);

		if (vAxisForward.magSquared() < FLT_EPSILON || vAxisRight.magSquared() < FLT_EPSILON || vAxisUp.magSquared() < FLT_EPSILON)
		{
			vAxisRight = Vector3(1, 0, 0);
			vAxisForward = Vector3(0, 1, 0);
			vAxisUp = Vector3(0, 0, 1);
		}

		vAxisRight = vAxisRight.normal();
		vAxisForward = vAxisForward.normal();
		vAxisUp = vAxisUp.normal();

		mInverseViewMatrix.loadIdentity();
		mInverseViewMatrix.setAxisX(vAxisRight);
		mInverseViewMatrix.setAxisY(vAxisUp);
		mInverseViewMatrix.setAxisZ(-vAxisForward);
		mInverseViewMatrix.setTrans(vEye);

		mViewMatrix = mInverseViewMatrix;
		mViewMatrix.invert();

		mViewProjMatrix = mViewMatrix * mProjMatrix;
		mEyePosition = vEye;
		mTargetPosition = vTarget;

		/*mTransform.loadIdentity();
		mTransform.setAxisX(vAxisRight);
		mTransform.setAxisY(vAxisForward);
		mTransform.setAxisZ(vAxisUp);
		mTransform.setTrans(vEye);

		updateFrustum();*/
	}
}