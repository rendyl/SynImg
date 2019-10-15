#include "Triangle.h"

Triangle::Triangle(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 n)
{
	Vec3 vertice1 = v1;
	Vec3 vertice2 = v1;
	Vec3 vertice3 = v1;
	Vec3 normal = n;
}

void Triangle::recalculateNorm()
{
	// Vector3 pt1 = vertices[triangles[t++]];
	// Vector3 pt2 = vertices[triangles[t++]];
	// Vector3 pt3 = vertices[triangles[t++]];
	// Vector3 vec1 = pt1 - pt2;
	// Vector3 vec2 = pt2 - pt3;

	// normTri[j] = Vector3.Cross(vec1, vec2).normalized;
}