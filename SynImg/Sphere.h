#pragma once
#include "Vec3.h"

class Sphere
{
	public :

		float rayon;
		Vec3 position;
		Vec3 couleur;
		float albedo;

		Sphere(float rayon, Vec3 pos, Vec3 col, float alb);
};

