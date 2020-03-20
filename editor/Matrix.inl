namespace Editor
{
	void Matrix::loadIdentity()
	{
		mX.mX = 1.0f; mX.mY = 0.0f; mX.mZ = 0.0f; mX.mW = 0.0f;
		mY.mX = 0.0f; mY.mY = 1.0f; mY.mZ = 0.0f; mY.mW = 0.0f;
		mZ.mX = 0.0f; mZ.mY = 0.0f; mZ.mZ = 1.0f; mZ.mW = 0.0f;
		mT.mX = 0.0f; mT.mY = 0.0f; mT.mZ = 0.0f; mT.mW = 1.0f;
	}

	void Matrix::transpose()
	{
		Matrix out;

		out.mX.mX = mX.mX; out.mX.mY = mY.mX; out.mX.mZ = mZ.mX; out.mX.mW = mT.mX;
		out.mY.mX = mX.mY; out.mY.mY = mY.mY; out.mY.mZ = mZ.mY; out.mY.mW = mT.mY;
		out.mZ.mX = mX.mZ; out.mZ.mY = mY.mZ; out.mZ.mZ = mZ.mZ; out.mZ.mW = mT.mZ;
		out.mT.mX = mX.mW; out.mT.mY = mY.mW; out.mT.mZ = mZ.mW; out.mT.mW = mT.mW;

		*this = out;
	}

	void Matrix::invert()
	{
		float a0 = mX.mX*mY.mY - mX.mY*mY.mX;
		float a1 = mX.mX*mY.mZ - mX.mZ*mY.mX;
		float a2 = mX.mX*mY.mW - mX.mW*mY.mX;
		float a3 = mX.mY*mY.mZ - mX.mZ*mY.mY;
		float a4 = mX.mY*mY.mW - mX.mW*mY.mY;
		float a5 = mX.mZ*mY.mW - mX.mW*mY.mZ;
		float b0 = mZ.mX*mT.mY - mZ.mY*mT.mX;
		float b1 = mZ.mX*mT.mZ - mZ.mZ*mT.mX;
		float b2 = mZ.mX*mT.mW - mZ.mW*mT.mX;
		float b3 = mZ.mY*mT.mZ - mZ.mZ*mT.mY;
		float b4 = mZ.mY*mT.mW - mZ.mW*mT.mY;
		float b5 = mZ.mZ*mT.mW - mZ.mW*mT.mZ;

		float det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;


		Matrix tmp;
		tmp.mX.mX = +mY.mY*b5 - mY.mZ*b4 + mY.mW*b3;
		tmp.mY.mX = -mY.mX*b5 + mY.mZ*b2 - mY.mW*b1;
		tmp.mZ.mX = +mY.mX*b4 - mY.mY*b2 + mY.mW*b0;
		tmp.mT.mX = -mY.mX*b3 + mY.mY*b1 - mY.mZ*b0;
		tmp.mX.mY = -mX.mY*b5 + mX.mZ*b4 - mX.mW*b3;
		tmp.mY.mY = +mX.mX*b5 - mX.mZ*b2 + mX.mW*b1;
		tmp.mZ.mY = -mX.mX*b4 + mX.mY*b2 - mX.mW*b0;
		tmp.mT.mY = +mX.mX*b3 - mX.mY*b1 + mX.mZ*b0;
		tmp.mX.mZ = +mT.mY*a5 - mT.mZ*a4 + mT.mW*a3;
		tmp.mY.mZ = -mT.mX*a5 + mT.mZ*a2 - mT.mW*a1;
		tmp.mZ.mZ = +mT.mX*a4 - mT.mY*a2 + mT.mW*a0;
		tmp.mT.mZ = -mT.mX*a3 + mT.mY*a1 - mT.mZ*a0;
		tmp.mX.mW = -mZ.mY*a5 + mZ.mZ*a4 - mZ.mW*a3;
		tmp.mY.mW = +mZ.mX*a5 - mZ.mZ*a2 + mZ.mW*a1;
		tmp.mZ.mW = -mZ.mX*a4 + mZ.mY*a2 - mZ.mW*a0;
		tmp.mT.mW = +mZ.mX*a3 - mZ.mY*a1 + mZ.mZ*a0;

		float invDet = 1.0f / det;

		mX.mX = invDet * tmp.mX.mX;
		mX.mY = invDet * tmp.mX.mY;
		mX.mZ = invDet * tmp.mX.mZ;
		mX.mW = invDet * tmp.mX.mW;
		mY.mX = invDet * tmp.mY.mX;
		mY.mY = invDet * tmp.mY.mY;
		mY.mZ = invDet * tmp.mY.mZ;
		mY.mW = invDet * tmp.mY.mW;
		mZ.mX = invDet * tmp.mZ.mX;
		mZ.mY = invDet * tmp.mZ.mY;
		mZ.mZ = invDet * tmp.mZ.mZ;
		mZ.mW = invDet * tmp.mZ.mW;
		mT.mX = invDet * tmp.mT.mX;
		mT.mY = invDet * tmp.mT.mY;
		mT.mZ = invDet * tmp.mT.mZ;
		mT.mW = invDet * tmp.mT.mW;
	}

	Matrix	Matrix::operator *(const Matrix &mat) const
	{
		Matrix out;

		out.mX = mX.mX*mat.mX + mX.mY*mat.mY + mX.mZ*mat.mZ + mX.mW*mat.mT;

		return out;
	}

	void Matrix::operator *=(const Matrix &mat)
	{
		*this = *this*mat;
	}
}