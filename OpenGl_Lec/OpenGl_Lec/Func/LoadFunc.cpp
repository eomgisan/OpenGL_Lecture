#include "pch.h"
#include "LoadFunc.h"




// ���� �о�ͼ� string�� ����
string ReadFile(const char* filePath)
{
	string content;
	ifstream fileStream(filePath, ios::in);

	while (!fileStream.is_open())
	{
		cout << "���� ��� Ȯ��";
		return "";
	}

	string line = "";
	while (!fileStream.eof())
	{
		getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

//=============
// ���̴� �ε�
//=============

GLuint AddShader(const char* shaderCode, GLenum shaderType)
{

	GLuint new_shader = glCreateShader(shaderType);

	const GLchar* code[1];
	code[0] = shaderCode;

	glShaderSource(new_shader, 1, code, NULL);

	GLint result = 0;
	GLchar err_log[1024] = { 0 };

	glCompileShader(new_shader);



	// ������ ��� Ȯ���� ���� �ڵ�
	glGetShaderiv(new_shader, GL_COMPILE_STATUS, &result);


	if (result != GL_TRUE)
	{
		glGetShaderInfoLog(new_shader, sizeof(err_log), NULL, err_log);
		// �����α� Ȯ��

		printf("Error compiling the %d shader: '%s'\n", shaderType, err_log);

		return 0;
	}
	return new_shader;
}


// ���̴� �������ϱ�
void CompileShader(const char* vsCode, const char* fsCode, GLuint &shader)
{
	GLuint vs, fs;

	shader = glCreateProgram();

	if (!shader)
	{
		printf("Error: Cannot create shader program.");
		return;
	}


	// �ش� Ÿ������ ���̴� �����
	vs = AddShader(vsCode, GL_VERTEX_SHADER);
	fs = AddShader(fsCode, GL_FRAGMENT_SHADER);


	// ���̴� ��ũ
	glAttachShader(shader, vs);  // Attach shaders to the program for linking process.
	glAttachShader(shader, fs);

	GLint result = 0;
	GLchar err_log[1024] = { 0 };

	glLinkProgram(shader);  // Create executables from shader codes to run on corresponding processors.

	// ���� Ȯ�ο� �ڵ�
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(err_log), NULL, err_log);
		printf("Error linking program: '%s'\n", err_log);
		return;
	}
}


// ���̴� �ҷ����� ���̴� �������ϱ�
void CreateShaderProgramFromFiles(const char* vsPath, const char* fsPath, GLuint &shader)
{
	string vsFile = ReadFile(vsPath);
	string fsFile = ReadFile(fsPath);
	const char* vsCode = vsFile.c_str();
	const char* fsCode = fsFile.c_str();

	CompileShader(vsCode, fsCode, shader);
}



