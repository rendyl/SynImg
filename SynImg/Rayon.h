#pragma once
#include "Sphere.h"
#include "Box.h"
#include "TreeBox.h"
#include "Triangle.h"
#include <optional>
#include <iostream>
#include <math.h>

struct returnResult
{
	returnResult(float inter, int index)
	{
		intersect = inter;
		indexToSend = index;
	};

	float intersect;
	int indexToSend;
};

class Rayon
{
	public : 

		Vec3 position;
		Vec3 direction;
		Vec3 inv_direction;

		Rayon(Vec3 pos, Vec3 dir);
		float intersect(Sphere s);
		float intersect(Triangle t);
		float intersect(Box b);
		returnResult intersectTB(TreeBox * tb); 
};

