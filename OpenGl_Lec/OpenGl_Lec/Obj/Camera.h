#pragma once
class Camera
{
private:
	glm::mat4 View;
	glm::mat4 Proj;

	
private:
	double xpos, ypos;
	int width, heigth;

	glm::vec3 position;
	float horizontalAngle; 
	float verticalAngle;
	float FoV;
	float speed;
	float mouseSpeed;


private:
	glm::vec3 direction;
	glm::vec3 right;
	glm::vec3 up;
	GLFWwindow* window;

private:
	// for delta time
	double currentTime;
	double lastTime;
	float deltaTime;

public:
	Camera(GLFWwindow* _window,int w, int h);

	const glm::mat4 &GetView() { return View; }
	const glm::mat4 &GetProj() { return Proj; }
	const glm::vec3& GetPos() { return position; }
	const glm::vec3 &GetDirection() { return direction; }
	void update();
};

