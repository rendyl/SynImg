#pragma once

#include "Vec3.h"

class Triangle
{
	public :
		Vec3 vertice1;
		Vec3 vertice2;
		Vec3 vertice3;
		Vec3 normal;


		Triangle(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 n);
		void recalculateNorm();
};

