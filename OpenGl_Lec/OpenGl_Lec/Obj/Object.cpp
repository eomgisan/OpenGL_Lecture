#include "pch.h"
#include "Object.h"
#include "Func/LoadFunc.h"

Object::Object(const char* vsPath, const char* fsPath, const char* objPath)
{
	textureID = 0;
	normalTexID = 0;

	CreateShaderProgramFromFiles("Shader/VS.vert", "Shader/FS.frag", shader);
	
	WorldMatrixID = glGetUniformLocation(shader, "World");
	ViewMatrixID = glGetUniformLocation(shader, "View");
	ProjectionMatrixID = glGetUniformLocation(shader, "Projection");

	LightDirID = glGetUniformLocation(shader, "LightDir");
	CameraPosID = glGetUniformLocation(shader, "CameraPos");
	
	loadOBJ(objPath);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);
	
	glGenBuffers(1, &TBO);
	glBindBuffer(GL_ARRAY_BUFFER, TBO);
	glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), texCoords.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(1);
	
	glGenBuffers(1, &NBO);
	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(2);



	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(unsigned short), idx.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

Object::~Object(){}


void Object::SetColorBuffer(const vector<GLfloat> &g_color_buffer_data)
{
	glBindVertexArray(VAO);

	glGenBuffers(1, &CBO);
	glBindBuffer(GL_ARRAY_BUFFER, CBO);
	glBufferData(GL_ARRAY_BUFFER, g_color_buffer_data.size() * sizeof(GLfloat), g_color_buffer_data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);

}



bool Object::loadOBJ(const char* path) {
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}

	

	vector<glm::vec2> tempTexCoord;
	vector<glm::vec3> tempNormal;


	while (1) {
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertices.push_back(vertex);
		}

		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			tempTexCoord.push_back(uv);
		}

		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			tempNormal.push_back(normal);
		}

		else if (strcmp(lineHeader, "f") == 0) {
			
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}

			idx.push_back(vertexIndex[0] - 1);
			idx.push_back(vertexIndex[1] - 1);
			idx.push_back(vertexIndex[2] - 1);

			texCoords.push_back(tempTexCoord[uvIndex[0] - 1]);
			texCoords.push_back(tempTexCoord[uvIndex[1] - 1]);
			texCoords.push_back(tempTexCoord[uvIndex[2] - 1]);

			normals.push_back(tempNormal[normalIndex[0] - 1]);
			normals.push_back(tempNormal[normalIndex[1] - 1]);
			normals.push_back(tempNormal[normalIndex[2] - 1]);

		}
	}
	return true;
}






void Object::draw(glm::mat4 View, glm::mat4 Proj) {
	
	

	glUseProgram(shader);

	glUniformMatrix4fv(WorldMatrixID, 1, GL_FALSE, glm::value_ptr(World));
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, glm::value_ptr(View));
	glUniformMatrix4fv(ProjectionMatrixID, 1, GL_FALSE, glm::value_ptr(Proj));
	glUniform3fv(LightDirID, 1, glm::value_ptr(lightDir));
	glUniform3fv(CameraPosID, 1, glm::value_ptr(camPos));

	if(textureID != 0) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
		GLint location = glGetUniformLocation(shader, "AlbedoTex");
		glUniform1i(location, 0);
		
	}

	if (normalTexID != 0) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normalTexID);
		GLint location = glGetUniformLocation(shader, "NormalTex");
		glUniform1i(location, 1);


	}
	
	

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, idx.size(), GL_UNSIGNED_SHORT, nullptr);
	
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgram(0);
}