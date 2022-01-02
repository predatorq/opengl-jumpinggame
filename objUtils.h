#pragma once
#include <glm.hpp>
#include <ext.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

typedef struct {
	float point[4];
	float normal[4];
	//float color[4];
	//glm::vec2 texcoord;
} Vertex;

vector<Vertex> LoadOBJ(istream& in);