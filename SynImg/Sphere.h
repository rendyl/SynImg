#pragma once
#include "Vec3.h"

class Sphere //: public Object
{
	public :

		float rayon;
		Vec3 position;
		Vec3 couleur;
		float albedo;

		// float intersect(Rayon r) override;
		// Box createBoundingBox(int indice) override;

		Sphere();
		Sphere(float rayon, Vec3 pos, Vec3 col, float alb);
};

