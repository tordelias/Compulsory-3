#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib> 
#include <ctime> 
#include "Resources/Shaders/shaderClass.h"
#include "Resources/Shaders/VAO.h"
#include "Resources/Shaders/VBO.h"
#include "Resources/Shaders/EBO.h"

#include "Camera.h"

#include "Pokal.h"
#include "Player.h"
#include "LSM.h"
#include "SphereCollition.h"
#include "stb_image.h"
#include "Texture.h"



const unsigned int width = 800;
const unsigned int height = 800;
using namespace std;

void processInput(GLFWwindow* window);







int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGLProject", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	
	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800

	
	glViewport(0, 0, width, height);

	Shader shaderProgram("default.vert", "default.frag");
	shaderProgram.Activate();

	 


	



	//creating our objects in the scene


	Player myPlayer(1.0f, glm::vec3(0,0.5,40), 0.1f, 0.0f, 0.5f, 1);

	Player myPlane(40.f, glm::vec3(0, -41, 0), 0.f, 1.f, 0.f, 4); 

	Player myNPC(1.0f, glm::vec3(5, 0.5, 20), 0.1f, 0.4f, 0.5f, 1);




		//Texture

	Texture texture("textures/cool_Image.jpg", 1, shaderProgram);
	Texture texture1("textures/HARDASSPFP.jpg", 1, shaderProgram);
	//Texture texture2("textures/cobblestone.jpg", 2, shaderProgram);

	// Unbind all to prevent accidentally modifying them
	
	
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
	float scaleValue = 100.0f;
	

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	
	
	//Camera object
	Camera camera(width, height, glm::vec3(0.0f, 10.0f, 100.0f));
	
	//speed of cube
	float translationSpeed = 0.05f;
	//Collison 



	std::vector<double> patrolPoints = { -1 , 2, 1, -2, 2, 2 }; // points for patrolling
	LSM PatrolPath(patrolPoints, patrolPoints.size() / 2); // the degree of the function, f.exa x^2

	//SphereCollition sc(myPlayer, NPC);
	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	while (!glfwWindowShouldClose(window))
	{

		camera.Position = glm::vec3(myPlayer.position.x, myPlayer.position.y + 3, myPlayer.position.z +10);
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

		myPlane.calculateBarycentricCoordinates(myPlayer.position, myPlane.planePoints[0], myPlane.planePoints[1], myPlane.planePoints[2]); 
		myPlane.calculateBarycentricCoordinates(myPlayer.position, myPlane.planePoints[2], myPlane.planePoints[3], myPlane.planePoints[0]);

		myPlane.calculateBarycentricCoordinates(myNPC.position, myPlane.planePoints[0], myPlane.planePoints[1], myPlane.planePoints[2]);
		myPlane.calculateBarycentricCoordinates(myNPC.position, myPlane.planePoints[2], myPlane.planePoints[3], myPlane.planePoints[0]);

		myNPC.Patrol(PatrolPath.getCoefficients());
		processInput(window);
		myPlayer.inputs(window);
		camera.Inputs(window);
		//myPlayer.CheckCollision(myPlane);


		//Set render distance and FOV
		glm::mat4 viewproj= camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		glBindTexture(GL_TEXTURE_2D, texture.texture);
		glActiveTexture(GL_TEXTURE1);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, myPlayer.position);
		//model = glm::rotate(model, myPlayer.Orientation);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(viewproj*model));
		myPlayer.BindVAO();
		glDrawArrays(GL_TRIANGLES, 0, myPlayer.mVertecies.size());
		myPlayer.UnbindVAO();
		texture.UnbindTexture();

		//glBindTexture(GL_TEXTURE_2D, texture2.texture);
		//glActiveTexture(GL_TEXTURE2);

		glm::mat4 planeModel = glm::mat4(1.0f);
		planeModel = glm::translate(planeModel, myPlane.position);
		planeModel = glm::scale(planeModel, glm::vec3(40, 40, 40));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(viewproj * planeModel));
		myPlane.BindVAO();
		glDrawArrays(GL_TRIANGLES, 0, myPlane.mVertecies.size());
		myPlane.UnbindVAO();
		//texture2.UnbindTexture();

		glBindTexture(GL_TEXTURE_2D, texture1.texture);
		glActiveTexture(GL_TEXTURE1);
		glm::mat4 modelNPC = glm::mat4(1.0f);
		modelNPC = glm::translate(modelNPC, myNPC.position);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(viewproj * modelNPC));
		myNPC.BindVAO();
		glDrawArrays(GL_TRIANGLES, 0, myNPC.mVertecies.size());
		myNPC.UnbindVAO();
		texture1.UnbindTexture();



		
		
		
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	
	
	
	
	// Delete all the objects we've created
	
	myPlayer.VAO5.Delete();
	myPlane.VAO5.Delete();

	
	shaderProgram.Delete();
	
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}