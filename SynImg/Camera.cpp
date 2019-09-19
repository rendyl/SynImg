#include "Camera.h"

Camera::Camera()
{
	width = 0;
	height = 0; 
	distanceToScreen = 0;
}

Camera::Camera(int wid, int hei, float dist, Vec3 pos)
{
	width = wid;
	height = hei;
	position = pos;
	distanceToScreen = dist;
} 