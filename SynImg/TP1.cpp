#include "TP1.h"

void TP1::testVec3()
{
	Vec3 v(1, 2, 3);
	Vec3 v2(4, 5, 6);
	Vec3 v3(5, 7, 9);
	assert(v == v);
	assert(v.norm2() == 14);
	assert(v * v == 14);
	assert(v + v2 == v3);
}

void TP1::simFall()
{
	std::string const nomFichier("C:/Users/rlatbi/Desktop/2019/Test70.txt");
	std::ofstream flow(nomFichier.c_str());

	double start = clock();
	double end = clock();

	float dt = 200;
	float coef = (10 * 9.81) / (70 * 70);
	float m = 15;

	Vec3 vent(-4, -3, 0);

	Vec3 p0(0, 0, 100);
	Vec3 v0(5, 3, 0);
	Vec3 g(0, 0, -9.81);

	Vec3 pos = p0;
	Vec3 posVent = p0;
	Vec3 vit = v0;
	Vec3 accel;

	double lastIter = 0;

	while (end - start < 10000) // On arrête au bout de 10s
	{
		end = clock();
		if (end - lastIter > dt) // On itere cette boucle tous les dt
		{
			accel = g - (vit * coef * vit.norm()) / m;
			vit = vit + accel * (dt / 1000);
			pos = pos + vit * (dt / 1000);
			posVent = pos + vent * ((end - start) / 1000);

			if (flow)
			{
				flow << posVent.x << "," << posVent.y << "," << posVent.z << std::endl;
				//flow << pos.x << "," << pos.y << "," << pos.z << std::endl;
			}
			else
			{
				std::cout << "Impossible d'écrire ds le fichier" << std::endl;
			}

			std::cout << "accelX " << accel.x << " accelY " << accel.y << " accelZ " << accel.z << std::endl;
			std::cout << "vitX " << vit.x << " vitY " << vit.y << " vitZ " << vit.z << std::endl;
			std::cout << "posX " << pos.x << " posY " << pos.y << " posZ " << pos.z << std::endl;

			// debug std::cout << "LastIter " << lastIter << " end " << end << std::endl;
			lastIter = end;
		}
	}
}