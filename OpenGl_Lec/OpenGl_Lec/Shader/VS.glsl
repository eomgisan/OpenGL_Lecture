#version 460

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 col;

out vec2 texCoord;
out vec3 fragCol;
out vec3 fragPos;
out vec3 fragNormal;
out vec3 fragView;

uniform mat4 World;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 CameraPos;


void main(){

  texCoord = uv;
  fragCol = col;

  fragPos = vec3(World * vec4(pos,1));
  fragNormal = normalize(transpose(inverse(mat3(World)))*normalize(normal));
  fragView = vec3(CameraPos - fragPos);
  
  gl_Position =  Projection * View * World * vec4(pos,1);
  
}