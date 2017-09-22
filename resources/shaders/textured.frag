#version 450

layout(location = 3) uniform sampler2D map;
out vec4 outColor;
in vec4 vCol;
in vec2 vUV;
in vec4 vNormal;
void main()
{	
	//outColor = dot(vNormal,-normalize(vec4(1,1,1,0))) * texture(map, vUV);
	outColor = texture(map, vUV);
}