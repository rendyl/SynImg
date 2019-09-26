#pragma once
#include "Image.h"
#include "Rayon.h"
#include "FreeImage.h"
#include "Camera.h"
#include "SurfaceLight.h"

#include <algorithm>
#include <vector>
#include <random>

class Scene
{
	public :
		
		double generateRandomNumber(double min, double max);

		// Camera 
		Camera camera;
		int bpp = 24;

		// Elements
		std::vector<Sphere> tabSphere;
		std::vector<Sphere> tabLight;

		// Constructeur
		Scene(Camera cam);

		// Ajouter un element
		void addSphere(Sphere s);
		void addLight(Sphere l);
		void addSurfaceLight(SurfaceLight s);

		// Chope la direction de la cam depuis le pixel
		Vec3 getDirPixCam(int i, int j);
		Vec3 getDir2Pos(Vec3 posFrom, Vec3 posTo);

		// Creer une Image a partir de la scene
		void createImage();
		void createImage2();
		RGBQUAD chercheCouleur(Rayon r1, int compteur);
		Vec3 appliqueCouleurLumiere(int indMin, Vec3 posTouche, Vec3 vecLightObj, Vec3 vecLightObjDir, int k);
		void rayIntersectSphere(Rayon r1, float* result, int* index);
		// void rayIntersectSphere(Rayon r1, std::vector<float>* results, std::vector<int>* indexs);
		void getMinFromTab(int* indMin, float* resMin, std::vector<float> results, std::vector<int> indexs);
		bool obstacleInTheWay(Rayon r2, Vec3 vecLightObj);
		Vec3 generateRandomVectorHemisphere();
};

