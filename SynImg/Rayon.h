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
	returnResult(std::string typ, float inter, int index)
	{
		type = typ;
		intersect = inter;
		indexToSend = index;
	};

	std::string type;
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