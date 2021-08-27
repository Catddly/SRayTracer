#pragma once

#include "Ray/IHittable.h"

interface IMaterial;

class alignas(64) Sphere : public IHittable
{
public:
	Sphere() = default;
	Sphere(point3 center, double radius, shared_ptr<IMaterial> pMat)
		:mCenter(center), mRadius(radius), mpMaterial(pMat)
	{}

	virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& rec) const override;
private:
	point3 mCenter;
	double mRadius;
	shared_ptr<IMaterial> mpMaterial;
};