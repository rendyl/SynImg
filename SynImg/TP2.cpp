#include "TP2.h"

void TP2::testIntersect()
{
	Vec3 posRayon(0, 0, 0);
	Vec3 dirRayon(1, 0, 0);

	Vec3 posRayon1(0, 0, 0);
	Vec3 dirRayon1(-1, 0, 0);

	float rayonSphere = 5;
	Vec3 posSphere(10, 0, 0);

	Rayon r(posRayon, dirRayon);
	Rayon r1(posRayon1, dirRayon1);
	Sphere s(rayonSphere, posSphere, Vec3(0, 0, 0), 1);

	assert(r.intersect(s) == 5);
	assert(r1.intersect(s) == -1);
}

void TP2::testCross()
{
	Vec3 v1(1, 0, 0);
	Vec3 v2(0, 0, -1);
	Vec3 v3 = v1.cross(v2);

	assert(v3.x == 0);
	assert(v3.y == -1);
	assert(v3.z == 0);
}