#include "pch.h"
#include "Camera.h"

Camera::Camera(GLFWwindow* _window, int w, int h):
	window(_window),
	View(glm::lookAt(glm::vec3(0,0,5), glm::vec3(0, 0, 4), glm::vec3(0, 1, 0))),
	Proj(glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 100.0f)),
	xpos(0.),
	ypos(0.),
	width(w),
	heigth(h)
{
	position = glm::vec3(0, 10, 10);
	// 수평각 : -Z 방향으로
	horizontalAngle = 3.14f;
	// 수직각 : 0, 수직을 바라봅니다. 
	verticalAngle = 0.0f;
	// 초기 FOV값
	FoV = 45.0f;
	speed = 0.001f; // 초당 3 unitsl
	mouseSpeed = 0.0001f;

	direction = glm::vec3(0, 0, -1);
	right = glm::vec3(1, 0, 0);
	up = glm::cross(right, direction);

	lastTime = glfwGetTime();
	currentTime = glfwGetTime();
}

void Camera::update()
{
	currentTime = glfwGetTime();
	deltaTime = float(currentTime - lastTime);

	glfwGetCursorPos(window, &xpos, &ypos);
	glfwSetCursorPos(window, width/2, heigth/2);

	horizontalAngle += mouseSpeed * deltaTime * float(width / 2 - xpos);
	verticalAngle += mouseSpeed * deltaTime * float(heigth / 2 - ypos);

	direction = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	up = glm::cross(right, direction);

	
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		position += direction * deltaTime * speed;
	}
	// 뒤로
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		position -= direction * deltaTime * speed;
	}
	// 오른쪽
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		position += right * deltaTime * speed;
	}
	// 왼쪽
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		position -= right * deltaTime * speed;
	}

	Proj = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// 카메라 행렬
	View = glm::lookAt(
		position,           
		position + direction, 
		up                  
	);
}
