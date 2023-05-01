#pragma once
class Texture
{
private:

	map<string, GLuint> texMap;

public:

	void LoadTex(const char * path, string texName);

	GLuint GetTex(string texName);
};

