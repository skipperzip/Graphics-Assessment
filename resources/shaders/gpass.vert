#version 450

layout(location = 0) in vec4 pos;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec4 normal;
layout(location = 4) in vec4 tangent;
layout(location = 5) in vec4 bitangent;

//Camera
layout(location = 0) uniform mat4 proj;
layout(location = 1) uniform mat4 view;

//Model
layout(location = 2) uniform mat4 model;

//output
out vec2 vUV;
out vec3 vPos;
out mat4 vTBN;	//what does tbn stand for?

void main()
{
	gl_Position = proj * view * model * pos;

	vTBN = view * model * mat4(tangent, bitangent, normal, vec4(0,0,0,0));
	vUV = texCoord;
	vPos = (view * model * pos).xyz;
}