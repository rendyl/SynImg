#include "Rayon.h"

Rayon::Rayon(Vec3 pos, Vec3 dir)
{
	position = pos;
	direction = dir;
}

float Rayon::intersect(Sphere s)
{
	float a = 1;
	float b = 2 * (position * direction - s.position * direction);
	float c = position.norm2() + s.position.norm2() - 2 * (position * s.position) - pow(s.rayon, 2);

	float delta = pow(b, 2) - 4*a*c;

	//std::cout << delta << std::endl;

	if (delta < 0)
	{
		// std::cout << "delta < 0, 0 sol(s)" << std::endl; 
		
		return -1;
	}
	else
	{
		// std::cout << "delta > 0, 2 sol(s)" << std::endl;
		// float solT1 = -(position * direction - s.position * direction) - sqrt(delta) / 2;
		// float solT2 = -(position * direction - s.position * direction) + sqrt(delta) / 2;

		float solT1 = -(b + sqrt(delta))/2*a;
		float solT2 = -(b - sqrt(delta))/2*a;
		//std::cout << solT1 << std::endl;
		//std::cout << solT2 << std::endl;

		if (solT1 >= 0)
		{
			return solT1;
		}
		else if (solT2 >= 0)
		{
			return solT2;
		}
		else
		{
			return -1;
		}
	}
}

float Rayon::intersect(Triangle t)
{
	/*
	bool intersect_triangle(Ray ray, Object object, Intersection & intersection)
	{
		Vec3F edge1, edge2, h, s, q;
		float a, f, u, v;
		const float epsilon = 0.0000001f;
		edge1 = object.geom.triangle.v1 - object.geom.triangle.v0;
		edge2 = object.geom.triangle.v2 - object.geom.triangle.v0;
		h = cross(ray.direction, edge2);
		a = dot(edge1, h);
		if (a > -epsilon && a < epsilon)
			return false;
		f = 1.f / a;
		s = ray.origin - object.geom.triangle.v0;
		u = f * (dot(s, h));
		if (u < 0.f || u > 1.f)
			return false;
		q = cross(s, edge1);
		v = f * (dot(ray.direction, q));
		if (v < 0.f || u + v > 1.f)
			return false;
		float t = f * dot(edge2, q);
		if (t > epsilon)
		{
			intersection.distance = t;
			intersection.position = ray.origin + ray.direction * t;
			intersection.normale = normalize(cross(edge1, edge2));
			intersection.object = object;
			return true;
		}
		else
			return false;
	}
	*/
}

float Rayon::intersect(Box b)
{

}