#pragma once


string ReadFile(const char* filePath);

void CreateShaderProgramFromFiles(const char* vsPath, const char* fsPath, GLuint& shader);
void CompileShader(const char* vsCode, const char* fsCode, GLuint& shader);
GLuint AddShader(const char* shaderCode, GLenum shaderType);


// GLuint loadBMP_custom(const char* imagepath);
