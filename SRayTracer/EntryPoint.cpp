#include "Math/vec3.h"
#include "Math/color.h"

#include "Ray/Ray.h"

#include "Mesh/Sphere.h"
#include "Ray/HittableList.h"
#include "Camera/Camera.h"
#include "Material/Material.h"
#include "Material/Lambertian.h"
#include "Material/Metal.h"
#include "Material/Dielectric.h"

#include "Base/Helpers.h"

#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <map>

/// quality settings
const int SAMPLE_PER_PIXEL = 50;
const int MAX_BOUNCING_DEPTH = 60;

HittableList random_scene()
{
	HittableList world;

	auto ground_material = std::make_shared<Lambertian>(color(0.5, 0.5, 0.5));
	world.Append(std::make_shared<Sphere>(point3(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			auto choose_mat = Random();
			point3 center(a + 0.9 * Random(), 0.2, b + 0.9 * Random());

			if ((center - point3(4, 0.2, 0)).length() > 0.9)
			{
				shared_ptr<IMaterial> sphere_material;

				if (choose_mat < 0.8)
				{
					// diffuse
					auto albedo = color::random() * color::random();
					sphere_material = std::make_shared<Lambertian>(albedo);
					world.Append(std::make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95)
				{
					// metal
					auto albedo = color::random(0.5, 1);
					auto fuzz = Random(0, 0.5);
					sphere_material = std::make_shared<Metal>(albedo, fuzz);
					world.Append(std::make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else
				{
					// glass
					sphere_material = std::make_shared<Dielectric>(1.5);
					world.Append(std::make_shared<Sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = std::make_shared<Dielectric>(1.5);
	world.Append(std::make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = std::make_shared<Lambertian>(color(0.4, 0.2, 0.1));
	world.Append(std::make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = std::make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0);
	world.Append(std::make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));

	return std::move(world);
}

/// world settings
HittableList world = random_scene();

/// camera settings
point3 lookfrom(13, 2, 3);
point3 lookat(0, 0, 0);
vec3 upVec(0, 1, 0);
auto distToFocus = 10.0;
auto aperture = 0.1;
Camera camera(lookfrom, lookat, upVec, 20, aperture, distToFocus);

//std::mutex gMutex;
//
//struct ColorBuffer
//{
//	uint8_t pBuf[WIDTH * 3] = {};
//};
//
//std::map<int, ColorBuffer> mColorBuffers;

color RayColor(const Ray& r, const HittableList& world, int depth)
{
	if (depth <= 0) // exceed the ray bouncing limits
		return color(0, 0, 0);

	HitRecord rec;
	if (world.Hit(r, 0.001, T_INFINITY, rec))
	{
		Ray   scattered;
		color attenuation; // accumulate the scatter ray's color
		if (rec.pMaterial->Scatter(r, rec, attenuation, scattered)) // ray continue the bouncing
			return attenuation * RayColor(scattered, world, depth - 1);
		return color(0, 0, 0);
	}

	// background color
	vec3 nDirect = Normalize(r.Direction());
	// calculate a gradient
	double t = 0.5 * (nDirect.y() + 1.0); // make the y positive
	return Lerp(t, COLOR_LIGHTBLUE, COLOR_WHITE);
}

//static void _ThreadFunc(int y)
//{
//	ColorBuffer cb;
//	int offset = 0;
//	for (int x = 0; x < WIDTH; x++)
//	{
//		color pixel(0, 0, 0);
//		for (int s = 0; s < SAMPLE_PER_PIXEL; s++)
//		{
//			// texcoord of the viewport, define which pixel is currently sampling
//			// random sample in the pixel
//			auto u = double(x + Random()) / ((double)WIDTH - 1);
//			auto v = double(y + Random()) / ((double)HEIGHT - 1);
//
//			Ray	ray = camera.SendRay(u, v);
//			pixel += RayColor(ray, world, MAX_BOUNCING_DEPTH);
//		}
//		WriteBufferColor(&cb.pBuf[0], pixel, SAMPLE_PER_PIXEL);
//		offset += 3;
//	}
//
//	{
//		std::lock_guard<std::mutex> lck(gMutex);
//		mColorBuffers[y] = cb;
//	}
//}

int main()
{
	/// material settings
	//auto matGround = std::make_shared<Lambertian>(color(0.2, 0.86, 0.47));
	//auto matCenter = std::make_shared<Lambertian>(color(0.88, 0.54, 0.72));
	//auto matCenter = std::make_shared<Dialectric>(1.5);
	//auto matLeft = std::make_shared<Metal>(color(0.85, 0.85, 0.85), 0.2);
	//auto matLeft = std::make_shared<Dielectric>(1.5);
	//auto matRight = std::make_shared<Metal>(color(0.32, 0.58, 0.86), 0.65);

	/// world settings
	//HittableList world = random_scene();
	//world.Append(std::make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100.0, matGround));
	//world.Append(std::make_shared<Sphere>(point3(0.0, 0.0, -1.0), 0.5, matCenter));
	//world.Append(std::make_shared<Sphere>(point3(-1.0, 0.0, -1.0), 0.5, matLeft));
	//world.Append(std::make_shared<Sphere>(point3(-1.0, 0.0, -1.0), -0.45, matLeft));
	//world.Append(std::make_shared<Sphere>(point3(1.0, 0.0, -1.0), 0.5, matRight));

	/// camera settings
	//point3 lookfrom(13, 2, 3);
	//point3 lookat(0, 0, 0);
	//vec3 upVec(0, 1, 0);
	//auto distToFocus = 10.0;
	//auto aperture = 0.1;
	//Camera camera(lookfrom, lookat, upVec, 20, aperture, distToFocus);

	//std::thread threads[32];
	//for (int i = 0; i < 32; i++)
	//{
	//	threads[i] = std::thread(_ThreadFunc, 1);
	//}

	/// write out as image
	// header of PPM image
	std::cout << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";
	// write out pixel data
	for (int y = HEIGHT - 1; y >= 0; y--)
	{
		std::cerr << "\rScanlines remaining: " << y << "\n" << std::flush;
		for (int x = 0; x < WIDTH; x++)
		{
			color pixel(0, 0, 0);
			for (int s = 0; s < SAMPLE_PER_PIXEL; s++)
			{
				// texcoord of the viewport, define which pixel is currently sampling
				// random sample in the pixel
				auto u = double(x + Random()) / ((double)WIDTH - 1);
				auto v = double(y + Random()) / ((double)HEIGHT - 1);

				pixel += RayColor(camera.SendRay(u, v), world, MAX_BOUNCING_DEPTH);
			}
			WriteOutColor(std::cout, pixel, SAMPLE_PER_PIXEL);
		}
	}
	
	std::cerr << "\nDone.\n";
}