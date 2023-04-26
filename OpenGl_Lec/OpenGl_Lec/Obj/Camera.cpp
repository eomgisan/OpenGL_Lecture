#include "pch.h"
#include "Camera.h"

Camera::Camera(GLFWwindow* _window, int w, int h):
	window(_window),
	View(glm::lookAt(glm::vec3(0,0,5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0))),
	Proj(glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 100.0f)),
	xpos(0.),
	ypos(0.),
	width(w),
	heigth(h)
{
	position = glm::vec3(0, 0, 5);
	// ���� : -Z ��������
	horizontalAngle = 3.14f;
	// ������ : 0, ������ �ٶ󺾴ϴ�. 
	verticalAngle = 0.0f;
	// �ʱ� FOV��
	FoV = 45.0f;
	speed = 0.003f; // �ʴ� 3 unitsl
	mouseSpeed = 0.0005f;

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
	// �ڷ�
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		position -= direction * deltaTime * speed;
	}
	// ������
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		position += right * deltaTime * speed;
	}
	// ����
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		position -= right * deltaTime * speed;
	}

	Proj = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// ī�޶� ���
	View = glm::lookAt(
		position,           // ī�޶�� ���� �ְ�, 
		position + direction, // ���� ��ǥ�� ���� �־��.  : ���� ��ġ����, "direction"�� �����ּ���. 
		up                  // �Ӹ��� �����ְ��. (set to 0,-1,0 to look upside-down)
	);
}
