#version 450

in vec3 vPos[];
out vec3 tcPos[];

void main()
{
	tcPos = vPos;
}