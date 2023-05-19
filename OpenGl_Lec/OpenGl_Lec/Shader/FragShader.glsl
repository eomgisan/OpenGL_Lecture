#version 460


in vec2 texCoord;
in vec3 fragCol;
in vec3 fragPos;
in vec3 fragNormal;
in vec3 fragView;

uniform sampler2D AlbedoTex;

uniform vec3 CameraPos;    


//============
// Fragment Shader
//============
out vec4 color;

void main()
{
	
    vec3 TexCol = vec3(0.5,0.5,0.5);

	vec3 v = normalize(fragView);
	vec3 l = vec3(0,1,0);
	vec3 n = normalize(fragNormal);

	vec3 diff = max( dot( n,l ), 0.0 )  * TexCol;
	vec3 refl = 2.0 * n * dot(n, l) - l;
	vec3 spec = pow(max( dot(refl, v ), 0),3) * vec3(1,1,1);
	vec3 final_light = TexCol + 0.3*  spec + 0.3* diff;

	color = vec4(final_light,1.0);
}
