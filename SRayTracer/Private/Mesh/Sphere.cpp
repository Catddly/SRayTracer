#include "Sphere.h"

bool Sphere::Hit(const Ray& ray, double tMin, double tMax, HitRecord& rec) const
{
	vec3 oc = ray.Origin() - mCenter;
	double a = ray.Direction().length_squared();
	double half_b = Dot(oc, ray.Direction());
	double c = oc.length_squared() - mRadius * mRadius;
	double discriminant = half_b * half_b - a * c;

	if (discriminant < 0.0f)
		return false;
	double sqrtDiscriminant = sqrt(discriminant);
	double root = (-half_b - sqrtDiscriminant) / a;

	// find the nearest t in the acceptable range
	if (root < tMin || tMax < root) // exceed the range
	{
		root = (-half_b + sqrtDiscriminant) / a; // find the bigger t
		if (root < tMin || tMax < root)
			return false;
	}

	rec.t = root;
	rec.p = ray.At(rec.t);
	vec3 N = (rec.p - mCenter) / mRadius;
	rec.SetFaceNormal(ray, N);
	rec.pMaterial = mpMaterial;
	return true;
}
