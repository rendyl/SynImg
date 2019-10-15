#include "TreeBox.h"
#include <algorithm>
#include <iostream>

bool comparatorTabBoxes(Box b1, Box b2)
{
	return (b1.pt1.x < b2.pt1.x);
}

TreeBox * TreeBox::createTreeFromBoxies(std::vector<Box> tabBoxes)
{
	TreeBox * tb = new TreeBox;
	tb->boxster = tabBoxes[0];

	// Fin de la recursion
	if (tabBoxes.size() == 1)
	{
		// std::cout << tabBoxes[0].indixSphere << std::endl;
		// ICI
		if (tabBoxes[0].typeContained == "sphere")
		{
			tb->s = tabBoxes[0].s;
			tb->indixSphere = tabBoxes[0].indixSphere;
			tb->typeContained = "sphere";
		}

		else if (tabBoxes[0].typeContained == "triangle")
		{
			tb->t = tabBoxes[0].t;
			tb->indixTriangle = tabBoxes[0].indixTriangle;
			tb->typeContained = "triangle";
		}

		tb->isLeaf = true;
		
		return tb;
	}

	for (int i = 1; i < tabBoxes.size(); i++) tb->boxster = tb->boxster.unionBox(tabBoxes[i]);

	std::vector<Box> vLeft;
	std::vector<Box> vRight;

	std::sort(tabBoxes.begin(), tabBoxes.end(), comparatorTabBoxes);

	for (int i = 0; i < tabBoxes.size(); i++)
	{
		(i < tabBoxes.size() / 2) ? vLeft.push_back(tabBoxes[i]) : vRight.push_back(tabBoxes[i]);
	}

	tb->isLeaf = false;
	tb->typeContained = "none";
	tb->left = createTreeFromBoxies(vLeft);
	tb->right = createTreeFromBoxies(vRight);

	return tb;
}