#include "Dielectric.h"

#include "Ray/IHittable.h"

bool Dielectric::Scatter(const Ray& inRay, const HitRecord& rec, color& attenuation, Ray& scattered) const
{
	attenuation = color(1.0, 1.0, 1.0);
	double refractionRatio = rec.bIsFrontFace ? (1.0 / mIr) : mIr; // ir of air is 1.0

	vec3 nDirection = Normalize(inRay.Direction());

	double cosTheta = fmin(Dot(-nDirection, rec.normal), 1.0);
	double sinTheta = sqrt(1.0 - cosTheta * cosTheta);
	bool bCannotRefract = (refractionRatio * sinTheta > 1.0);
	vec3 direction;
	if (bCannotRefract || Reflectance(cosTheta, refractionRatio) > Random())
	{
		direction = Reflect(nDirection, rec.normal);
	}
	else
	{
		direction = Refract(nDirection, rec.normal, refractionRatio);
	}

	scattered = Ray(rec.p, direction);
	return true;
}

double Dielectric::Reflectance(double cosine, double reflectIdx)
{
	// use Schlick's Approximation for fresnel reflection(reflectance).
	double r0 = (1.0 - reflectIdx) / (1.0 + reflectIdx);
	r0 *= r0;
	return r0 + (1.0 - r0) * pow((1.0 - cosine), 5);
}
