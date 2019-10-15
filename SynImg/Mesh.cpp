#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Mesh.h"

bool Mesh::parse(std::string filename)
{
	int nv, nf;
	/* Container holding last line read */

	std::string readLine;

	/* Containers for delimiter positions */

	int delimiterPos_1, delimiterPos_2, delimiterPos_3, delimiterPos_4;

	/* Open file for reading */

	std::ifstream in(filename.c_str());

	/* Check if file is in OFF format */

	getline(in, readLine);
	if (readLine != "OFF")
	{
		std::cout << "The file to read is not in OFF format." << std::endl;
		return false;
	}

	/* Read values for Nv and Nf */

	getline(in, readLine);
	delimiterPos_1 = (int)readLine.find(" ", 0);
	nv = atoi(readLine.substr(0, delimiterPos_1 + 1).c_str());
	delimiterPos_2 = (int)readLine.find(" ", delimiterPos_1);
	nf = atoi(readLine.substr(delimiterPos_1, delimiterPos_2 + 1).c_str());

	/* Vertices */

	for (int n = 0; n < nv; n++)
	{
		Vec3 v;
		getline(in, readLine);
		delimiterPos_1 = (int)readLine.find(" ", 0);
		v.x = (float)atof(readLine.substr(0, delimiterPos_1).c_str());
		delimiterPos_2 = (int)readLine.find(" ", delimiterPos_1 + 1);
		v.y = -1*(float)atof(readLine.substr(delimiterPos_1, delimiterPos_2).c_str());
		delimiterPos_3 = (int)readLine.find(" ", delimiterPos_2 + 1);
		v.z = (float)atof(readLine.substr(delimiterPos_2, delimiterPos_3).c_str());
		//std::cout << "Vx " << v.x << " Vy " << v.y << " Vz " << v.z << std::endl;
		vertices.push_back(v);
	}

	/* Façades */

	for (int n = 0; n < nf; n++)
	{
		getline(in, readLine);
		delimiterPos_1 = (int)readLine.find(" ", 0);
		delimiterPos_2 = (int)readLine.find(" ", delimiterPos_1 + 1);
		int indice1 = (int)atof(readLine.substr(delimiterPos_1, delimiterPos_2).c_str());
		delimiterPos_3 = (int)readLine.find(" ", delimiterPos_2 + 1);
		int indice2 = (int)atof(readLine.substr(delimiterPos_2, delimiterPos_3).c_str());
		delimiterPos_4 = (int)readLine.find(" ", delimiterPos_3 + 1);
		int indice3 = (int)atof(readLine.substr(delimiterPos_3, delimiterPos_4).c_str());
		//std::cout << "f0 " << indice1 << " f1 " << indice2 << " f2 " << indice3 << std::endl;
		facades.push_back(Vec3(indice1, indice2, indice3));
	}

	return true;
}

void Mesh::createMesh(Vec3 posi, float size, Vec3 color, float albedo)
{
	position = posi;
	taille = size;

	float x_min = vertices[0].x;
	float y_min = vertices[0].y;
	float z_min = vertices[0].z;
	float x_max = vertices[0].x;
	float y_max = vertices[0].y;
	float z_max = vertices[0].z;

	/* Centrer l'objet */

	Vec3 somme_vertices = vertices[0];
	size_t vertices_count = vertices.size();
	float norm_max = vertices[0].norm();
	for (unsigned int i = 1; i < vertices_count; i++)
	{
		somme_vertices = somme_vertices + vertices[i];

		if (vertices[i].norm() > norm_max) norm_max = vertices[i].norm();
		if (vertices[i].x < x_min) x_min = vertices[i].x;
		if (vertices[i].y < y_min) y_min = vertices[i].y;
		if (vertices[i].z < z_min) z_min = vertices[i].z;
		if (vertices[i].x > x_max) x_max = vertices[i].x;
		if (vertices[i].y > y_max) y_max = vertices[i].y;
		if (vertices[i].z > z_max) z_max = vertices[i].z;
	}
	
	norm_max /= taille;

	Vec3 centre_gravite = somme_vertices / (float)vertices_count;
	Vec3 offset = position;
	offset = offset - (centre_gravite / norm_max);

	/* Normaliser sa taille */

	for (unsigned int i = 0; i < vertices_count; i++) vertices[i] = vertices[i] / norm_max;

	/* Création de la boîte englobante */

	// x_min = x_min / norm_max + offset.x;
	// y_min = y_min / norm_max + offset.y;
	// z_min = z_min / norm_max + offset.z;
	// x_max = x_max / norm_max + offset.x;
	// y_max = y_max / norm_max + offset.y;
	// z_max = z_max / norm_max + offset.z;

	// Box box;
	// box.lb = { x_min, y_min, z_min };
	// box.rt = { x_max, y_max, z_max };
	// box.depth = 0;
	// Objects objects;

	/* Création des triangles */

	size_t facades_count = facades.size();
	for (unsigned int i = 0; i < facades_count; i++)
	{
		// Object triangle;
		// triangle.material = mesh.material;
		// triangle.geom.type = TRIANGLE;

		Vec3 v0 = vertices[(int)facades[i].x] + offset;
		Vec3 v1 = vertices[(int)facades[i].y] + offset;
		Vec3 v2 = vertices[(int)facades[i].z] + offset;

		// std::cout << "tri" << (int)facades[i].x << std::endl;
		Triangle tri = Triangle(v0, v1, v2, color, albedo);

		// v0.display();
		// std::cout << " x " << tri.vertice1.x << std::endl;


		// triangle.geom.triangle.v0 = mesh.vertices.at((int)mesh.facades.at(i).x) + offset;
		// triangle.geom.triangle.v1 = mesh.vertices.at((int)mesh.facades.at(i).y) + offset;
		// triangle.geom.triangle.v2 = mesh.vertices.at((int)mesh.facades.at(i).z) + offset;
		triangles.push_back(tri);
	}

	// box.objects = objects;
	// boxs.push_back(box);
}