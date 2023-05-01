#define STB_IMAGE_IMPLEMENTATION

#include "pch.h"

#include "Func/LoadFunc.h"
#include "Obj/object.h"
#include "Obj/Camera.h"
#include "Texture/texture.h"



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

	//==========
	// texture ���ε�
	//==========
	
	unique_ptr<Texture> texManager = make_unique<Texture>();
	texManager->LoadTex("Texture/tree_default_Albedo.png", "Tree_Col");
	texManager->LoadTex("Texture/tree_default_Normal.png", "Tree_Nor");
	texManager->LoadTex("Texture/tree_default_AO.png", "Tree_Height");

	//==========
	// �� �����
	//==========

	vector<Object> objs;

	objs.push_back(Object("Shader/VS.glsl", "Shader/FS.glsl", "Model/tree.obj"));

	glm::mat4 World = glm::scale(glm::mat4(1.0f),glm::vec3(0.05));



	objs[0].SetWorld(World);

	objs[0].SetTexID(texManager->GetTex("Tree_Col"));
	objs[0].SetNormalTexID(texManager->GetTex("Tree_Nor"));



	
	// ī�޶� ����
	Camera mainCam(window, framebuf_width, framebuf_height);

	//=============
	//�� �� �� �� ��
	//=============

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mainCam.update();
		
		for (unsigned int i = 0; i < objs.size(); ++i) {
			objs[i].SetLightDir(mainCam.GetDirection());
			objs[i].SetCameraPos(mainCam.GetPos());
			objs[i].draw(mainCam.GetView(), mainCam.GetProj());
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}