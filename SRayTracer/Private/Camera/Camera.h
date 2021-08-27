#pragma once

#include "Base/Defs.h"
#include "Math/vec3.h"

#include "Ray/Ray.h"

class Camera
{
public:
	Camera(point3 lookFrom, point3 lookAt, vec3 upVec, double fov, double aperture, double focusDist, double aspectRatio = ASPECT_RATIO)
	{
		double theta = Degrees2Radians(fov);
		double h = tan(theta / 2.0);
		double viewportHeight = 2.0 * h;
		double viewportWidth = aspectRatio * viewportHeight;

		// construct a coordinate system
		mW = Normalize(lookFrom - lookAt);
		mU = Normalize(Cross(upVec, mW));
		mV = Cross(mW, mU);

		mOrigin = lookFrom;
		mViewportHorizontal = viewportWidth * mU * focusDist;
		mViewportVertical = viewportHeight * mV * focusDist;
		mLowerLeftCorner = mOrigin - (mViewportHorizontal / 2) - (mViewportVertical / 2) - focusDist * mW;
		mLensRadius = aperture / 2.0;
	}

	/** 
	* Send a ray from this camera.
	* @param [u] - u of the viewport's texture coordinate.
	* @param [v] - v of the viewport's texture coordinate.
	* @return a ray.
	*/ 
	inline Ray SendRay(double s, double t) const 
	{
		vec3 rd = mLensRadius * RandomInUnitDisk();
		vec3 offset = mU * rd.x() + mV * rd.y();

		return Ray(mOrigin + offset, mLowerLeftCorner + s * mViewportHorizontal + t * mViewportVertical - mOrigin - offset);
	}

private:
	point3 mOrigin;
	point3 mLowerLeftCorner;
	vec3   mViewportHorizontal;
	vec3   mViewportVertical;
	vec3   mU, mV, mW;
	double mLensRadius;
};