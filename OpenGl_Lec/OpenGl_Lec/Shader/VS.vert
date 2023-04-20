#version 460


layout(location = 0) in vec3 pos;
layout(location = 3) in vec3 col;

out vec3 fragCol;

uniform mat4 World;
uniform mat4 View;
uniform mat4 Projection;

void main(){

  fragCol = col;
  gl_Position =  Projection * View * World * vec4(pos,1);
}