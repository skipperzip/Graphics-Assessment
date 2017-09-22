#include "graphics\Context.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObject.h"
#include "graphics\Draw.h"
#include "graphics\GenShape.h"

int main()
{
	Context context;
	context.init(800,800);

	//Vertex verts[3] = { {{-.5f,-.5f,0,1}, {1,0,0,1}},
	//					{{.5f,-.5f,0,1}, { 1,0,0,1 } },
	//					{{0,.5f,0,1}, { 1,0,0,1 } }};
	//unsigned idxs[3] = { 0,1,2 };

	//Geometry g = makeGeometry(verts, 3, idxs, 3);

	//Geometry g = makeRectangle(0, 0, .5, .5);
	//Geometry g = makeNGon(100, 1);
	Geometry g = makeCheckerboard(5, .9);

	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 pos;\n"	//location corresponds to an attribute
		"layout(location = 1) in vec4 color;\n"
		"out vec4 vColor;\n"
		"void main ()\n"
		"{\n"
			"gl_Position = pos;\n"
			"vColor = color;\n"
		"}\n";

	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"
		"in vec4 vColor;\n"
		"void main ()\n"
		"{\n"
			"outColor = 1-vColor;\n"
		"}\n";

	Shader s = makeShader(vsource, fsource);
	Framebuffer f = { 0,800,800 };

	while (context.step())
	{
		s0_draw(f, s, g);
	}
	
	freeGeometry(g);
	freeShader(s);

	context.term();
	return 0;
}