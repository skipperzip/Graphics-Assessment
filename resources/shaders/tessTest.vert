#version 450

layout(location = 0)in vec4 pos;

out vec3 vPos;

void main()
{
	vPos = pos.xyz;
}