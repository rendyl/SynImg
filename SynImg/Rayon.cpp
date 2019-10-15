#include <limits>
#include <algorithm>
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
	float t;
	// r.dir is unit direction vector of ray
	(direction.x == 0) ? inv_direction.x = std::numeric_limits<float>::infinity() : inv_direction.x = 1.0f / direction.x;
	(direction.y == 0) ? inv_direction.y = std::numeric_limits<float>::infinity() : inv_direction.y = 1.0f / direction.y;
	(direction.z == 0) ? inv_direction.z = std::numeric_limits<float>::infinity() : inv_direction.z = 1.0f / direction.z;

	// lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
	// r.org is origin of ray
	float t1 = (b.pt1.x - position.x) * inv_direction.x;
	float t2 = (b.pt2.x - position.x) * inv_direction.x;
	float t3 = (b.pt1.y - position.y) * inv_direction.y;
	float t4 = (b.pt2.y - position.y) * inv_direction.y;
	float t5 = (b.pt1.z - position.z) * inv_direction.z;
	float t6 = (b.pt2.z - position.z) * inv_direction.z;

	float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if (tmax < 0)
	{
		t = tmax;
		return -1;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		t = tmax;
		return -1;
	}

	t = tmin;
	return 1;
}

returnResult Rayon::intersectTB(TreeBox * tb)
{
	if (tb->isLeaf)
	{
		return returnResult(intersect(tb->s), tb->indixSphere);
	}
	else
	{
		if (intersect(tb->boxster) != -1)
		{
			returnResult r1 = intersectTB(tb->left);
			//std::cout << "indexL " << r1.indexToSend << std::endl;
			//std::cout << "intersectL " << r1.intersect << std::endl;
			returnResult r2 = intersectTB(tb->right);
			//std::cout << "indexR " << r2.indexToSend << std::endl;
			//std::cout << "intersectR " << r2.intersect << std::endl;

			if (r1.intersect == -1 && r2.intersect == -1)
			{	
				//std::cout << "returned NONE" << std::endl;
				return returnResult(-1, -1);
			}
			else if (r1.intersect == -1)
			{
				//std::cout << "returned RIGHT" << std::endl;
				return r2;
			}
			else if (r2.intersect == -1)
			{
				//std::cout << "returned LEFT" << std::endl;
				return r1;
			}
			else
			{
				if (r2.intersect < r1.intersect)
				{
					//std::cout << "returned RIGHT" << std::endl; 
					return r2;
				}
				//std::cout << "returned LEFT" << std::endl;
				return r1;
			}
		}
		else
		{
			return returnResult(-1, -1);
		}
	}
}
