#include "Box.h"

Box Box::createBoxFromSphere(Sphere s)
{
	Box b;
	b.pt1 = s.position - Vec3(1, 1, 1)*s.rayon;
	b.pt2 = s.position + Vec3(1, 1, 1)*s.rayon;
	return b;
}

Box Box::unionBox(Box b)
{

}