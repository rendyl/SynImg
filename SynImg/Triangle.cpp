#include "Triangle.h"
#include <iostream>

Triangle::Triangle()
{

}

Triangle::Triangle(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 couleurx, float albedox)
{
	vertice1 = v1;
	// vertice1.display();
	vertice2 = v2;
	// vertice2.display();
	vertice3 = v3;
	// vertice3.display();
	normal = calculateNorm(v1, v2, v3)*(-1);
	// normal.display();
	couleur = couleurx;
	albedo = albedox;
}

Vec3 Triangle::calculateNorm(Vec3 v1, Vec3 v2, Vec3 v3)
{
	Vec3 edge1 = v2 - v1;
	// edge1 = edge1 / edge1.norm();
	
	Vec3 edge2 = v3 - v1;
	// edge2 = edge2 / edge2.norm();

	Vec3 norm = edge1.cross(edge2) / edge1.cross(edge2).norm();
	//norm.display();

	return norm;
}

void Triangle::display()
{
	std::cout << "Vertice 1 ";
	vertice1.display();
	std::cout << "Vertice 2 ";
	vertice2.display();
	std::cout << "Vertice 3 ";
	vertice3.display();
	std::cout << "Normal ";
	normal.display();
}
