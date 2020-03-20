#pragma once

#include "Vector3.h"

namespace Editor
{
	class Aabb
	{
	public:
		Aabb(const Vector3& min,const Vector3& max):mMin(min),mMax(max){}
	public:
		Vector3 mMin;
		Vector3 mMax;
	};
}