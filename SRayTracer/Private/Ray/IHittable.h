#pragma once

#include "Base/Defs.h"
#include "Ray.h"

#include <memory>

using std::shared_ptr;

interface IMaterial;

//! The hit data of a ray.
struct HitRecord
{
	point3 p = { 0.0, 0.0, 0.0 };
	vec3   normal = { 0.0, 0.0, 0.0 };
	double t = -1.0f;
	bool   bIsFrontFace = true;

	shared_ptr<IMaterial> pMaterial;

	inline void SetFaceNormal(const Ray& r, const vec3& N)
	{
		bIsFrontFace = (Dot(r.Direction(), N) < 0.0);
		normal = bIsFrontFace ? N : -N;
	}
};

//! Any ray hittable object.
interface IHittable
{
	virtual ~IHittable() = default;

	virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& rec) const = 0;
};