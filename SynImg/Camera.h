#pragma once
#include "Vec3.h"

class Camera
{
	public :

		int width;
		int height;
		float distanceToScreen;

		Camera();
		Camera(int wid, int hei, float dis);
};

