#version 450

in vec2 vUV;
in vec4 vPos;
in vec3 vNormal;

layout (location = 3) uniform sampler2D diffuse;
layout (location = 4) uniform vec3 lightDirection;
layout (location = 5) uniform vec4 lightColor;

out vec4 outColor;

void main()
{
	vec4 surfaceColor = texture(diffuse, vUV);
	
	//max will clamp the factor so it doesn't go negative
	float lamFactor = max(dot(vNormal, -lightDirection), 0);

	vec4 lamTerm = surfaceColor * lamFactor * lightColor;

	outColor = lamTerm;
}