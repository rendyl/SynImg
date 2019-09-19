#pragma once
#include "Image.h"
#include "Rayon.h"
#include "FreeImage.h"
#include "Camera.h"

#include <algorithm>
#include <vector>

class Scene
{
	public :
		
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

		// Chope la direction de la cam depuis le pixel
		Vec3 getDirPixCam(int i, int j);
		Vec3 getDir2Pos(Vec3 posFrom, Vec3 posTo);

		// Creer une Image a partir de la scene
		void createImage();
};

