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




/*
GLuint loadBMP_custom(const char* imagepath) {

	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	unsigned char* data;

	// Open the file
	FILE* file = fopen(imagepath, "rb");
	if (!file) { printf("Image could not be opened\n"); return 0; }

	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}

	// ����Ʈ �迭���� int ������ �н��ϴ�. 
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	// ��� BMP ���ϵ��� ������ �߸��Ǿ����ϴ�. ������ �������� Ȯ���غ��ϴ�. 
// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)    imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

	// ���� ����
	data = new unsigned char[imageSize];

	// ���Ͽ��� ���۷� ���� ������ �ֱ�. 
	fread(data, 1, imageSize, file);

	//���� ��� �޸� �ȿ� �����ϱ�, ������ �ݽ��ϴ�. 
	//Everything is in memory now, the file can be closed
	fclose(file);

	// OpenGL Texture�� �����մϴ�. 
	GLuint textureID;
	glGenTextures(1, &textureID);

	// �� �ؽ�ó�� "Bind" �մϴ� : ���� ��� �ؽ�ó �Լ����� �� �ؽ�ó�� �����մϴ�. 
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	

	// OpenGL���� �̹����� �Ѱ��ݴϴ�. 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
	return textureID;
}
*/
