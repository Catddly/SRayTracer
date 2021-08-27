#pragma once

#include "Base/Defs.h"
#include "Ray/Ray.h"

struct HitRecord;

interface IMaterial
{
	virtual ~IMaterial() = default;

	virtual bool Scatter(const Ray& inRay, const HitRecord& rec, color& attenuation, Ray& scattered) const = 0;
};