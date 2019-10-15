#pragma once
#include <vector>
#include "Box.h"

class TreeBox
{
	public :

		TreeBox * left;
		TreeBox * right;
		Box boxster;

		Sphere s;
		Triangle t;

		std::string typeContained = "";

		int indixSphere = -1;
		int indixTriangle = -1;

		bool isLeaf = false;

		TreeBox * createTreeFromBoxies(std::vector<Box> tabBoxes);
};

