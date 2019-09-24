#pragma once
#include <cmath>

class Vec3
{
	public:

		float x, y, z;

		Vec3(float x, float y, float z);
		Vec3();
		~Vec3();
		
		float norm();
		float norm2();
		
		Vec3 mult(Vec3 v2);
		Vec3 cross(Vec3 v2);
		float operator*(Vec3 v2);
		Vec3 operator+(Vec3 v2);
		Vec3 operator-(Vec3 v2);
		Vec3 operator/(Vec3 v2);
		Vec3 operator*(float a);
		Vec3 operator/(float a);
		bool operator==(Vec3 v2);
		void operator=(Vec3 v2);
};

