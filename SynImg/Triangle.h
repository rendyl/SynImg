#pragma once

#include "Vec3.h"

class Triangle
{
	public :
		Vec3 vertice1;
		Vec3 vertice2;
		Vec3 vertice3;
		Vec3 normal;

		void recalculateNorm();
};

