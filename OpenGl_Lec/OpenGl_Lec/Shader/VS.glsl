#version 460

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 col;

out vec2 UV;
out vec3 fragCol;
out vec3 WorldPos;
out vec3 a_normal;

uniform mat4 World;
uniform mat4 View;
uniform mat4 Projection;



out vec3 LightDirection_tangentspace;
out vec3 EyeDirection_tangentspace;


void main(){

  UV = uv;
  fragCol = col;

  WorldPos = vec3(World * vec4(pos,1));
  
  
  a_normal = normalize(transpose(inverse(mat3(World)))*normal);
 
  gl_Position =  Projection * View * World * vec4(pos,1);
  
}