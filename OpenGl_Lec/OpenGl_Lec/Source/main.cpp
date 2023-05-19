#define STB_IMAGE_IMPLEMENTATION

#include "pch.h"

#include "Func/LoadFunc.h"
#include "Object/object.h"
#include "Camera/Camera.h"
#include "Texture/texture.h"



int main(void)
{
	if (!glfwInit())
		exit(EXIT_FAILURE);

	// openGL 4.5 환경에서 수행
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	// 윈도우 생성
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
	// texture 업로드
	//==========
	
	unique_ptr<Texture> texManager = make_unique<Texture>();
	texManager->LoadTex("Texture/tree_default_Albedo.png", "Tree_Col");
	texManager->LoadTex("Texture/tree_default_Normal.png", "Tree_Nor");
	texManager->LoadTex("Texture/tree_default_AO.png", "Tree_Height");
	texManager->LoadTex("Texture/tex.bmp", "Gisan");

	//==========
	// 씬 만들기
	//==========

	vector<Object> objs;

	objs.push_back(Object("Shader/VS.glsl", "Shader/NormalMappingFragShader.glsl", "Model/tree.obj"));

	glm::mat4 World = glm::scale(glm::mat4(1.0f),glm::vec3(0.05f));



	objs[0].SetWorld(World);

	objs[0].SetTexID(texManager->GetTex("Tree_Col"));
	objs[0].SetNormalTexID(texManager->GetTex("Tree_Nor"));

	objs.push_back(Object("Shader/VS.glsl", "Shader/FragShader.glsl", "Model/plane.obj"));

	objs[1].SetWorld(glm::mat4(1.0f));
	//objs[1].SetTexID(texManager->GetTex("Gisan"));

	
	// 카메라 선언
	Camera mainCam(window, framebuf_width, framebuf_height);

	//=============
	//메 인 루 프 다
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
		
		unsigned int ShadowMapFBO;
		glGenFramebuffers(1, &ShadowMapFBO);

		const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

		unsigned int ShadowMap;
		glGenTextures(1, &ShadowMap);
		glBindTexture(GL_TEXTURE_2D, ShadowMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
			SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, ShadowMap, 0);

		for (unsigned int i = 0; i < objs.size(); ++i) {
			objs[i].SetCameraPos(mainCam.GetPos());
			objs[i].draw(mainCam.GetView(), mainCam.GetProj());
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}