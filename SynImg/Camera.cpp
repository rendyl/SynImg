#include "Camera.h"

Camera::Camera()
{
	width = 0;
	height = 0; 
	distanceToScreen = 0;
}

Camera::Camera(int wid, int hei, float dist)
{
	width = wid;
	height = hei;
	distanceToScreen = dist;
} 