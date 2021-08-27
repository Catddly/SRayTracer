#include "Lambertian.h"

#include "Ray/IHittable.h"

bool Lambertian::Scatter(const Ray& inRay, const HitRecord& rec, color& attenuation, Ray& scattered) const
{
	// three different diffuse calculate method
	// from top to bottom, the intensity of shadow decreasing 
	
	//vec3 scatterDirection = rec.normal + RandomUnitSphere(); // choose a random reflect point
	vec3 scatterDirection = rec.normal + RandomUnitVector(); 
	//vec3 scatterDirection = RandomUnitHemiSphere(rec.normal); 

	if (scatterDirection.near_zero()) // if the random unit vector is -normal
		scatterDirection = rec.normal;

	scattered = Ray(rec.p, scatterDirection);
	attenuation = mAlbedo;
	return true;
}
