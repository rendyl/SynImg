#include "Scene.h"
#include "TP1.h"
#include "TP2.h"

#include <algorithm>
#include <iostream>

int main()
{	
	Scene s(Camera(600, 600, 100));
	s.addSphere(Sphere(59, Vec3(345, 250, 220), Vec3(1, 1, 1)));
	s.addSphere(Sphere(59, Vec3(255, 250, 220), Vec3(1, 1, 1)));
	s.addSphere(Sphere(100, Vec3(300, 300, 250), Vec3(1, 0, 0)));
	s.addLight(Sphere(10, Vec3(200, 200, 0), Vec3(1, 0.95, 0.9)));
	s.createImage();
}



