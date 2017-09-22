
#include "graphics\Context.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObject.h"
#include "graphics\Draw.h"
#include "graphics\GenShape.h"
#include "glm\gtx\transform.hpp"
#include "glm\ext.hpp"
#include <ctime>

#include <iostream>

int main()
{
	srand(time(0));

	Context context;
	context.init(800, 800);

	Geometry g2 = makeRectangle(0, 0, .2, .2);

	Geometry g = makeNGon(100, .1, 1,1);

	//Geometry g = makeCheckerboard(100, 2);

	unsigned char pixels[] =
	{ 0,50,250,
		0,0,100,
		0,0,155 };
	unsigned char pixels2[] =
	{ rand(),rand(),rand(),
		rand(),rand(),rand(),
		rand(),rand(),rand() };
	//use pixels2 for fun times
	Texture t_magyel = makeTexture(3, 1, 3, pixels2);
	Framebuffer f = { 0,800,800 };

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 pos;\n"	//location corresponds to an attribute
		"layout(location = 2) in vec2 texCoord;"
		"layout(location = 0) uniform mat4 model;\n"
		"out vec2 vUV;\n"
		"void main ()\n"
		"{\n"
		"gl_Position = model * pos; vUV = texCoord;\n"
		"}\n";

	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"
		/*"layout(location = 0) uniform int k0;\n"
		"layout(location = 1) uniform int k1;\n"
		"layout(location = 2) uniform int k2;\n"*/

		//layout only needed if you set it in the program...also defaults
		/*"layout(location = 3) uniform vec4 c0 = vec4(1,0,0,1);\n"
		"layout(location = 4)uniform vec4 c1 = vec4(0,1,0,1);\n"
		"layout(location = 5)uniform vec4 c2 = vec4(0,0,1,1);\n"*/

		"in vec2 vUV;\n"
		"void main ()\n"
		"{\n"
		"outColor = vec4(1,1,1,1);\n"
		//"outColor = c0*k0 + c1*k1 + c2*k2;\n"
		"}\n";

	Shader s = makeShader(vsource, fsource);

	while (context.step())
	{
		clearFrameBuffer(f);

		int loc = 0, tSlot = 0;
		glm::mat4 rot = glm::rotate((float)context.getTime() / 10, glm::vec3(0.f, 0.f, 1.f));
			//glm::scale(glm::vec3(1, 1, 1));
			//glm::translate(glm::vec3(0,0,0));

		setUniforms(s, loc, tSlot, t_magyel,
								 rot);
		//s0_draw(f, s, g);(int)context.getKey('A'), (int)context.getKey('S'), (int)context.getKey('D')glm::vec4(0,1,1,1), glm::vec4(1,0,1,1), glm::vec4(.5,.5,1,1),


		//setUniforms()
		s0_draw(f, s, g2);
	}

	freeShader(s);
	freeGeometry(g);
	freeTexture(t_magyel);

	context.term();
	return 0;
}