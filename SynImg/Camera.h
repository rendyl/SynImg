#pragma once
#include "Vec3.h"

class Camera
{
	public :

		int width;
		int height;
		Vec3 position;
		float distanceToScreen;

		Camera();
		Camera(int wid, int hei, float dis, Vec3 pos);
};

