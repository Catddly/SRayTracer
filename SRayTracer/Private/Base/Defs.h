#pragma once

#include <limits>

#define T_INFINITY std::numeric_limits<double>::infinity()
#define PI         3.1415926535897932385f

#include "Math/vec3.h"

#define COLOR_WHITE     color(1.0f, 1.0f, 1.0f)
#define COLOR_LIGHTBLUE color(0.5f, 0.7f, 1.0f)

#define ASPECT_RATIO (3.0 / 2.0)
#define WIDTH  600
#define HEIGHT (int)(WIDTH / ASPECT_RATIO)

#define SMALL_NUMBER 1e-8

#ifndef interface
#define __STRUCT__ struct
#define interface __STRUCT__
#endif