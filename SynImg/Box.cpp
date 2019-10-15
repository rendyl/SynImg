#include "Box.h"
#include <algorithm>

Box::Box()
{

}

Box Box::createBoxFromSphere(Sphere s, int i)
{
	Box b;
	b.indixSphere = i;

	b.pt1 = s.position - Vec3(1, 1, 1) * s.rayon;
	b.pt2 = s.position + Vec3(1, 1, 1) * s.rayon;

	b.typeContained = "sphere";
	b.s = s;

	return b;
}

Box Box::createBoxFromTriangle(Triangle t, int i)
{
	Box b;
	b.indixTriangle = i;

	b.pt1.x = std::min(std::min(t.vertice1.x, t.vertice2.x), t.vertice3.x);
	b.pt1.y = std::min(std::min(t.vertice1.y, t.vertice2.y), t.vertice3.y);
	b.pt1.z = std::min(std::min(t.vertice1.z, t.vertice2.z), t.vertice3.z);

	b.pt2.x = std::max(std::max(t.vertice1.x, t.vertice2.x), t.vertice3.x);
	b.pt2.y = std::max(std::max(t.vertice1.y, t.vertice2.y), t.vertice3.y);
	b.pt2.z = std::max(std::max(t.vertice1.z, t.vertice2.z), t.vertice3.z);

	b.typeContained = "triangle";
	b.t = t;

	return b;
}

Box::Box(Sphere s, int i)
{
	*this = createBoxFromSphere(s, i);
}

Box::Box(Triangle t, int i)
{
	*this = createBoxFromTriangle(t, i);
}

Box Box::unionBox(Box b)
{
	Box b2;
	b2.pt1 = Vec3(std::min(this->pt1.x, b.pt1.x), std::min(this->pt1.y, b.pt1.y), std::min(this->pt1.z, b.pt1.z));
	b2.pt2 = Vec3(std::max(this->pt2.x, b.pt2.x), std::max(this->pt2.y, b.pt2.y), std::max(this->pt2.z, b.pt2.z));
	return b2;
}