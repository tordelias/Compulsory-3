#include "Player.h"
#include <iostream>




float Player::GetA()
{
    return a;
}

//void Player::ConstructVBO(std::vector<GLfloat> flattenedVertices, bool update)
//{
//	
//	
//
//	// Update VBO data if necessary
//	//if (update) {
//	//	VBO1.UpdateData(flattenedVertices.data(), flattenedVertices.size() * sizeof(GLfloat));
//	//}
//	//else {
//	//	VAO5.Bind();
//	//	VBO1.UpdateData(flattenedVertices.data(), flattenedVertices.size() * sizeof(GLfloat));
//	//	VAO5.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
//	//	VAO5.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	//	VAO5.Unbind();
//	//	VBO1.Unbind();
//	//}
//	
//	
//}

void Player::DeleteVBOANDVAO()
{
	VAO5.Delete();

}

void Player::UnbindVAO()
{
	VAO5.Unbind();
}

void Player::BindVAO()
{
	VAO5.Bind();
}

void Player::UpdateVertices(float Xspeed, float Yspeed, float Zspeed, glm::vec3 velocity)
{
	position.x += Xspeed;
	position.y += Yspeed;
position.z += Zspeed;

}

VBO Player::GetVBO()
{
	return VBO1;
}

void Player::inputs(GLFWwindow* window)
{
	float speed = 0.1f;
	float translationSpeed = speed;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

		UpdateVertices(0, 0, -speed, glm::vec3(0, 0, 1));
		//position.z -= translationSpeed;

	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

		UpdateVertices(0, 0, speed, glm::vec3(0, 0, 1));
		//position.z += translationSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {

		UpdateVertices(-speed, 0, 0, glm::vec3(1, 0, 0));
		//position.x -= translationSpeed;

	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {

		UpdateVertices(speed, 0, 0, glm::vec3(1, 0, 0));
		//position.x += translationSpeed;
	}

	

	double mouseX;
	double mouseY;
	const unsigned int width = 800;
	const unsigned int height = 800;
	// Fetches the coordinates of the cursor
	glfwGetCursorPos(window, &mouseX, &mouseY);

	// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
	// and then "transforms" them into degrees 

	float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;


	// Rotates the Orientation left and right
	Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
}



bool Player::CheckCollision( Player& otherCube)
{
	float distance_centers = glm::length(position - otherCube.position);

	// If the distance between centers is less than the sum of the radii, collision occurs
	if (distance_centers <= (sphere_radius + otherCube.sphere_radius)) {

		float minimuntranslation = sphere_radius +otherCube.sphere_radius - distance_centers;
		auto dirvec = glm::normalize(position - otherCube.position);
		position += dirvec * minimuntranslation;
		//otherCube.position += dirvec * minimuntranslation;

		otherCube.move = false;
		return true; 

	}
	else {
;
		otherCube.move = true;
	}


	// No collision detected
	return false;
}




std::vector<double> computeDerivative(const std::vector<double>& coefficients) {
	std::vector<double> derivativeCoefficients;

	// Compute derivative coefficients
	for (size_t i = 1; i < coefficients.size(); ++i) {
		derivativeCoefficients.push_back(i * coefficients[i]);
	}

	return derivativeCoefficients;
}

double evaluatePolynomial(const std::vector<double>& coefficients, double x) {
	double result = 0.0;
	double power = 1.0;
	for (size_t i = 0; i < coefficients.size(); ++i) {
		result += coefficients[i] * power;
		power *= x;
	}
	return result;
}

double computeDerivativeAtPoint(const std::vector<double>& coefficients, double x) {
	std::vector<double> derivativeCoefficients = computeDerivative(coefficients);
	return evaluatePolynomial(derivativeCoefficients, x);
}


void Player::Patrol(std::vector<double> coefficients)
{
	//if(move)
	//{
		double Derivative = computeDerivativeAtPoint(coefficients, xvalue) / 4096;
		for (Vertex& vertex : mVertecies) {
			position.x += xspeed / 2;
			if (xPositiveDir) position.z += Derivative;
			else position.z -= Derivative;
		}
		xvalue += xspeed;
		if (xvalue >= 1) {
			xspeed *= -1;
			xPositiveDir = false;
		}
		else if (xvalue <= -0.25) {
			xspeed *= -1;
			xPositiveDir = true;
		}
	//}
}


glm::vec3 Player::calculateBarycentricCoordinates(glm::vec3& cpoint, bool ground)
{
	float u, v, w; 

	glm::vec3 point = cpoint;

	for (int i = 0; i < mVertecies.size() - 2; i += 3)
	{

		glm::vec3 v0 = glm::vec3((mVertecies[i].x * size1) + position.x, (mVertecies[i].y * size1) + position.y, (mVertecies[i].z * size1) + position.z);
		glm::vec3 v1 = glm::vec3((mVertecies[i + 1].x * size1) + position.x, (mVertecies[i + 1].y * size1) + position.y, (mVertecies[i + 1].z * size1) + position.z);
		glm::vec3 v2 = glm::vec3((mVertecies[i + 2].x * size1) + position.x, (mVertecies[i + 2].y * size1) + position.y, (mVertecies[i + 2].z * size1) + position.z);



		if (!ground)
		{

			v0.y = 0;
			v1.y = 0;
			v2.y = 0;
			point.y = 0;


		}


		glm::vec3 v0v1(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
		glm::vec3 v0v2(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
		glm::vec3 v0p(point.x - v0.x, point.y - v0.y, point.z - v0.z);

		// Compute dot products
		float dot00 = glm::dot(v0v1, v0v1);
		float dot01 = glm::dot(v0v1, v0v2);
		float dot02 = glm::dot(v0v1, v0p);
		float dot11 = glm::dot(v0v2, v0v2);
		float dot12 = glm::dot(v0v2, v0p);

		// Compute barycentric coordinates
		float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
		 u = (dot11 * dot02 - dot01 * dot12) * invDenom;
		 v = (dot00 * dot12 - dot01 * dot02) * invDenom;
		 w = 1 - u - v;
		if (u > 0 && v > 0 && w > 0) {
			if (ground)
			{
				float heightV6 = v0.y * w + v1.y * u + v2.y * v;
				cpoint.y = heightV6 + 1; // -19 is planePosition.y -2, offset to have player above 
				//std::cout << "Collision " << u << std::endl;
			}
			else
			{
				cpoint.y += 1;
				//std::cout << "Collision " << u << std::endl;
			}
		}

		//else {
		//    std::cout << "x: " << u << std::endl;
		//    std::cout << "y: " << v << std::endl;
		//    std::cout << "z: " << w << std::endl;
		//}




	}

	return glm::vec3(u, v, w);
}
