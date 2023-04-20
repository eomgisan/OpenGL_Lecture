#include "pch.h"

#include "Obj/object.h"
#include "Obj/Camera.h"

static const vector<GLfloat> g_color_buffer_data = {
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
};


int main(void)
{
	if (!glfwInit())
		exit(EXIT_FAILURE);

	// openGL 4.5 ȯ�濡�� ����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	// ������ ����
	GLFWwindow* window = glfwCreateWindow(1080, 720, "ah..", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}


	glfwMakeContextCurrent(window);
	

	int framebuf_width, framebuf_height;
	glfwGetFramebufferSize(window, &framebuf_width, &framebuf_height);
	glViewport(0, 0, framebuf_width, framebuf_height);

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}





	// �������� ��Ʈ���� : 45�� �þ߰�, 4:3 ����, �þ� ���� : 0.1 ���� <--> 100 ����
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)framebuf_width / (float)framebuf_height, 0.1f, 100.0f);

	// ī�޶� ��Ʈ����
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // ī�޶�� (4,3,3) �� �ִ�. ���� ��ǥ����
		glm::vec3(0, 0, 0), // �׸��� ī�޶� ������ ����
		glm::vec3(0, 1, 0)  // �Ӹ��� �����̴� (0,-1,0 ���� �غ���, ������ �����̴�)
	);



	//==========
	// �� �����
	//==========
	vector<Object> objs;

	objs.push_back(Object("Shader/VS.vert", "Shader/FS.frag", "Obj/cube.obj"));

	glm::mat4 World = glm::mat4(1.0f);
	objs[0].SetWorld(World);
	objs[0].SetColorBuffer(g_color_buffer_data);
	
	
	// ī�޶� ����
	//Camera mainCam;

	//=============
	//�� �� �� �� ��
	//=============

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		

		for (unsigned int i = 0; i < objs.size(); ++i) {
			objs[i].draw(View, Projection);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}