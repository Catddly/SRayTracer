#pragma once

#include "Base/Defs.h"

#include <random>

template <class T>
T Lerp(double factor, const T& min, const T& max)
{
	return (1.0 - factor) * min + factor * max;
}

template <class T>
T Clamp(T v, T min, T max)
{
	if (v < min) return min;
	if (max < v) return max;
	return v;
}

inline double Degrees2Radians(double degrees)
{
	return degrees * PI / 180.0f;
}

/// Returns a random real in [0,1).
inline double Random() 
{
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}

/// Returns a random real in [min,max).
inline double Random(double min, double max) 
{
	return min + (max - min) * Random();
}