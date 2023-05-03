#version 460

in vec2 UV;
in vec3 fragCol;
in vec3 WorldPos;
in vec3 a_normal;


uniform sampler2D AlbedoTex;
uniform sampler2D NormalTex;
uniform sampler2D Tex3;


uniform vec3 CameraPos;    
uniform vec3 LightDir;

//============
// Fragment Shader
//============
out vec3 color;

void main()
{

	// compute derivations of the world position
    vec3 p_dx = dFdx(WorldPos);
    vec3 p_dy = dFdy(WorldPos);
    
    // compute derivations of the texture coordinate
    vec2 tc_dx = dFdx(UV);
    vec2 tc_dy = dFdy(UV);
    
    // compute initial tangent and bi-tangent
    // t = dFdW X tc
    // b = dFdW X tc
    
    vec3 t = normalize( tc_dy.y * p_dx - tc_dx.y * p_dy );
    vec3 b = normalize( tc_dy.x * p_dx - tc_dx.x * p_dy ); // sign inversion
    vec3 n = normalize(a_normal);
    // get new tangent from a given mesh normal
    
    
    vec3 x = cross(n, t);
    t = cross(x, n);
    t = normalize(t);
    
    // get updated bi-tangent
    x = cross(b, n);
    b = cross(n, x);
    b = normalize(b);
    
    mat3 tbn = transpose(mat3(t, b, n));
    
    //vec3 Tangent = normalize(pos);
    //vec3 Bitangent = normalize(cross(normal, Tangent));
	

	vec3 TextureNormal_tangentspace = normalize(texture( NormalTex, UV ).rgb*2.0 - 1.0);
	
    vec3 TexCol = texture2D(AlbedoTex,UV).rgb;

	vec3 v_ts = normalize(tbn*(CameraPos - WorldPos));
	vec3 l_ts = normalize(tbn*LightDir);


	vec3 diff = max( dot( TextureNormal_tangentspace,l_ts ), 0.0 )  * vec3(1,1,1);
	vec3 refl = reflect(-l_ts,  TextureNormal_tangentspace);
	vec3 spec = pow(max( dot(refl, v_ts ), 0),3) * TexCol;
	vec3 final_light = TexCol + 0.3*  spec + 0.3* diff;

	

	
	color = final_light;
}