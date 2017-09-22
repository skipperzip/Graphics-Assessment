
#include "graphics\Context.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObject.h"
#include "graphics\Draw.h"
#include "graphics\GenShape.h"
#include <ctime>

#include <iostream>

int main()
{
	srand(time(0));

	Context context;
	context.init(800, 800);

	/*Vertex verts[3] = { {{-.5f,-.5f,0,1}, {1,0,0,1}},
						{{.5f,-.5f,0,1}, { 1,0,0,1 } },
						{{0,.5f,0,1}, { 1,0,0,1 } }};
	unsigned idxs[3] = { 0,1,2 };

	Geometry g = makeGeometry(verts, 3, idxs, 3);*/

	//Geometry g = makeRectangle(0, 0, .2, .2);

	Geometry g = makeNGon(100, .9);

	//Geometry g = makeCheckerboard(100, 2);

	unsigned char pixels[] =
		{	0,50,250,
			0,0,100,
			0,0,155};
	unsigned char pixels2[] =
	{ rand(),rand(),rand(),
		rand(),rand(),rand(),
		rand(),rand(),rand() };
	unsigned char pixels3[] =
	{ 50,50,50,
		100,100,100,
		255,255,255 };
	unsigned char pixels4[] =
	{255,0,255,0,
	0,255,0,255,
	255,0,255,0, 
	0,255,0,255, };

	//use pixels2 for fun times
	Texture t_magyel = makeTexture(3, 1, 3, pixels);
	//Texture t_magyel = makeTexture(4, 4, 1, pixels4);

	Texture t_mask = makeTexture(4, 1, 4, pixels2);


	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 pos;\n"	//location corresponds to an attribute
		"layout(location = 1) in vec4 color;\n"
		"layout(location = 2) in vec2 texCoord;\n"
		"layout(location = 0) uniform float time;\n"
		"layout(location = 2) uniform float mouseX;\n"
		"layout(location = 3) uniform float mouseY;\n"
		"out vec4 vColor;\n"
		"out vec2 vUV;\n"
		"void main ()\n"
		"{\n"
			"gl_Position = pos;\n"
			/*"gl_Position.x += mouseX * 2;\n"
			"gl_Position.y -= mouseY * 2;\n"*/
		//"gl_Position.z += sin(time);\n"
		"vColor = color;\n"
		"vUV = texCoord;\n"
		"}\n";

	const char* fsource =
		"#version 450\n"
		"layout(location = 0) uniform float time;\n"
		"layout(location = 1) uniform int tog;\n"
		"layout(location = 4) uniform sampler2D map;\n"
		"layout(location = 5) uniform sampler2D mask;\n"
		"out vec4 outColor;\n"
		"in vec4 vColor;\n"
		"in vec2 vUV;\n"
		"void main ()\n"
		"{\n"
		"vec2 thing = vUV;\n"
		//////////////////
		//THE MAGIC LINE//
		"thing += 2 * sin(time + (cos(thing.x) * sin(thing.y))) + gl_FragCoord.xy;\n"
		//////////////////
		//"thing += (time/5) * sin(.6*gl_FragCoord.x/50)*5;\n"
		//"thing.x= vUV.x * sin(time+gl_FragCoord.x/100)-5;\n"
		//"thing.y += time * tan(gl_FragCoord.y*10)*5;\n"
		"outColor = texture(map, thing);\n"
		//"outColor = texture(map, thing) * texture(mask, thing).g;\n"
		//"outColor = vColor;\n"
		//"outColor = cos(time+gl_FragCoord/5);\n"
		/*"if(tog == 1)\n"
		"outColor = vColor*2;\n"
		"else outColor = vColor;\n"*/
		"}\n";

	Shader s = makeShader(vsource, fsource);
	Framebuffer f = { 0,800,800 };

	double x, y;
	float ox, oy;
	while (context.step())
	{
		clearFrameBuffer(f);

		setUniform(s, 0, (float)context.getTime());
		setUniform(s, 1, context.getMouseButton(0));
		
		context.getMousePosition(x, y);

		ox = ((x / 800)-.5);
		oy = ((y / 800)-.5);
		setUniform(s, 2, ox);
		setUniform(s, 3, oy);
		setUniform(s, 4, t_magyel, 0);
		setUniform(s, 5, t_mask, 1);

		s0_draw(f, s, g);


		std::cout << ox << ", " << oy << std::endl;
	}

	freeShader(s);
	freeGeometry(g);
	freeTexture(t_magyel);

	context.term();
	return 0;
}