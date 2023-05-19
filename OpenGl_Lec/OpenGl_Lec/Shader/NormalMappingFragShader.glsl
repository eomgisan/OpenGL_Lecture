#version 460


in vec2 texCoord;
in vec3 fragCol;
in vec3 fragPos;
in vec3 fragNormal;
in vec3 fragView;


uniform sampler2D AlbedoTex;
uniform sampler2D NormalTex;
uniform sampler2D Tex3;


uniform vec3 CameraPos;    


//============
// Fragment Shader
//============
out vec4 color;

void main()
{

	// compute derivations of the world position
    vec3 p_dx = dFdx(fragPos);
    vec3 p_dy = dFdy(fragPos);
    
    // compute derivations of the texture coordinate
    vec2 tc_dx = dFdx(texCoord);
    vec2 tc_dy = dFdy(texCoord);
    
    // compute initial tangent and bi-tangent
    // t = dFdW X tc
    // b = dFdW X tc
    
    vec3 t = normalize( tc_dy.y * p_dx - tc_dx.y * p_dy );
    vec3 b = normalize( tc_dy.x * p_dx - tc_dx.x * p_dy ); // sign inversion
    vec3 n = normalize(fragNormal);
    // get new tangent from a given mesh normal
    
    
    vec3 x = cross(n, t);
    t = cross(x, n);
    t = normalize(t);
    
    // get updated bi-tangent
    x = cross(b, n);
    b = cross(n, x);
    b = normalize(b);
    
    mat3 tbn = transpose(mat3(t, b, n));

	vec3 TextureNormal_tangentspace = normalize((texture( NormalTex, texCoord ).rgb - 0.5)*2.0);
	
    vec3 TexCol = texture(AlbedoTex,texCoord).rgb;

	vec3 v_ts = normalize(tbn*normalize(fragView));
	vec3 l_ts = normalize(tbn*normalize(vec3(0,1,0)));


	vec3 diff = max( dot( TextureNormal_tangentspace,l_ts ), 0.0 )  * TexCol;
	vec3 refl = 2.0 * n * dot(n, l_ts) - l_ts;
	vec3 spec = pow(max( dot(refl, v_ts ), 0),3) * vec3(1,1,1);
	vec3 final_light = TexCol + 0.3*  spec + 0.3* diff;





	color = vec4(final_light,1.0);
    
  
}
