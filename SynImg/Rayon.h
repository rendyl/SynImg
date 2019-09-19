#pragma once
#include "Sphere.h"
#include <optional>
#include <iostream>
#include <math.h>

class Rayon
{
	public : 

		Vec3 position;
		Vec3 direction;

		Rayon(Vec3 pos, Vec3 dir);
		float intersect(Sphere s);
};

