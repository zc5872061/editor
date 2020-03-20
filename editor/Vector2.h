#pragma once

namespace Editor
{
	class Vector2
	{
	public:
		Vector2() {}
		Vector2(float x, float y) { mX = x; mY = y;  }
		Vector2(int x, int y) { mX = (float)x; mY = (float)y; }
		explicit Vector2(const float *p) { mX = p[0]; mY = p[1]; }
		explicit Vector2(const float s) { mX = s; mY = s; }

		inline float getValue(int i) const { return *(&mX + i); }
		inline void setValue(int i, float value) { *(&mX + i) = value; }
		inline void setValue(float x, float y, float z) { mX = x; mY = y;  }

		void operator *=(const Vector2 &v) { mX *= v.mX; mY *= v.mY; }
		void operator /=(const Vector2 &v) { mX /= v.mX; mY /= v.mY;  }
		void operator +=(const Vector2 &v) { mX += v.mX; mY += v.mY;  }
		void operator -=(const Vector2 &v) { mX -= v.mX; mY -= v.mY;  }

		void operator *=(const float s) { mX *= s; mY *= s;  }
		void operator /=(const float s) { float temp = 1.0f / s; mX *= temp; mY *= temp;  }

		bool operator ==(const Vector2 &v) { return mX == v.mX && mY == v.mY ; }
		bool operator !=(const Vector2 &v) { return mX != v.mX || mY != v.mY ; }
		float mX, mY;

		static inline const Vector2&  zero() { return mZeroVector2; }
		static inline const Vector2& one() { return mOneVector2; }
	private:
		static Vector2 mZeroVector2;
		static Vector2 mOneVector2;
	};
}
