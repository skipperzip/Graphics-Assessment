#version 450

in vec3 tcPos[];
out vec3 tePos;

void main()
{
	tePos = tcPos;
}