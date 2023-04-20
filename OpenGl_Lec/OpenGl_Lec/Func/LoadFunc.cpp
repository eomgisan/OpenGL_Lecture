#include "pch.h"
#include "LoadFunc.h"




// 파일 읽어와서 string에 저장
string ReadFile(const char* filePath)
{
	string content;
	ifstream fileStream(filePath, ios::in);

	while (!fileStream.is_open())
	{
		cout << "파일 경로 확인";
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
// 쉐이더 로드
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



	// 컴파일 결과 확인을 위한 코드
	glGetShaderiv(new_shader, GL_COMPILE_STATUS, &result);


	if (result != GL_TRUE)
	{
		glGetShaderInfoLog(new_shader, sizeof(err_log), NULL, err_log);
		// 에러로그 확인

		printf("Error compiling the %d shader: '%s'\n", shaderType, err_log);

		return 0;
	}
	return new_shader;
}


// 쉐이더 컴파일하기
void CompileShader(const char* vsCode, const char* fsCode, GLuint &shader)
{
	GLuint vs, fs;

	shader = glCreateProgram();

	if (!shader)
	{
		printf("Error: Cannot create shader program.");
		return;
	}


	// 해당 타입으로 쉐이더 만들기
	vs = AddShader(vsCode, GL_VERTEX_SHADER);
	fs = AddShader(fsCode, GL_FRAGMENT_SHADER);


	// 쉐이더 링크
	glAttachShader(shader, vs);  // Attach shaders to the program for linking process.
	glAttachShader(shader, fs);

	GLint result = 0;
	GLchar err_log[1024] = { 0 };

	glLinkProgram(shader);  // Create executables from shader codes to run on corresponding processors.

	// 에러 확인용 코드
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(err_log), NULL, err_log);
		printf("Error linking program: '%s'\n", err_log);
		return;
	}
}


// 쉐이더 불러온후 쉐이더 컴파일하기
void CreateShaderProgramFromFiles(const char* vsPath, const char* fsPath, GLuint &shader)
{
	string vsFile = ReadFile(vsPath);
	string fsFile = ReadFile(fsPath);
	const char* vsCode = vsFile.c_str();
	const char* fsCode = fsFile.c_str();

	CompileShader(vsCode, fsCode, shader);
}



