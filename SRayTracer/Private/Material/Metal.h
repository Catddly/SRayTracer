#pragma once

#include "Material/Material.h"

class Metal : public IMaterial 
{
public:
	Metal(const color& a, float fuzziness) 
		: mAlbedo(a), mFuzziness(fuzziness)
	{}

	virtual bool Scatter(const Ray& inRay, const HitRecord& rec, color& attenuation, Ray& scattered) const override;
public:
	color mAlbedo;
	float mFuzziness; //! < It is the roughness ?
};