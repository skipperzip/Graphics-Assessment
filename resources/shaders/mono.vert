#version 450

layout(location = 0) in vec4 pos;
layout(location = 2) in vec2 texCoord;

layout(location = 1) uniform int idx = 5;
layout(location = 2) uniform int row = 4;
layout(location = 3) uniform int col = 4;
layout(location = 4) uniform int speed = 3;
layout(location = 5) uniform int time;

out vec2 vUV;

void main()
{
	int	t = (time * 3) % 4;

	int c = t / col;
	int r = t % col;

	gl_Position = pos;
	vUV = (vec2(r,c) + texCoord) / vec2(row,col);
}