#version 450

layout(location = 0)in vec4 pos;
layout(location = 2)in vec2 texCoord;

out vec2 vUV;

void main()
{
	vUV = texCoord;
	gl_Position = pos;
}