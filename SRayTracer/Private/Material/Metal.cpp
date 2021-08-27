#include "Metal.h"

#include "Ray/IHittable.h"

bool Metal::Scatter(const Ray& inRay, const HitRecord& rec, color& attenuation, Ray& scattered) const
{
	vec3 reflectRay = Reflect(Normalize(inRay.Direction()), rec.normal);
	scattered = Ray(rec.p, reflectRay + mFuzziness * RandomInUnitSphere());
	attenuation = mAlbedo;
	return (Dot(scattered.Direction(), rec.normal) > 0);
}
