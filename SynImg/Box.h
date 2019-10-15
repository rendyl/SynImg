#pragma once
#include <string>
#include "Sphere.h"
#include "Triangle.h"
#include "Vec3.h"

class Box
{
	public :
		Vec3 pt1;
		Vec3 pt2;
		
		// Object * obj;
		
		Sphere s;
		int indixSphere = -1;

		Triangle t;
		int indixTriangle = -1;

		std::string typeContained = "";

		Box();
		Box(Sphere s, int i);
		Box(Triangle s, int i);

		Box createBoxFromSphere(Sphere s, int i);
		Box createBoxFromTriangle(Triangle t, int i);

		Box unionBox(Box b);

		
};

