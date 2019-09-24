#include "Scene.h"
#include "TP1.h"
#include "TP2.h"

#include <algorithm>
#include <iostream>

int main()
{	
	/*
	// Pretty Scene
	s.addSphere(Sphere(50, Vec3(200, 550, 50), Vec3(1, 1, 1)));
	s.addSphere(Sphere(100, Vec3(300, 500, 150), Vec3(1, 1, 1)));
	s.addLight(Sphere(10, Vec3(500, 300, 100), Vec3(0.3, 0.5, 0.3)));
	s.addLight(Sphere(10, Vec3(100, 300, 100), Vec3(0.5, 0.3, 0.3)));
	s.addLight(Sphere(10, Vec3(300, 300, -50), Vec3(0.8, 0.65, 0.6)));
	*/

	Scene s(Camera(600, 600, 100, Vec3(300, 300, -350)));
	// s.addSphere(Sphere(59, Vec3(345, 250, 220), Vec3(1, 1, 1)));
	s.addSphere(Sphere(50, Vec3(200, 550, 50), Vec3(1, 1, 1)));
	s.addSphere(Sphere(100, Vec3(300, 500, 150), Vec3(1, 1, 1)));
	// s.addLight(Sphere(10, Vec3(500, 300, 100), Vec3(0.3, 0.5, 0.3)));
	// s.addLight(Sphere(10, Vec3(100, 300, 100), Vec3(0.5, 0.3, 0.3)));
	// s.addLight(Sphere(10, Vec3(300, 300, -50), Vec3(0.8, 0.65, 0.6)));

	s.addSurfaceLight(SurfaceLight(50, Vec3(400, 300, 100), Vec3(100, 100, 100), Vec3(0.3, 0.5, 0.3)));
	s.addSurfaceLight(SurfaceLight(50, Vec3(200, 300, 100), Vec3(100, 100, 100), Vec3(0.5, 0.3, 0.3)));
	s.addSurfaceLight(SurfaceLight(120, Vec3(300, 300, -100), Vec3(100, 100, 100), Vec3(0.8, 0.65, 0.6)));

	s.createImage();
}



