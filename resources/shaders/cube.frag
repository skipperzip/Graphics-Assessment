#version 450

out vec4 outColor;
in vec4 vCol;
in vec2 vUV;
in vec4 vNormal;
void main()
{
	//outColor = dot(-normalize(vec4(1,1,1,0)), vNormal) * outColor;
	//outColor.a = 1;
outColor = vCol;
}