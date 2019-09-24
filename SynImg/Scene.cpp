#include "Scene.h"

Scene::Scene(Camera cam)
{
	camera = cam;
	tabSphere.push_back(Sphere(30000, Vec3(-30000, 300, 0), Vec3(0.7, 0.1, 0.1)));	// Left
	tabSphere.push_back(Sphere(30000, Vec3(30000+600, 300, 0), Vec3(0.1, 0.7, 0.1))); // Right
	tabSphere.push_back(Sphere(30000, Vec3(300, -30000, 0), Vec3(1, 1, 1)));	// Down
	tabSphere.push_back(Sphere(30000, Vec3(300, 600+30000, 0), Vec3(1, 1, 1))); // Up
	tabSphere.push_back(Sphere(30000, Vec3(300, 300, -30500), Vec3(0, 0, 0)));  // Back
	tabSphere.push_back(Sphere(30000, Vec3(300, 300, 30300), Vec3(0.9, 0.9, 0.9)));	// Front

}

float clamp(float min, float max, float value)
{
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

float lerp(float start, float end, float percent)
{
	return start + percent * (end - start);
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
		double randX = rand() / RAND_MAX;
		double randY = rand() / RAND_MAX;
		double randZ = rand() / RAND_MAX;

		int iRandX = (rand() % (int)s.dimension.x);
		int iRandY = (rand() % (int)s.dimension.y);
		int iRandZ = (rand() % (int)s.dimension.z);

		Vec3 vecRand(iRandX, iRandY, iRandZ);

		tabLight.push_back(Sphere(10, s.position + vecRand - s.dimension / 2, (s.color*2) / s.nbLights));
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

// TODO REAL CAMERA

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

			// Rayon r(Vec3(i, j, 0), getDirPixCam(i, j));
			
			Vec3 vecCam = getDir2Pos(camera.position, Vec3(i, j, 0));
			vecCam = vecCam / vecCam.norm();
			Rayon r1(Vec3(i, j, 0), vecCam);


			std::vector<float> results;
			std::vector<int> indexs;

			for(int k = 0; k < tabSphere.size(); k++)
			{
				int res = r1.intersect(tabSphere[k]);
				if (res != -1)
				{
					results.push_back(res);
					indexs.push_back(k);
				}
			}

			// Si le rayon n'a rien trouvé on met du noir
			if (indexs.empty())
			{
				color.rgbRed = 0;
				color.rgbGreen = 0;
				color.rgbBlue = 0;
			}
			// Sinon on cherche la premiere intersection
			else
			{
				color.rgbRed = 0;
				color.rgbGreen = 0;
				color.rgbBlue = 0;

				float resMin = 99999999999999;
				float indMin = 99999999999999;
				for(int i = 0; i < results.size(); i++)
				{
					if (results[i] < resMin)
					{
						resMin = results[i];
						indMin = indexs[i];
					}
				}
				
				// On cherche la position de l'intersection
				Vec3 posTouche = r1.position + r1.direction * resMin;

				bool noLight = true;

				for (int k = 0; k < tabLight.size(); k++)
				{
					Vec3 vecLightObj = getDir2Pos(posTouche, tabLight[k].position);
					Vec3 vecLightObjDir = vecLightObj / vecLightObj.norm();

					// On trace un rayon entre la lumière et l'intersection
					Rayon r2(posTouche, vecLightObjDir);

					bool obstacleInTheWay = false;

					for (int i = 0; i < tabSphere.size(); i++)
					{
						int res2 = r2.intersect(tabSphere[i]);

						if (res2 != -1)
						{
							if (i != indMin && res2 < vecLightObj.norm())
							{
								obstacleInTheWay = true;
								break;
							}
						}
					}

					if (!obstacleInTheWay)
					{
						Vec3 normObjDir = getDir2Pos(tabSphere[indMin].position, posTouche);
						normObjDir = normObjDir / normObjDir.norm();

						noLight = false;
						
						float colorToAddRed = color.rgbRed + 255 * tabSphere[indMin].couleur.x * abs(normObjDir * vecLightObjDir) * tabLight[k].couleur.x * 1.1 * (250 / vecLightObj.norm());
						float colorToAddGreen = color.rgbGreen + 255 * tabSphere[indMin].couleur.y * abs(normObjDir * vecLightObjDir) * tabLight[k].couleur.y * 1.1 * (250 / vecLightObj.norm());
						float colorToAddBlue = color.rgbBlue + 255 * tabSphere[indMin].couleur.z * abs(normObjDir * vecLightObjDir) * tabLight[k].couleur.z * 1.1 *  (250 / vecLightObj.norm());

						if ((normObjDir * vecLightObjDir) < 0)
						{
							colorToAddRed = color.rgbRed;
							colorToAddBlue = color.rgbGreen;
							colorToAddGreen = color.rgbBlue;
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


						(colorToAddRed > 255) ? color.rgbRed = 255 : color.rgbRed = colorToAddRed;
						(colorToAddGreen > 255) ? color.rgbGreen = 255 : color.rgbGreen = colorToAddGreen;
						(colorToAddBlue > 255) ? color.rgbBlue = 255 : color.rgbBlue = colorToAddBlue;
					}
				}

				if (noLight)
				{
					color.rgbRed = 0;
					color.rgbGreen = 0;
					color.rgbBlue = 0;

					// color.rgbRed = 255 * 0.25 * tabSphere[indMin].couleur.x;
					// color.rgbGreen = 255 * 0.25 * tabSphere[indMin].couleur.x;
					// color.rgbBlue = 255 * 0.25 * tabSphere[indMin].couleur.x;
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