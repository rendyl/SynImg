#include "Vec3.h"

Vec3::Vec3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vec3::Vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3::~Vec3()
{

}

float Vec3::norm()
{
	return sqrt(this->norm2());
}

float Vec3::norm2()
{
	return (*this)*(*this);
}

Vec3 Vec3::mult(Vec3 v2)
{
	Vec3 v(x * v2.x, y * v2.y, z * v2.z);
	return v;
}

Vec3 Vec3::cross(Vec3 v2)
{
	Vec3 v(y * v2.z - z * v2.y, z * v2.x - v2.z*x, x*v2.y - y*v2.x);
	return v;
}

float Vec3::operator*(Vec3 v2)
{
	return x * v2.x + y * v2.y + z * v2.z;
}

Vec3 Vec3::operator+(Vec3 v2)
{
	Vec3 v3(x + v2.x, y + v2.y, z + v2.z);
	return v3;
}

Vec3 Vec3::operator-(Vec3 v2)
{
	Vec3 v3(x - v2.x, y - v2.y, z - v2.z);
	return v3;
}

Vec3 Vec3::operator/(Vec3 v2)
{
	Vec3 v3(x / v2.x, y / v2.y, z / v2.z);
	return v3;
}

bool Vec3::operator==(Vec3 v2)
{
	return x == v2.x && y == v2.y && z == v2.z;
}

void Vec3::operator=(Vec3 v2)
{
	x = v2.x;
	y = v2.y;
	z = v2.z;
}

Vec3 Vec3::operator*(float a)
{
	return Vec3(a * x, a * y, a * z);
}

Vec3 Vec3::operator/(float a)
{
	return Vec3(x / a, y / a, z / a);
}