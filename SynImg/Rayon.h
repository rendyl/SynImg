#pragma once
#include "Sphere.h"
#include "Box.h"
#include "Triangle.h"
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
		float intersect(Triangle t);
		float intersect(Box b);
};

