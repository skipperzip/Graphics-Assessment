   
#include "graphics\Context.h"
#include "graphics\RenderObject.h"
#include "graphics\Vertex.h"
#include "graphics\Draw.h"
#include "graphics\Load.h"
#include "glm\ext.hpp"
#include <ctime>

int main()
{
	Context context;
	context.init(1000,1000);

	Texture tex = loadTexture("../../resources/textures/Charactervector.png");

	Texture think = loadTexture("../../resources/textures/think.png");
	Texture angry = loadTexture("../../resources/textures/angry.png");
	Texture lava = loadTexture("../../resources/textures/lava.png");

	Vertex vquad[] = {
		{{-1,-1,0,1}, {}, {0,0}},
		{{1,-1,0,1},{},{1,0}},
		{{1,1,0,1},{},{1,1}},
		{{-1,1,0,1},{},{0,1}}
	};

	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	Geometry cube = loadGeometry("../../resources/models/cube.obj");
	Geometry sphere = loadGeometry("../../resources/models/sphere.obj");

	Geometry soulSpear = loadGeometry("../../resources/models/soulspear.obj");

	//Shader s = makeShader(vsource, fsource);
	Shader s = loadShader("../../resources/shaders/mono.vert", "../../resources/shaders/mono.frag");
	Shader scube = loadShader("../../resources/shaders/textured.vert", "../../resources/shaders/textured.frag");
	Shader scube2 = loadShader("../../resources/shaders/textured.vert", "../../resources/shaders/textured.frag");
	Shader scube3 = loadShader("../../resources/shaders/textured.vert", "../../resources/shaders/textured.frag");
	Framebuffer f = { 0,1000,1000 };

	while (context.step())
	{
		clearFrameBuffer(f);
		setFlags(RenderFlag::DEPTH);
		float fTime = (float)context.getTime();

		int speed = 1;
		glm::mat4 modCube = glm::rotate(fTime * speed, glm::vec3(1, 1.3,.2));
		glm::mat4 modSpear = 
			glm::rotate(fTime * speed, glm::vec3(1, 1.3, .2))*
			glm::scale(glm::vec3(.2, .2, .2))*
			glm::translate(glm::vec3(1,-5,1));

		//SPEHRE STUFF
		glm::mat4 modSphere1 = glm::rotate(fTime * speed, glm::vec3(0, 1, 0)) *
			glm::scale(glm::vec3(.8,.8,.8));
		glm::mat4 modSphere2 = 
			glm::rotate(fTime * speed * 2, glm::vec3(0, 0, 1)) *
			glm::translate(glm::vec3(.8,0,0)) *
			glm::rotate(fTime * speed, glm::vec3(1, 0, 0)) *
			glm::scale(glm::vec3(.3,.3,.3));
		glm::mat4 modSphere3 =
			glm::rotate(fTime * speed, glm::vec3(0, 0, 1)) *
			glm::translate(glm::vec3(-3, 0, 0)) *
			glm::scale(glm::vec3(.15,.15,.15));

		int loc = 0, tslot = 0;
	//	setUniforms(s, loc, tslot, tex, 0, 4, 4, 1, (int)context.getTime());

		//s0_draw(f, s, quad);

		loc = 0, tslot = 0;
		setUniforms(scube, loc, tslot, modSphere1, fTime, think);
		s0_draw(f, scube, sphere);
	
		loc = 0, tslot = 0;
		setUniforms(scube, loc, tslot, modSphere2, fTime, angry);	
		//s0_draw(f, scube, sphere);
		
		loc = 0, tslot = 0;
		setUniforms(scube, loc, tslot, modSphere3, fTime, lava);
		//s0_draw(f, scube, sphere);
	}

	freeShader(s);
	freeShader(scube);
	freeShader(scube2);
	freeShader(scube3);

	freeTexture(tex);
	freeTexture(think);
	freeTexture(angry);
	freeTexture(lava);

	freeGeometry(quad);
	freeGeometry(soulSpear);
	freeGeometry(cube);
	freeGeometry(sphere);

	return 0;
}