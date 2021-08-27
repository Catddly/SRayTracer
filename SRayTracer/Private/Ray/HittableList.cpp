#include "HittableList.h"

bool HittableList::Hit(const Ray& ray, double tMin, double tMax, HitRecord& rec) const
{
	HitRecord tempRec;
	bool bHitAnything = false;
	double closest = tMax;

	for (const auto& e : mHittables)
	{
		if (e->Hit(ray, tMin, closest, tempRec))
		{
			bHitAnything = true;
			closest = tempRec.t;
			rec = tempRec;
		}
	}
	return bHitAnything;
}
