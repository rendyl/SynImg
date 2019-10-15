#pragma once
#include "Vec3.h"

class Triangle //: public Object
{
	public :

		Vec3 vertice1;
		Vec3 vertice2;
		Vec3 vertice3;
		Vec3 normal;
		Vec3 couleur;
		float albedo;

		// float intersect(Rayon r) override;
		// Box createBoundingBox(int indice) override;

		Vec3 calculateNorm(Vec3 v1, Vec3 v2, Vec3 v3);

		Triangle();
		Triangle(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 couleur, float albedo);

		void display();
};

