#version 450

in vec2 vUV;
in vec3 vPos;
in mat4 vTBN; 

//camera
layout(location = 1)uniform mat4 view;

//surface material data
layout(location = 3) uniform sampler2D diffuseMap;
layout(location = 4) uniform sampler2D specularMap;
layout(location = 5) uniform sampler2D normalMap;
layout(location = 6) uniform float     gloss;

//light data
layout(location =  7) uniform vec3  l_data;
layout(location =  8) uniform vec4  l_color;
layout(location =  9) uniform float l_intensity;
layout(location = 10) uniform vec4  l_ambient;
layout(location = 11) uniform int   light_type; 

//outputs
layout(location = 0) out vec4 outFinal;
layout(location = 1) out vec4 outDiffuse;
layout(location = 2) out vec4 outSpecular;
layout(location = 3) out vec4 outNormal;

float lamb(vec3 N, vec3 L)
{
	return max(0, dot(N,-L));
}

float phong(vec3 N, vec3 L, vec3 V, float power)
{
	if(dot(N,-L) <=0) return 0;
	vec3 R = reflect (-L,N);
	return pow(max(0, dot(V,-R)), power);
}

void main()
{			
	//this makes it between 1 and -1 (convert to 1/-1 coords)
	// Read surface data
	vec3 normal  = (vTBN*(2*texture(normalMap, vUV)-1)).xyz;	
	vec4 diffuse  = texture(diffuseMap, vUV);
	vec4 specular = texture(specularMap, vUV);

	// calculate light direction
	vec3 lDir = l_data;
	float attenuation = 1;
	if(light_type == 1)
	{
		lDir = normalize(l_data - vPos.xyz);
		attenuation = 1.0/distance(vPos.xyz, l_data);
	}

	// calculate our lighting factors
	float lamb = lamb(normal, lDir);
	float ambi = 1;
	float spec = phong(normal, lDir, normalize(view[0].xyz - vPos), gloss);

	// calculate color terms
	vec4 outAmbient = diffuse   * ambi * vec4(0,0,1,1) * l_ambient;
	outDiffuse = diffuse   * lamb * vec4(0,1,0,1) * l_color * l_intensity;
	outSpecular = specular * spec * vec4(1,0,0,1) * l_color * l_intensity;
	
	outNormal = vec4(normal,0);

	outFinal = outAmbient + outDiffuse + outSpecular;
}