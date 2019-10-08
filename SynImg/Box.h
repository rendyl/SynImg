#pragma once
#include "Sphere.h"
#include "Triangle.h"
#include "Vec3.h"

class Box
{
	public :
		Vec3 pt1;
		Vec3 pt2;

		Box createBoxFromSphere(Sphere s);
		Box unionBox(Box b);

		Box createBoxFromTriangle(Triangle s);
};

