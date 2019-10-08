#pragma once
#include "Sphere.h"
#include "Triangle.h"
#include "Vec3.h"

class Box
{
	public :
		Vec3 pt1;
		Vec3 pt2;
		Sphere s;
		int indixSphere = -1;

		Box();
		Box(Sphere s, int i);
		Box createBoxFromSphere(Sphere s, int i);

		Box unionBox(Box b);

		Box createBoxFromTriangle(Triangle t);
		
};

