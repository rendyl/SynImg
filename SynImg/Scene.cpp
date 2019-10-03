#define _USE_MATH_DEFINES
#include "Scene.h"
#include <math.h>
#include <omp.h>

double Scene::generateRandomNumber(double min, double max)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<double> distrib(min, max);

	return distrib(generator);
}

Scene::Scene(Camera cam)
{
	camera = cam;
	tabSphere.push_back(Sphere(30000, Vec3(-30000, 300, 0), Vec3(0.45, 0.34, 0.34), 0.9));	// Left
	tabSphere.push_back(Sphere(30000, Vec3(30000 + 600, 300, 0), Vec3(0.74, 0.71, 0.57), 0.9)); // Right
	tabSphere.push_back(Sphere(30000, Vec3(300, -30000, 0), Vec3(1, 1, 1), 0.9));	// Down
	tabSphere.push_back(Sphere(30000, Vec3(300, 600 + 30000, 0), Vec3(1, 1, 1), 0.9)); // Up
	tabSphere.push_back(Sphere(30000, Vec3(300, 300, -30500), Vec3(1, 1, 1), 0.9));  // Back
	tabSphere.push_back(Sphere(30000, Vec3(300, 300, 30300), Vec3(1, 1, 1), 0.9));	// Front
}

void Scene::addSphere(Sphere s)
{
	tabSphere.push_back(s);
}

void Scene::addLight(Sphere l)
{
	tabLight.push_back(l);
}

void Scene::addSurfaceLight(SurfaceLight s)
{
	for (int i = 0; i < s.nbLights; i++)
	{
		float iRandX = generateRandomNumber(0, s.dimension.x);
		float iRandY = generateRandomNumber(0, s.dimension.y);
		float iRandZ = generateRandomNumber(0, s.dimension.z);

		Vec3 vecRand(iRandX, iRandY, iRandZ);

		tabLight.push_back(Sphere(10, s.position + vecRand - s.dimension / 2, (s.color) / s.nbLights, 0));
	}
}

Vec3 Scene::getDirPixCam(int i, int j)
{
	Vec3 v = Vec3((camera.width / 2) - i, (camera.height / 2) - j, camera.distanceToScreen);
	return (v / v.norm());
}

Vec3 Scene::getDir2Pos(Vec3 posFrom, Vec3 posTo)
{
	Vec3 dir = posTo - posFrom;
	return dir;
}

Vec3 Scene::appliqueCouleurLumiere(int indMin, Vec3 posTouche, Vec3 vecLightObj, Vec3 vecLightObjDir, int k)
{
	Vec3 normObjDir = getDir2Pos(tabSphere[indMin].position, posTouche);
	normObjDir = normObjDir / normObjDir.norm();

	// float colorToAddRed = color->rgbRed + 255 * tabSphere[indMin].couleur.x * abs(normObjDir * vecLightObjDir) * tabLight[k].couleur.x * 1 * (250 / vecLightObj.norm());
	// float colorToAddGreen = color->rgbGreen + 255 * tabSphere[indMin].couleur.y * abs(normObjDir * vecLightObjDir) * tabLight[k].couleur.y * 1 * (250 / vecLightObj.norm());
	// float colorToAddBlue = color->rgbBlue + 255 * tabSphere[indMin].couleur.z * abs(normObjDir * vecLightObjDir) * tabLight[k].couleur.z * 1 * (250 / vecLightObj.norm());

	float colorToAddRed = 255 * tabSphere[indMin].couleur.x * abs(normObjDir * vecLightObjDir) * tabLight[k].couleur.x * 1 * (250 / vecLightObj.norm());
	float colorToAddGreen = 255 * tabSphere[indMin].couleur.y * abs(normObjDir * vecLightObjDir) * tabLight[k].couleur.y * 1 * (250 / vecLightObj.norm());
	float colorToAddBlue = 255 * tabSphere[indMin].couleur.z * abs(normObjDir * vecLightObjDir) * tabLight[k].couleur.z * 1 * (250 / vecLightObj.norm());

	if ((normObjDir * vecLightObjDir) < 0)
	{
		colorToAddRed = 0;
		colorToAddBlue = 0;
		colorToAddGreen = 0;
	}

	float modifierRed = 0;
	float modifierGreen = 0;
	float modifierBlue = 0;

	if (colorToAddRed > 255)
	{
		modifierGreen += colorToAddRed - 255;
		modifierBlue += colorToAddRed - 255;
	}

	if (colorToAddGreen > 255)
	{
		modifierRed += colorToAddGreen - 255;
		modifierBlue += colorToAddGreen - 255;
	}

	if (colorToAddBlue > 255)
	{
		modifierRed += colorToAddBlue - 255;
		modifierGreen += colorToAddBlue - 255;
	}

	colorToAddRed += modifierRed;
	colorToAddGreen += modifierGreen;
	colorToAddBlue += modifierBlue;

	return Vec3(colorToAddRed, colorToAddGreen, colorToAddBlue);

	// colorToAddRed = ((colorToAddRed / 255) / pow(2, 2)) * 255;
	// colorToAddGreen = ((colorToAddGreen / 255)/ pow(2, 2)) * 255;
	// colorToAddBlue = ((colorToAddBlue / 255) / pow(2, 2)) * 255;

	// (colorToAddRed > 255) ? color->rgbRed = 255 : color->rgbRed = colorToAddRed;
	// (colorToAddGreen > 255) ? color->rgbGreen = 255 : color->rgbGreen = colorToAddGreen;
	// (colorToAddBlue > 255) ? color->rgbBlue = 255 : color->rgbBlue = colorToAddBlue;
}

void Scene::rayIntersectSphere(Rayon r1, float* result, int* index)
{
	for (int k = 0; k < tabSphere.size(); k++)
	{
		float res = r1.intersect(tabSphere[k]);

		if (res != -1)
		{
			if (*index == -1 || res < *result)
			{
				*result = res;
				*index = k;
			}
		}
	}
}

bool Scene::obstacleInTheWay(Rayon r2, Vec3 vecLightObj)
{
	for (int i = 0; i < tabSphere.size(); i++)
	{
		float res2 = r2.intersect(tabSphere[i]);

		if (res2 != -1 && tabSphere[i].albedo <= 1)
		{
			if (res2 < vecLightObj.norm())
			{
				return true;
			}
		}
	}
	return false;
}

Vec3 Scene::generateRandomVectorHemisphere()
{
	double r1 = generateRandomNumber(0, 1);
	double r2 = generateRandomNumber(0, 1);

	float iRandX = cos(2 * M_PI * r1) * sqrt(1 - pow(r2, 2));
	float iRandY = sin(2 * M_PI * r1) * sqrt(1 - pow(r2, 2));
	float iRandZ = r2;

	return Vec3(iRandX, iRandY, iRandZ);
}

RGBQUAD Scene::chercheCouleur(Rayon r1, int compteur)
{
	RGBQUAD color;
	color.rgbRed = 0;
	color.rgbGreen = 0;
	color.rgbBlue = 0;

	float resMin = -1;
	int indMin = -1;

	// On regarde si le rayon intersecte un ou plusieurs objets
	rayIntersectSphere(r1, &resMin, &indMin);

	// Si le rayon n'a rien trouvé on met du noir
	float colorToAddRed = 0;
	float colorToAddGreen = 0;
	float colorToAddBlue = 0;

	if (indMin == -1 || compteur == 3)
	{
		return color;
	}

	// On prend la position de l'intersection
	Vec3 posTouche = r1.position + r1.direction * resMin;

	// Si on a touché un miroir on va refaire un rayon et refaire les calculs précédents

	if (tabSphere[indMin].albedo == 1)
	{
		Vec3 vecNormMiroir = getDir2Pos(tabSphere[indMin].position, posTouche);
		vecNormMiroir = vecNormMiroir / vecNormMiroir.norm();

		Vec3 dir = r1.direction - vecNormMiroir * 2 * (r1.direction * vecNormMiroir);
		dir = dir / dir.norm();

		Rayon r4(posTouche + dir * 1.5, dir);

		color = chercheCouleur(r4, compteur + 1);

		return color;
	}

	// Indice de refractions : N = 1 AIR / N = 1.5 VERRE / n1.sin(i1) = n2.sin(i2)

	if (tabSphere[indMin].albedo > 1)
	{
		Vec3 vecNormVerre = getDir2Pos(tabSphere[indMin].position, posTouche);
		vecNormVerre = vecNormVerre / vecNormVerre.norm();

		Vec3 dirReflechie = r1.direction - vecNormVerre * 2 * (r1.direction * vecNormVerre);
		dirReflechie = dirReflechie / dirReflechie.norm();

		int prodScalNormIncident = (r1.direction * vecNormVerre) / abs(r1.direction * vecNormVerre);

		Vec3 dirRefractee;
		float eta = 1;
		float N_dot_I = (r1.direction * vecNormVerre);

		float n1 = 1;
		float n2 = eta;

		bool reflectionTotale = false;

		if (prodScalNormIncident >= 0) float tmp = n1, n1 = n2, n2 = tmp, eta = 1 / tabSphere[indMin].albedo;

		// float r0 = pow((n1 - n2) / (n1 + n2), 2);
		// float rTheta = r0 + (1 - r0) * pow((1 - abs(N_dot_I)), 5);

		vecNormVerre = vecNormVerre * (-prodScalNormIncident);

		float k = 1.f - eta * eta * (1.f - N_dot_I * N_dot_I);
		if (k < 0.f) reflectionTotale = true;
		else dirRefractee = r1.direction * eta - vecNormVerre * (eta * (-prodScalNormIncident) * N_dot_I + sqrtf(k));

		dirRefractee = dirRefractee / dirRefractee.norm();

		Rayon r4(posTouche + dirReflechie * 1.5, dirReflechie);
		RGBQUAD color1 = chercheCouleur(r4, compteur + 1);

		Rayon r5(posTouche + dirRefractee * 1.5, dirRefractee);
		RGBQUAD color2 = chercheCouleur(r5, compteur + 1);
		
		float pourcentReflect = 0;
		float pourcentRefract = 1;

		if (reflectionTotale)
		{
			pourcentReflect = 0.9;
			pourcentRefract = 0.1;
		}
		else
		{
			pourcentReflect = 0.5;
			pourcentRefract = 0.5;
		}

		float colorToAddRed1 = (int)color1.rgbRed;
		float colorToAddGreen1 = (int)color1.rgbGreen;
		float colorToAddBlue1 = (int)color1.rgbBlue;

		float colorToAddRed2  = colorToAddRed1 * pourcentReflect;
		float colorToAddGreen2 = colorToAddGreen1 * pourcentReflect;
		float colorToAddBlue2 = colorToAddBlue1 * pourcentReflect;

		float colorToAddRed3 = (int)color2.rgbRed;
		float colorToAddGreen3 = (int)color2.rgbGreen;
		float colorToAddBlue3 = (int)color2.rgbBlue;

		float colorToAddRed4 = colorToAddRed3 * pourcentRefract;
		float colorToAddGreen4 = colorToAddGreen3 * pourcentRefract;
		float colorToAddBlue4 = colorToAddBlue3 * pourcentRefract;

		colorToAddRed = tabSphere[indMin].couleur.x*(colorToAddRed2 + colorToAddRed4);
		colorToAddGreen = tabSphere[indMin].couleur.y*(colorToAddGreen2 + colorToAddGreen4);
		colorToAddBlue = tabSphere[indMin].couleur.z*(colorToAddBlue2 + colorToAddBlue4);

		// std::cout << colorToAddRed << std::endl;
		// std::cout << colorToAddGreen << std::endl;
		// std::cout << colorToAddBlue << std::endl;

		color.rgbRed = colorToAddRed;
		color.rgbGreen = colorToAddGreen;
		color.rgbBlue = colorToAddBlue;
		
		return color;
	}


	// Sinon on va regarder si l'intersection est eclairée
	for (int k = 0; k < tabLight.size(); k++)
	{
		Vec3 vecLightObj = getDir2Pos(posTouche, tabLight[k].position);
		Vec3 vecLightObjDir = vecLightObj / vecLightObj.norm();

		// On trace un rayon entre la lumière et l'intersection
		Rayon r2(posTouche + vecLightObjDir * 1.5, vecLightObjDir);

		// On regarde s'il y a un obstacle entre la lumiere et l'intersection
		bool obsInTheWay = obstacleInTheWay(r2, vecLightObj);

		// S'il n'y a pas d'obstacle on applique la couleur de la lumiere k
		if (!obsInTheWay)
		{
			// Il y a au moins une lumiere qui eclaire l'intersection
			Vec3 colorToAddVec = appliqueCouleurLumiere(indMin, posTouche, vecLightObj, vecLightObjDir, k);
			colorToAddRed += colorToAddVec.x;
			colorToAddGreen += colorToAddVec.y;
			colorToAddBlue += colorToAddVec.z;
		}
	}

	// On ajoute les lumières indirectes
	/*
	Vec3 normObjDir = getDir2Pos(tabSphere[indMin].position, posTouche);
	normObjDir = normObjDir / normObjDir.norm();
	Vec3 vecRandom = normObjDir + Vec3(generateRandomNumber(0, 1), generateRandomNumber(0, 1), generateRandomNumber(0, 1));
	Vec3 base1 = normObjDir.cross(vecRandom);
	base1 = base1 / base1.norm();
	Vec3 base2 = normObjDir.cross(base1);
	base2 = base2 / base2.norm();

	for (int l = 0; l < 5; l++)
	{
		// On genere un vecteur
		Vec3 vecDir = generateRandomVectorHemisphere();
		vecDir = normObjDir * vecDir.z + base2 * vecDir.x + base1 * vecDir.y;
		// On le normalise
		vecDir = vecDir / vecDir.norm();

		Rayon r3(posTouche + vecDir * 1.5, vecDir);

		RGBQUAD newColor = chercheCouleur(r3, compteur + 1);

		float resMin3 = -1;
		int indMin3 = -1;
		rayIntersectSphere(r3, &resMin3, &indMin3);

		if (indMin3 != -1)
		{
			Vec3 posTouche3 = r3.position + r3.direction * resMin3;
			Vec3 normTouche3 = getDir2Pos(tabSphere[indMin3].position, posTouche3);
			normTouche3 = normTouche3 / normTouche3.norm();

			colorToAddRed = colorToAddRed + (tabSphere[indMin].albedo/ (2*M_PI)) * abs(r3.direction * normTouche3) * tabSphere[indMin].couleur.x * (newColor.rgbRed);
			colorToAddGreen = colorToAddGreen + (tabSphere[indMin].albedo / (2 * M_PI)) * abs(r3.direction * normTouche3) * tabSphere[indMin].couleur.y * (newColor.rgbGreen);
			colorToAddBlue = colorToAddBlue + (tabSphere[indMin].albedo / (2 * M_PI)) * abs(r3.direction * normTouche3) * tabSphere[indMin].couleur.z * (newColor.rgbBlue);
		}
	}
	*/

	(colorToAddRed > 255) ? color.rgbRed = 255 : color.rgbRed = colorToAddRed;
	(colorToAddGreen > 255) ? color.rgbGreen = 255 : color.rgbGreen = colorToAddGreen;
	(colorToAddBlue > 255) ? color.rgbBlue = 255 : color.rgbBlue = colorToAddBlue;

	return color;
}

void Scene::createImage()
{
	FreeImage_Initialise();

	FIBITMAP* bitmap = FreeImage_Allocate(camera.width, camera.height, bpp);
	RGBQUAD color;

	if (!bitmap)
	{
		exit(1);
	}

	// On parcourt les pixels de l'image
	#pragma omp parallel for
	for (int i = 0; i < camera.width; i++)
	{
		if (i % 100 == 0) std::cout << "i " << i << std::endl;
		for (int j = 0; j < camera.height; j++)
		{
			// On prend la direction de la camera depuis sa position vers le premier pixel
			Vec3 vecCam = getDir2Pos(camera.position, Vec3(i, j, 0));
			vecCam = vecCam / vecCam.norm();

			// On trace un rayon a partir de la
			Rayon r1(Vec3(i, j, 0), vecCam);

			color = chercheCouleur(r1, 0);

			FreeImage_SetPixelColor(bitmap, i, camera.height - (j + 1), &color);
		}
	}

	if (FreeImage_Save(FIF_PNG, bitmap, "test.png", 0))
	{
		std::cout << "Image enregistree !" << std::endl;
	}

	FreeImage_DeInitialise();
}