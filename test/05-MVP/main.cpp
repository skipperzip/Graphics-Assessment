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
	context.init(800,600);

	Texture tex = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	Geometry soulSpear = loadGeometry("../../resources/models/soulspear.obj");
	Shader s = loadShader("../../resources/shaders/mvplite.vert", "../../resources/shaders/mvplite.frag");
	
	Framebuffer f = { 0,800,600 };

	while (context.step())
	{
		clearFrameBuffer(f);
		setFlags(RenderFlag::DEPTH);
		float fTime = (float)context.getTime();

		int speed = 1;
		glm::mat4 modSpear =
			glm::rotate(fTime * speed, glm::vec3(3, 0, 0))*
			glm::scale(glm::vec3(.5, .5, .5))*
			glm::translate(glm::vec3(0, -1, 0));
		glm::mat4 modSpear2 =
			
			glm::scale(glm::vec3(.5, .5, .5))*
			glm::translate(glm::vec3(-3, -1, 0))*
			glm::rotate(fTime * speed, glm::vec3(0, 3, 0));
		glm::mat4 modSpear3 =
			glm::rotate(fTime * speed, glm::vec3(0, 0, 3))*
			glm::scale(glm::vec3(.5, .5, .5))*
			glm::translate(glm::vec3(3, -1, 0));


		//wasd
		int x = 0, y = 0;
		if (context.getKey('W')) y += 1;
		if (context.getKey('S')) y -= 1;

		if (context.getKey('A')) x += 1;
		if (context.getKey('D')) x -= 1;

		glm::vec3 targetPosition = { x,y,0 };


		//camera stuff
		glm::mat4 cam_view = glm::lookAt(glm::vec3(0, -1, -4), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
		glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);
		glm::mat4 go_model(1.0); // identity matrix for now

		int loc = 0, tslot = 0;
		setUniforms(s,loc,tslot, cam_proj, cam_view, modSpear, tex);
		s0_draw(f, s, soulSpear);

		loc = 0, tslot = 0;
		setUniforms(s, loc, tslot, cam_proj, cam_view, modSpear2, tex);
		s0_draw(f, s, soulSpear);

		loc = 0, tslot = 0;
		setUniforms(s, loc, tslot, cam_proj, cam_view, modSpear3, tex);
		s0_draw(f, s, soulSpear);
	}

	freeShader(s);
	freeTexture(tex);
	freeGeometry(soulSpear);


	return 0;
}