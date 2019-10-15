#pragma once
#include <vector>
#include "Triangle.h"

class Mesh
{
	public :

		Vec3 position;
		float taille;

		std::vector<Vec3> vertices;
		std::vector<Vec3> facades;
		std::vector<Triangle> triangles;

		bool parse(std::string filename);
		void createMesh(Vec3 posi, float size, Vec3 color, float albedo);
};