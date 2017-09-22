#version 450

out vec4 outColor;
in vec2 vUV;
layout(location = 0) uniform sampler2D map;
layout(location = 1) uniform int idx; 
layout(location = 2) uniform int row; 
layout(location = 3) uniform int col; 
void main()
{
	outColor = texture(map, vUV);
}