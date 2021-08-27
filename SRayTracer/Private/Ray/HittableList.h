#pragma once

#include "IHittable.h"

#include <memory>
#include <vector>

using std::vector;
using std::shared_ptr;

//! List of the hittable objects
class HittableList : public IHittable
{
public:
	HittableList() = default;
	HittableList(shared_ptr<IHittable> object) 
	{ 
		Append(object); 
	}

	void Clear() { mHittables.clear(); }
	void Append(shared_ptr<IHittable> object) { mHittables.emplace_back(object); }

	virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& rec) const override;
private:
	vector<shared_ptr<IHittable>> mHittables;
};