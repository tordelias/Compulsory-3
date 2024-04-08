#pragma once
#include "Resources/Shaders/VBO.h"
#include "Resources/Shaders/VAO.h"
#include <vector>
#include <array>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<GLFW/glfw3.h>
#include <cmath>
#include "Table.h"
#include "Pokal.h"
#include "Construct.h"
#include<glm/gtx/rotate_vector.hpp>

class Pokal;


using namespace std;

class Player {
private:


public:
std::vector<Vertex> mVertecies;

	glm::vec3 position;
	float r, g, b;
	glm::vec3 velocity;
	float sphere_radius = 0;
	bool move = true; 
	float sensitivity = 100.0f;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	std::array<glm::vec3, 4> planePoints; 

	float size1 = 1.f; 
	
	VAO VAO5;
	VBO VBO1;
	
	
	
	Player(float scale, const glm::vec3& initialPosition, float red = 1.0f, float green = 1.0f, float blue = 1.0f, float figure = 1.f)
		: a(scale), position(initialPosition), velocity(glm::vec3(0.0f)), r(red), g(green), b(blue), VBO1()
	{
		Construct con;

		//Cube
		if (figure == 1)
		{
			mVertecies = con.Cube(glm::vec3(red, green, blue));

			VAO5.Bind();
			VBO1.Bind();
			glBufferData(GL_ARRAY_BUFFER, mVertecies.size() * sizeof(Vertex), mVertecies.data(), GL_STATIC_DRAW);
			VAO5.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
			VAO5.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			VAO5.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			VAO5.Unbind();
			VBO1.Unbind();

			planePoints[0] = glm::vec3(-scale, scale, scale) + position;
			planePoints[1] = glm::vec3(scale, scale, scale) + position;
			planePoints[2] = glm::vec3(scale, scale, -scale) + position;
			planePoints[3] = glm::vec3(-scale, scale, -scale) + position;
		}
		else if (figure == 2)
		{
			mVertecies = con.Table(glm::vec3(red, green, blue));

			VAO5.Bind();
			VBO1.Bind();
			glBufferData(GL_ARRAY_BUFFER, mVertecies.size() * sizeof(Vertex), mVertecies.data(), GL_STATIC_DRAW);
			VAO5.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
			VAO5.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			VAO5.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			VAO5.Unbind();
			VBO1.Unbind();
		}

		else if (figure == 3)
		{
			mVertecies = con.House(glm::vec3(red, green, blue));

			VAO5.Bind();
			VBO1.Bind();
			glBufferData(GL_ARRAY_BUFFER, mVertecies.size() * sizeof(Vertex), mVertecies.data(), GL_STATIC_DRAW);
			VAO5.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
			VAO5.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			VAO5.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			VAO5.Unbind();
			VBO1.Unbind();
		}

		else if (figure == 4)
		{
			mVertecies = con.NotAPlane(glm::vec3(red, green, blue));

			VAO5.Bind();
			VBO1.Bind();
			glBufferData(GL_ARRAY_BUFFER, mVertecies.size() * sizeof(Vertex), mVertecies.data(), GL_STATIC_DRAW);
			VAO5.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
			VAO5.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			VAO5.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			VAO5.Unbind();
			VBO1.Unbind();

			planePoints[0] = glm::vec3(-scale, scale, scale) + position;
			planePoints[1] = glm::vec3(scale, scale, scale) + position;
			planePoints[2] = glm::vec3(scale, scale * 1.5f, -scale) + position;
			planePoints[3] = glm::vec3(-scale, scale, -scale) + position;
		}
		else
		{
			mVertecies = con.Cube(glm::vec3(red, green, blue));

			VAO5.Bind();
			VBO1.Bind();
			glBufferData(GL_ARRAY_BUFFER, mVertecies.size() * sizeof(Vertex), mVertecies.data(), GL_STATIC_DRAW);
			VAO5.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
			VAO5.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			VAO5.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			VAO5.Unbind();
			VBO1.Unbind();
		}
		

		//Table
		//mVertecies = con.Table(a, initialPosition, glm::vec3(red, green, blue));

		//collitionSphere
		sphere_radius = a; 
		size1 = scale;


		//flattenVertices();
	}
	float GetA();
	/*std::vector<GLfloat> getFlattenedVertices() const;*/
	/*void ConstructVBO(std::vector<GLfloat> flattenedVertices, bool update);*/
	void DeleteVBOANDVAO();
	void UnbindVAO();
	void BindVAO();
	void UpdateVertices(float Xspeed, float Yspeed, float Zspeed, glm::vec3 velocity);
	VBO GetVBO();
	void inputs(GLFWwindow* window);

	void Patrol(std::vector<double> coefficients);
	
	bool CheckCollision( Player& otherCube);
	


	glm::vec3 calculateBarycentricCoordinates( glm::vec3& cpoint, bool ground);

public:
	float a{ 1.0f };
	double xvalue = 0;
	double xspeed = 0.001;
	bool xPositiveDir = true;


};