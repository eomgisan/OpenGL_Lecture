#version 460

in vec2 UV;
in vec3 fragCol;
in vec3 WorldPos;
in mat3 tbn;


uniform sampler2D AlbedoTex;
uniform sampler2D NormalTex;
uniform sampler2D Tex3;




//============
// Fragment Shader
//============
out vec3 color;

void main()
{
	vec3 TextureNormal_tangentspace = normalize(texture( NormalTex, UV ).rgb*2.0 - 1.0);
 	vec3 n = normalize(Normal_worldspace);
	
	vec3 v = normalize(CameraPos - WorldPos);
	vec3 l = -1*normalize(LightDir);
	vec3 diff = max( dot( n,l ), 0.0 )  * vec3(1,1,1);
	vec3 refl = reflect(-l, n);
	vec3 spec = pow(max( dot(refl, v ), 0),3) * vec3(1,1,1);
	vec3 final_light = spec + diff;

	vec3 realN = normalize(Normal_worldspace);

	
	color = texture(TextureNormal_tangentspace , UV).rgb;
}