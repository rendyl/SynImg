#include <string>
#include "Rayon.h"
#include "Box.h"

#pragma once
class Object
{
	public :
		virtual float intersect(Rayon r) = 0;
		virtual Box createBoundingBox(int indice) = 0;
};