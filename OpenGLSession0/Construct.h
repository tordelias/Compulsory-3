#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
struct Vertex
{
	float x, y, z;
	float r, g, b;
	float u, v; 

};
class Construct
{
public:
	std::vector<Vertex> Cube(glm::vec3 Color);
	std::vector<Vertex> Table(glm::vec3 Color);
	std::vector<Vertex> House( glm::vec3 Color);
	std::vector<Vertex> NotAPlane(glm::vec3 Color);


	float randomFloat() {
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}
};

