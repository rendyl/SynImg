#define _USE_MATH_DEFINES
#include "Scene.h"
#include <math.h>
#include <random>

double generateRandomNumber(double min, double max)
{
	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_real_distribution<double> distrib(min, max);

	return distrib(generator);
}

Scene::Scene(Camera cam)
{
	camera = cam;
	tabSphere.push_back(Sphere(30000, Vec3(-30000, 300, 0), Vec3(0.7, 0.1, 0.1), 0));	// Left
	tabSphere.push_back(Sphere(30000, Vec3(30000+600, 300, 0), Vec3(0.1, 0.7, 0.1), 0)); // Right
	tabSphere.push_back(Sphere(30000, Vec3(300, -30000, 0), Vec3(1, 1, 1), 0));	// Down
	tabSphere.push_back(Sphere(30000, Vec3(300, 600+30000, 0), Vec3(1, 1, 1), 0)); // Up
	tabSphere.push_back(Sphere(30000, Vec3(300, 300, -30500), Vec3(1, 1, 1), 0));  // Back
	tabSphere.push_back(Sphere(30000, Vec3(300, 300, 30300), Vec3(1, 1, 1), 0));	// Front
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
	#pragma omp parallel for
	for (int i = 0; i < s.nbLights; i++)
	{
		float iRandX = generateRandomNumber(0 , s.dimension.x);
		float iRandY = generateRandomNumber(0 , s.dimension.y);
		float iRandZ = generateRandomNumber(0 , s.dimension.z);

		Vec3 vecRand(iRandX, iRandY, iRandZ);

		tabLight.push_back(Sphere(10, s.position + vecRand - s.dimension / 2, (s.color*1.6) / s.nbLights, 0));
	}
}

Vec3 Scene::getDirPixCam(int i, int j)
{
	Vec3 v = Vec3((camera.width/2) - i, (camera.height / 2) - j, camera.distanceToScreen);
	return (v/v.norm());
}

Vec3 Scene::getDir2Pos(Vec3 posFrom, Vec3 posTo)
{
	Vec3 dir = posTo - posFrom;
	return dir;
}

void Scene::appliqueCouleurLumiere(RGBQUAD * color, int indMin, Vec3 posTouche, Vec3 vecLightObj, Vec3 vecLightObjDir, int k)
{
	Vec3 normObjDir = getDir2Pos(tabSphere[indMin].position, posTouche);
	normObjDir = normObjDir / normObjDir.norm();

	float colorToAddRed = color->rgbRed + 255 * tabSphere[indMin].couleur.x * abs(normObjDir * vecLightObjDir) * tabLight[k].couleur.x * 1 * (250 / vecLightObj.norm());
	float colorToAddGreen = color->rgbGreen + 255 * tabSphere[indMin].couleur.y * abs(normObjDir * vecLightObjDir) * tabLight[k].couleur.y * 1 * (250 / vecLightObj.norm());
	float colorToAddBlue = color->rgbBlue + 255 * tabSphere[indMin].couleur.z * abs(normObjDir * vecLightObjDir) * tabLight[k].couleur.z * 1 * (250 / vecLightObj.norm());

	if ((normObjDir * vecLightObjDir) < 0)
	{
		colorToAddRed = color->rgbRed;
		colorToAddBlue = color->rgbGreen;
		colorToAddGreen = color->rgbBlue;
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

	// colorToAddRed = ((colorToAddRed / 255) / pow(2, 2)) * 255;
	// colorToAddGreen = ((colorToAddGreen / 255)/ pow(2, 2)) * 255;
	// colorToAddBlue = ((colorToAddBlue / 255) / pow(2, 2)) * 255;

	(colorToAddRed > 255) ? color->rgbRed = 255 : color->rgbRed = colorToAddRed;
	(colorToAddGreen > 255) ? color->rgbGreen = 255 : color->rgbGreen = colorToAddGreen;
	(colorToAddBlue > 255) ? color->rgbBlue = 255 : color->rgbBlue = colorToAddBlue;
}

void Scene::rayIntersectSphere(Rayon r1, std::vector<float> * results, std::vector<int> * indexs)
{
	for (int k = 0; k < tabSphere.size(); k++)
	{
		float res = r1.intersect(tabSphere[k]);

		if (res != -1)
		{
			results->push_back(res);
			indexs->push_back(k);
		}
	}
}

void Scene::getMinFromTab(int * indMin, float * resMin, std::vector<float> results, std::vector<int> indexs)
{
	*resMin = 99999999999999;
	*indMin = 99999999999999;

	// On recupere la premiere intersection
	for (int i = 0; i < results.size(); i++)
	{
		if (results[i] < *resMin)
		{
			*resMin = results[i];
			*indMin = indexs[i];
		}
	}
}

bool Scene::obstacleInTheWay(Rayon r2, Vec3 vecLightObj)
{
	for (int i = 0; i < tabSphere.size(); i++)
	{
		float res2 = r2.intersect(tabSphere[i]);

		if (res2 != -1)
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
	for (int i =  0; i < camera.width; i++)
	{
		#pragma omp parallel for
		for (int j = 0; j < camera.height; j++)
		{
			// On prend la direction de la camera depuis sa position vers le premier pixel
			Vec3 vecCam = getDir2Pos(camera.position, Vec3(i, j, 0));
			vecCam = vecCam / vecCam.norm();
			
			// On trace un rayon a partir de la
			Rayon r1(Vec3(i, j, 0), vecCam);
			std::vector<float> results;
			std::vector<int> indexs;

			// On regarde si le rayon intersecte un ou plusieurs objets
			rayIntersectSphere(r1, &results, &indexs);

			// Si le rayon n'a rien trouvé on met du noir
			color.rgbRed = 0;
			color.rgbGreen = 0;
			color.rgbBlue = 0;

			// Sinon 
			if(!indexs.empty())
			{
				float colorToAddRed, colorToAddBlue, colorToAddGreen;
				float resMin;
				int indMin;

				getMinFromTab(&indMin, &resMin, results, indexs);

				// On prend la position de l'intersection
				Vec3 posTouche = r1.position + r1.direction * resMin;
				
				// Si on a touché un miroir on va refaire un rayon et refaire les calculs précédents
				// TENTATIVE MIROIR

				if (tabSphere[indMin].albedo == 1)
				{
					Vec3 vecNormMiroir = getDir2Pos(tabSphere[indMin].position, posTouche);
					vecNormMiroir = vecNormMiroir / vecNormMiroir.norm();

					Vec3 dir = r1.direction  - vecNormMiroir*2*(r1.direction *vecNormMiroir);
					dir = dir / dir.norm();

					Rayon r4(posTouche + dir*1.5, dir);
					std::vector <float> results2;
					std::vector <int> indexs2;

					rayIntersectSphere(r4, &results2, &indexs2);
					if (results2.empty())
					{
						std::cout << "ahahhah" << std::endl;
						color.rgbRed = 255;
						color.rgbGreen = 0;
						color.rgbBlue = 255;
						break;
					}
					else
					{
						float resMin2 = 99999999999999;
						float indMin2 = 99999999999999;

						// On recupere la premiere intersection
						for (int i = 0; i < results2.size(); i++)
						{
							if (results2[i] < resMin2)
							{
								resMin2 = results2[i];
								indMin2 = indexs2[i];
							}
						}
						indMin = indMin2;
						posTouche = r4.position + r4.direction * resMin2;
					}
				}

				// On va regarder si elle est eclairée
				bool noLight = true;
				for (int k = 0; k < tabLight.size(); k++)
				{
					Vec3 vecLightObj = getDir2Pos(posTouche, tabLight[k].position);
					Vec3 vecLightObjDir = vecLightObj / vecLightObj.norm();

					// On trace un rayon entre la lumière et l'intersection
					Rayon r2(posTouche + vecLightObjDir*1.5, vecLightObjDir);

					// On regarde s'il y a un obstacle entre la lumiere et l'intersection
					bool obsInTheWay = obstacleInTheWay(r2, vecLightObj);

					// S'il n'y a pas d'obstacle on applique la couleur de la lumiere k
					if (!obsInTheWay)
					{
						// Il y a au moins une lumiere qui eclaire l'intersection
						noLight = false;				
						appliqueCouleurLumiere(&color, indMin, posTouche, vecLightObj, vecLightObjDir, k);
					}
				}

				// S'il n'y a pas de lumiere qui eclaire l'intersection
				if (noLight)
				{
					color.rgbRed = 0;
					color.rgbGreen = 0;
					color.rgbBlue = 0;
					
					// LUMIERE INDIRECTE
					
					Vec3 normObjDir = getDir2Pos(tabSphere[indMin].position, posTouche);
					normObjDir = normObjDir / normObjDir.norm();
					Vec3 vecRandom = normObjDir + Vec3(generateRandomNumber(0, 1), generateRandomNumber(0, 1), generateRandomNumber(0, 1));
					Vec3 base1 = normObjDir.cross(vecRandom);
					Vec3 base2 = normObjDir.cross(base1);

					for (int l = 0; l < 10; l++)
					{
						// On genere un vecteur
						Vec3 vecDir = generateRandomVectorHemisphere();
						vecDir = normObjDir * vecDir.z + base2 * vecDir.x + base1 * vecDir.y;

						// On le normalise
						vecDir = vecDir / vecDir.norm();

						Rayon r3(posTouche + vecDir * 1.5, vecDir);
						
						std::vector<float> results3;
						std::vector<int> indexs3;
						rayIntersectSphere(r3, &results3, &indexs3);

						if (!indexs3.empty())
						{
							int indMin3;
							float resMin3;
							getMinFromTab(&indMin3, &resMin3, results3, indexs3);

							Vec3 vecTouche = r3.position + r3.direction * resMin3;
							Vec3 vecToucheDir = vecTouche / vecTouche.norm();
							Vec3 normObjDirTouche = getDir2Pos(tabSphere[indMin3].position, vecTouche);
							normObjDirTouche = normObjDirTouche / normObjDirTouche.norm();
							// abs(vecToucheDir * normObjDirTouche / M_PI)
							colorToAddRed = color.rgbRed + 255 * tabSphere[indMin3].couleur.x * 0.2 * (250 / vecTouche.norm());
							colorToAddGreen = color.rgbGreen + 255 * tabSphere[indMin3].couleur.y * 0.2 * (250 / vecTouche.norm());
							colorToAddBlue = color.rgbBlue + 255 * tabSphere[indMin3].couleur.z * 0.2 * (250 / vecTouche.norm());

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

							break;
						}
					}

					(colorToAddRed > 255) ? color.rgbRed = 255 : color.rgbRed = colorToAddRed;
					(colorToAddGreen > 255) ? color.rgbGreen = 255 : color.rgbGreen = colorToAddGreen;
					(colorToAddBlue > 255) ? color.rgbBlue = 255 : color.rgbBlue = colorToAddBlue;
				}

				FreeImage_SetPixelColor(bitmap, i, camera.height-(j+1), &color);
			}
		}
	}

	if (FreeImage_Save(FIF_PNG, bitmap, "test.png", 0))
	{
		std::cout << "Image enregistree !" << std::endl;
	}
	
	FreeImage_DeInitialise();
}