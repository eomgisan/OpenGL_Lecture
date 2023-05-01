#version 460

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 col;

out vec2 UV;
out vec3 fragCol;
out vec3 WorldPos;
out mat3 tbn;

uniform mat4 World;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 CameraPos;    
uniform vec3 LightDir;

out vec3 LightDirection_tangentspace;
out vec3 EyeDirection_tangentspace;


void main(){

  UV = uv;
  fragCol = col;

  WorldPos = vec3(World * vec4(pos,1));
  vec3 a_normal = transpose(inverse(mat3(World)))* normal;



  // compute derivations of the world position
  vec3 p_dx = dFdx(WorldPos);
  vec3 p_dy = dFdy(WorldPos);

  // compute derivations of the texture coordinate
  vec2 tc_dx = dFdx(uv);
  vec2 tc_dy = dFdy(uv);

  // compute initial tangent and bi-tangent
  // t = dFdW X tc
  // b = dFdW X tc


  vec3 t = normalize( tc_dy.y * p_dx - tc_dx.y * p_dy );
  vec3 b = normalize( tc_dy.x * p_dx - tc_dx.x * p_dy); // sign inversion

  // get new tangent from a given mesh normal

  vec3 n = normalize(a_normal);
  vec3 x = cross(n, t);
  t = cross(x, n);
  t = normalize(t);

  // get updated bi-tangent
  x = cross(b, n);
  b = cross(n, x);
  b = normalize(b);

  tbn = mat3(t, b, n);
  
  LightDirection_tangentspace = tbn * LightDir;
  EyeDirection_tangentspace =  LightDirection_tangentspace;

  vec3 Tangent = normalize(pos);
  vec3 Bitangent = normalize(cross(normal, Tangent));


  gl_Position =  Projection * View * World * vec4(pos,1);
  
}