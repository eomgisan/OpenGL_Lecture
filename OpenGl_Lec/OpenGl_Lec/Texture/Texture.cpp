#include "pch.h"
#include "Texture.h"

void Texture::LoadTex(const char * path, string texName)
{

	if (texMap.find(texName) != texMap.end())
	{
		cout << "이미 존재하는 텍스처" << '\n';
		return;
	}

	int imgWidth, imgHeight, imgChannels;
	GLuint textureID;

	// OpenGL Texture를 생성합니다. 

	glGenTextures(1, &textureID);

	// 새 텍스처에 "Bind" 합니다 : 이제 모든 텍스처 함수들은 이 텍스처를 수정합니다. 
	// "Bind" the newly created texture : all future texture functions will modify this texture

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data = stbi_load(path, &imgWidth, &imgHeight, &imgChannels, 0);
	if (data) {
		cout << "이미지 로드 성공이염, 높이:" << imgHeight << "/ 길이: " << imgWidth << endl;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "이미지 로드 에러염" << endl;
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);


	texMap[texName] = textureID;
}

GLuint Texture::GetTex(string texName)
{
	if (texMap.find(texName) != texMap.end()) 
		return texMap[texName];
	
	return 0;
}
