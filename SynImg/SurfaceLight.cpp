#include "SurfaceLight.h"

SurfaceLight::SurfaceLight()
{

}

SurfaceLight::SurfaceLight(int nb, Vec3 pos, Vec3 dim, Vec3 col)
{
	nbLights = nb;
	position = pos;
	dimension = dim;
	color = col;
}