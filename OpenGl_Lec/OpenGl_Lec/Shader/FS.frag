#version 460

in vec2 UV;
in vec3 fragCol;
in vec3 EyeDir_worldspace;
in vec3 Normal_worldspace;

uniform sampler2D Tex;

//============
// Fragment Shader
//============
out vec4 color;

void main()
{
 	vec3 n = normalize(Normal_worldspace);
	vec3 v = normalize(EyeDir_worldspace);
	vec3 l = v;

	vec3 diff = clamp( dot( n,l ), 0,1 )  * fragCol ;

	vec3 refl = 2.0 * n * dot(n, l) - l;
	vec3 spec = pow(clamp( dot(refl, v ), 0, 1),3) * fragCol;

	color = texture( Tex, UV );	
	

}