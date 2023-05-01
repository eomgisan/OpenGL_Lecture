#pragma once
class Object
{
private:
	GLuint VAO, VBO, NBO, TBO, IBO, CBO;

    GLuint textureID;
    GLuint normalTexID;

private:
    GLuint shader;

private:
    GLuint WorldMatrixID;
    GLuint ViewMatrixID;
    GLuint ProjectionMatrixID;

    GLuint LightDirID;
    GLuint CameraPosID;

    glm::mat4 World;

private:
// �����ÿ�

private:
  
	vector<glm::vec3> vertices;
	vector<glm::vec2> texCoords;
    vector<glm::vec3> normals;

    vector<glm::vec3> tangents;
    vector<glm::vec3> bitangents;

    vector<unsigned short> idx;

    glm::vec3 camPos;
    glm::vec3 lightDir;


private:
    bool loadOBJ(const char* path);

public:
    
    Object(const char* vsPath, const char* fsPath, const char* objPath);
    ~Object();

public:
    void SetWorld(const glm::mat4& _world) { World = _world; }
    void SetCameraPos(const glm::vec3& _pos) { camPos = _pos; }
    void SetLightDir(const glm::vec3& _dir) { lightDir = _dir; }
    void SetColorBuffer(const vector<GLfloat> &g_color_buffer_data);

    void SetTexID(const GLuint& texId) { textureID =texId; }
    void SetNormalTexID(const GLuint& texId) { normalTexID = texId; }


    GLuint loadBMP_custom(const char * imagepath);

    void draw(glm::mat4 View, glm::mat4 Proj);
};

