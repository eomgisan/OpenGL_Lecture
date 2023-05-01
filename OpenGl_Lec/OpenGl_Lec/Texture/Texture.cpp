#include "pch.h"
#include "Texture.h"

void Texture::LoadTex(const char * path, string texName)
{

	if (texMap.find(texName) != texMap.end())
	{
		cout << "�̹� �����ϴ� �ؽ�ó" << '\n';
		return;
	}

	int imgWidth, imgHeight, imgChannels;
	GLuint textureID;

	// OpenGL Texture�� �����մϴ�. 

	glGenTextures(1, &textureID);

	// �� �ؽ�ó�� "Bind" �մϴ� : ���� ��� �ؽ�ó �Լ����� �� �ؽ�ó�� �����մϴ�. 
	// "Bind" the newly created texture : all future texture functions will modify this texture

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data = stbi_load(path, &imgWidth, &imgHeight, &imgChannels, 0);
	if (data) {
		cout << "�̹��� �ε� �����̿�, ����:" << imgHeight << "/ ����: " << imgWidth << endl;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "�̹��� �ε� ������" << endl;
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
