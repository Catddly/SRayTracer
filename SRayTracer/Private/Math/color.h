#pragma once

#include "Base/Helpers.h"
#include "vec3.h"

#include <iostream>
#include <cmath>

void WriteOutColor(std::ostream& out, const color& c, int samplesPerPixel)
{
	double r = c.x();
	double g = c.y();
	double b = c.z();

	// average the color by the number of samples
	double scalar = 1.0 / samplesPerPixel;
	r = sqrt(r * scalar);
	g = sqrt(g * scalar);
	b = sqrt(b * scalar);

	out << static_cast<int>(256 * Clamp(r, 0.0, 0.9999)) << ' '
		<< static_cast<int>(256 * Clamp(g, 0.0, 0.9999)) << ' '
		<< static_cast<int>(256 * Clamp(b, 0.0, 0.9999)) << '\n';
}

void WriteBufferColor(uint8_t* pBuf, const color& c, int samplesPerPixel)
{
	double r = c.x();
	double g = c.y();
	double b = c.z();

	// average the color by the number of samples
	double scalar = 1.0 / samplesPerPixel;
	r = sqrt(r * scalar);
	g = sqrt(g * scalar);
	b = sqrt(b * scalar);
	
	*pBuf = static_cast<int>(256 * Clamp(r, 0.0, 0.9999));
	*(pBuf + 1) = static_cast<int>(256 * Clamp(g, 0.0, 0.9999));
	*(pBuf + 2) = static_cast<int>(256 * Clamp(b, 0.0, 0.9999));
}