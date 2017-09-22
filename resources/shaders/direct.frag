#version 450


layout(location = 3) uniform mat4 lProj;
layout(location = 4) uniform mat4 lView;
layout(location = 5) uniform sampler2D shadowmap;
layout(location = 6) uniform vec4 col;

in vec2 vUV;
in vec4 vPos;

uniform float shadowBias = 0.01;

// Simple matrix that converts from clip space (-1,1) to UV space (0,1)
uniform mat4 clipToUV = mat4(0.5f, 0.0f, 0.0f, 0.0f,
							 0.0f, 0.5f, 0.0f, 0.0f,
							 0.0f, 0.0f, 0.5f, 0.0f,
							 0.5f, 0.5f, 0.5f, 1.0f);

out vec4 outColor;

void main()
{
	vec4 sUV = clipToUV * lProj * lView * vPos;
	
	float visibility = 1;
	if(texture(shadowmap,sUV.xy).r  < sUV.z - shadowBias)
		visibility = 0;	


	outColor = col * visibility;
}