#version 450

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 col;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec4 nor;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform float time;

out vec2 vUV;
out vec4 vCol;
out vec4 vNormal;

void main()
{
	vec4 stuff = {time,time,time, 1};
	vec4 stuff2 = {texCoord.x,texCoord.y,1, 1};
	vec4 blah = {texCoord.x,texCoord.y,.5,1};
	vNormal = model * nor;
	gl_Position = model * pos;
	vUV = texCoord;
	vCol = pos + blah;
}