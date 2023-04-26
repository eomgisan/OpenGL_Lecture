#pragma once
class Object
{
private:
	GLuint VAO, VBO, NBO, TBO, IBO, CBO;
    GLuint textureID;
private:
    GLuint shader;

private:
    GLuint WorldMatrixID;
    GLuint ViewMatrixID;
    GLuint ProjectionMatrixID;

    glm::mat4 World;

private:
// 라이팅용

private:
  
	vector<glm::vec3> vertices;
	vector<glm::vec2> texCoords;
    vector<glm::vec3> normals;

    vector<unsigned short> idx;



private:
    bool loadOBJ(const char* path);

public:
    
    Object(const char* vsPath, const char* fsPath, const char* objPath);
    ~Object();

public:
    void SetWorld(const glm::mat4& _world) { World = _world; }


    void SetColorBuffer(const vector<GLfloat> &g_color_buffer_data);
    void SetTexID(const GLuint& texId) { textureID = texId; }

    GLuint loadBMP_custom(const char * imagepath);

    void draw(glm::mat4 View, glm::mat4 Proj);
};

