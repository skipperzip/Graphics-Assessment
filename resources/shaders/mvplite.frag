#version 450

in vec2 vUV;
in vec4 vPos;
in vec4 vNormal;

layout (location = 3) uniform sampler2D diffuse;

out vec4 outColor;

void main()
{
	
	vec3 L = normalize(vec3(2,-1,1));
	vec3 N = vNormal.xyz;

	//diffuse lighting
	float lambert = dot(N, -L);

    outColor =  lambert*texture(diffuse, vUV);
}