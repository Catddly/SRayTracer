#pragma once

#include "Math/vec3.h"

class Ray
{
public:
	Ray() {}
	Ray(const point3& origin, const vec3& direction)
		: mOrigin(origin), mDirection(direction)
	{}

	inline point3 Origin()    const { return mOrigin; }
	inline vec3   Direction() const { return mDirection; }

	inline point3 At(double t) const
	{
		return mOrigin + mDirection * t;
	}
private:
	point3 mOrigin;
	vec3   mDirection;
};