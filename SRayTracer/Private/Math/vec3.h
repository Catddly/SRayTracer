#pragma once

#include "Base/Defs.h"
#include "Base/Helpers.h"

#include <cmath>
#include <iostream>

using std::sqrt;

struct vec3 
{
	vec3()
		: e{ 0,0,0 } 
	{}
	vec3(double e0, double e1, double e2) 
		: e{ e0, e1, e2 } 
	{}

	inline double x() const { return e[0]; }
	inline double y() const { return e[1]; }
	inline double z() const { return e[2]; }

	inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

	inline double  operator[](int i) const { return e[i]; }
	inline double& operator[](int i)       { return e[i]; }

	inline vec3& operator+=(const vec3& v) 
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	inline vec3& operator*=(const double t) 
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	inline vec3& operator/=(const double t) 
	{
		return *this *= 1 / t;
	}

	inline double length() const 
	{
		return sqrt(length_squared());
	}

	inline double length_squared() const 
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	inline bool near_zero()
	{
		const double s = 1e-8;
		return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
	}

	inline static vec3 random() 
	{
		return vec3(Random(), Random(), Random());
	}

	inline static vec3 random(double min, double max) 
	{
		return vec3(Random(min, max), Random(min, max), Random(min, max));
	}
public:
	double e[3];
};

// aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color

// global utility functions
inline std::ostream& operator<<(std::ostream& out, const vec3& v) 
{
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) 
{
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) 
{
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) 
{
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) 
{
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) 
{
	return t * v;
}

inline vec3 operator/(vec3 v, double t) 
{
	return (1 / t) * v;
}

inline double Dot(const vec3& u, const vec3& v) 
{
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

inline vec3 Cross(const vec3& u, const vec3& v)
{
	return vec3(
		u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

/**
 * Return a reflected ray based on incidence ray and normal.
 * @param [in] - incidence ray.
 * @param [normal] - normal of the reflected surface.
 * @return a vec3 represent the reflect ray.
 */
inline vec3 Reflect(const vec3& in, const vec3& normal)
{
	return in - 2.0 * Dot(in, normal) * normal;
}

/**
 * Return a refract ray based on incidence ray, normal and the refractive ratio.
 * @param [in] - incidence ray.
 * @param [normal] - normal of the reflected surface.
 * @param [refractiveRatio] - n1 / n2 where n1 is the medium refractive index of upper surface and n2 is the lower surface.
 * @return a vec3 represent the refract ray.
 */
inline vec3 Refract(const vec3& in, const vec3& normal, double refractiveRatio)
{
	double cosTheta = fmin(Dot(-in, normal), 1.0);
	vec3   outPerp = refractiveRatio * (in + cosTheta * normal);
	vec3   outParallel = -sqrt(fabs(1.0 - outPerp.length_squared())) * normal;
	return outPerp + outParallel;
}

inline vec3 Normalize(vec3 v) 
{
	return v / v.length();
}

inline vec3 SafeNormalize(vec3 v, float tolerance = 1e-8)
{
	double length = v.length();
	if (length == 1.0)
		return v;
	if (length < tolerance)
		return vec3(0, 0, 0);
	return v / length;
}

inline vec3 RandomInUnitSphere()
{
	// rejection method
	while (true)
	{
		auto p = vec3::random(-1, 1);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}

inline vec3 RandomUnitHemiSphere(const vec3& normal) 
{
	vec3 in_unit_sphere = RandomInUnitSphere();
	if (Dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return in_unit_sphere;
	else
		return -in_unit_sphere;
}

inline vec3 RandomUnitVector()
{
	return Normalize(RandomInUnitSphere());
}

inline vec3 RandomInUnitDisk()
{
	while (true) 
	{
		auto p = vec3(Random(-1.0, 1.0), Random(-1.0, 1.0), 0.0);
		if (p.length_squared() >= 1.0) continue;
		return p;
	}
}