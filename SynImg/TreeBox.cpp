#include "TreeBox.h"
#include <algorithm>
#include <iostream>

bool comparatorTabBoxes(Box b1, Box b2)
{
	return (b1.pt1.x < b2.pt1.x);
}

TreeBox * TreeBox::createTreeFromBoxies(std::vector<Box> tabBoxes)
{
	TreeBox t;
	t.boxster = tabBoxes[0];

	// Fin de la recursion
	if (tabBoxes.size() == 1)
	{
		// std::cout << tabBoxes[0].indixSphere << std::endl;
		t.s = tabBoxes[0].s;
		t.indixSphere = tabBoxes[0].indixSphere;
		t.isLeaf = true;
		return &t;
	}

	for (int i = 1; i < tabBoxes.size(); i++) t.boxster = t.boxster.unionBox(tabBoxes[i]);

	std::vector<Box> vLeft;
	std::vector<Box> vRight;

	std::sort(tabBoxes.begin(), tabBoxes.end(), comparatorTabBoxes);

	for (int i = 0; i < tabBoxes.size(); i++)
	{
		(i < tabBoxes.size() / 2) ? vLeft.push_back(tabBoxes[i]) : vRight.push_back(tabBoxes[i]);
	}

	t.left = createTreeFromBoxies(vLeft);
	t.right = createTreeFromBoxies(vRight);

	return &t;
}