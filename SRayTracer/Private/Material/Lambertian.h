#pragma once

#include "Material/Material.h"

class Lambertian : public IMaterial
{
public:
	Lambertian(const color& c)
		:mAlbedo(c)
	{}

	virtual bool Scatter(const Ray& inRay, const HitRecord& rec, color& attenuation, Ray& scattered) const override;
private:
	color mAlbedo;
};