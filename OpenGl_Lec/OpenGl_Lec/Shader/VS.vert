#version 460


layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 col;

out vec2 UV;
out vec3 fragCol;
out vec3 Normal_worldspace;
out vec3 EyeDir_worldspace;

uniform mat4 World;
uniform mat4 View;
uniform mat4 Projection;



void main(){


  
  mat4 ConversionMatrix = inverse(View);
  vec3 CameraPos = vec3(ConversionMatrix[3]);

  EyeDir_worldspace = CameraPos - (World * vec4(pos,1)).xyz;
  Normal_worldspace = transpose(inverse(mat3(World)))* normal;



  gl_Position =  Projection * View * World * vec4(pos,1);

  
  UV = uv;
  fragCol = col;
  
}