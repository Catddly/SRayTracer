#pragma once

#include "Material/Material.h"

class Dielectric : public IMaterial
{
public:
	Dielectric(double indexOfRefraction)
		:mIr(indexOfRefraction)
	{}

	virtual bool Scatter(const Ray& inRay, const HitRecord& rec, color& attenuation, Ray& scattered) const override;
protected:
	static double Reflectance(double cosine, double reflectIdx);
private:
	double mIr;
};