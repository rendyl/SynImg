#include "Scene.h"
#include "TP1.h"
#include "TP2.h"

#include <algorithm>
#include <iostream>

int main()
{	
	Scene s(Camera(600, 600, 100, Vec3(300, 300, -350)));
	
	// Pretty Light Scene
	// s.addSphere(Sphere(50, Vec3(200, 550, 50), Vec3(1, 1, 1), 0));
	// s.addSphere(Sphere(100, Vec3(300, 500, 150), Vec3(1, 1, 1), 0));
	// s.addLight(Sphere(10, Vec3(500, 300, 0), Vec3(0.6, 1, 0.6), 0));
	// s.addLight(Sphere(10, Vec3(100, 300, 0), Vec3(1, 0.6, 0.6), 0));
	// s.addLight(Sphere(10, Vec3(300, 300, -50), Vec3(0.8, 0.65, 0.6), 0));

	// Pretty Surface Light Scene
	// s.addSphere(Sphere(50, Vec3(200, 550, 50), Vec3(1, 1, 1), 0));
	// s.addSphere(Sphere(100, Vec3(300, 500, 150), Vec3(1, 1, 1), 0));
	// s.addSurfaceLight(SurfaceLight(50, Vec3(400, 300, 100), Vec3(100, 100, 100), Vec3(0.3, 0.5, 0.3)));
	// s.addSurfaceLight(SurfaceLight(50, Vec3(200, 300, 100), Vec3(100, 100, 100), Vec3(0.5, 0.3, 0.3)));
	// s.addSurfaceLight(SurfaceLight(70, Vec3(300, 300, -150), Vec3(300, 300, 100), Vec3(0.8, 0.65, 0.65)));


	// Chocolate Render
	// s.addSphere(Sphere(50, Vec3(200, 550, 50), Vec3(1, 1, 1), 1));
	// s.addSphere(Sphere(50, Vec3(400, 550, 50), Vec3(1, 1, 1), 1.5));
	// s.addSphere(Sphere(100, Vec3(300, 500, 150), Vec3(1, 1, 1), 0.9));
	// s.addSurfaceLight(SurfaceLight(50, Vec3(300, 100, 100), Vec3(300, 300, 300), Vec3(0.8, 0.65, 0.65)));

	// Box test
	
	
	for (int i = 0; i < 29; i++)
	{
		for (int j = 0; j < 29; j++)
		{
			for (int z = 0; z < 10; z++)
			{
				if (j % 10 == 0);
				else if (i < 10 && j < 10) s.addSphere(Sphere(6, Vec3(15 + 20 * i, 15 + 20 * j, 200 + 20 * z), Vec3(1, 1, 1), 0.9));
				else if (i % 10 == 0) s.addSphere(Sphere(6, Vec3(15 + 20 * i, 15 + 20 * j, 200 + 20 * z), Vec3(1, 1, 1), 0.9));
				else if (j > 20) s.addSphere(Sphere(6, Vec3(15 + 20 * i, 15 + 20 * j, 200 + 20 * z), Vec3(1, 1, 1), 0.9));
			}
		}
	}
	
	
	//s.addSphere(Sphere(6, Vec3(300, 300, 200), Vec3(1, 1, 1), 0.9));
	//s.addSphere(Sphere(6, Vec3(200, 200, 200), Vec3(1, 1, 1), 0.9));
	//s.addSphere(Sphere(6, Vec3(100, 200, 200), Vec3(1, 1, 1), 0.9));
	//s.addSphere(Sphere(6, Vec3(100, 200, 300), Vec3(1, 1, 1), 0.9));

	std::vector<Box> tabBoxies;

	for (int i = 6; i < s.tabSphere.size(); i++)
	{
		Box b(s.tabSphere[i], i);
		// std::cout << "i" << i << std::endl;
		// std::cout << "x1 " << b.pt1.x << " y1 " << b.pt1.y << " z1 " << b.pt1.z << std::endl;
		// std::cout << "x2 " << b.pt2.x << " y2 " << b.pt2.y << " z2 " << b.pt2.z << std::endl;
		tabBoxies.push_back(b);
	}

	s.tBox = s.tBox->createTreeFromBoxies(tabBoxies);

	// Test Union

	//for (int i = 0; i < tabBoxies.size(); i = i + 2)
	//{
	//	Box b2;
	//	(i + 1 < tabBoxies.size()) ? b2 = tabBoxies[i].unionBox(tabBoxies[i + 1]) : b2 = tabBoxies[i];
	//	s.addBox(b2);
	//}

	//s.addSurfaceLight(SurfaceLight(50, Vec3(300, 100, 100), Vec3(300, 300, 300), Vec3(0.8, 0.65, 0.65)));
	s.addLight(Sphere(10, Vec3(300, 300, 100), Vec3(0.8, 0.65, 0.6), 0));

	// s.addSphere(Sphere(50, Vec3(200, 550, 50), Vec3(1, 1, 1), 1));
	// s.addSphere(Sphere(50, Vec3(400, 550, 50), Vec3(1, 1, 1), 1.5));
	
	s.createImage();


}



