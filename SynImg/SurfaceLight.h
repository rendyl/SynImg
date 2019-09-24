#pragma once
#include <vector>
#include "Sphere.h"

class SurfaceLight
{
	public :
		int nbLights;
		Vec3 position;
		Vec3 dimension;
		Vec3 color;

		SurfaceLight();
		SurfaceLight(int nb, Vec3 pos, Vec3 dim, Vec3 col);
};

