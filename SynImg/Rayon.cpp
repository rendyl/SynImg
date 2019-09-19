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
		//std::cout << "delta < 0, 0 sol(s)" << std::endl; 
		
		return -1;
	}
	else
	{
		//std::cout << "delta > 0, 2 sol(s)" << std::endl;
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