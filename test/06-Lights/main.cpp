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
	context.init(800, 600);

	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 },{ 0,0,1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },
		{ { -1,1,0,1 },{},{ 0,1 },{ 0,0,1,0 } }
	};
	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	Texture tex = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	Texture lava = loadTexture("../../resources/textures/lava.png");
	Geometry soulSpear = loadGeometry("../../resources/models/soulspear.obj");
	Shader s = loadShader("../../resources/shaders/lambert.vert", "../../resources/shaders/lambert.frag");

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

		glm::mat4 modquad = 
			glm::rotate(glm::radians(90.f), glm::vec3(-1, 0, 0)) * 
			glm::scale(glm::vec3(5, 5, 1))*
			glm::translate(glm::vec3(0,0,-1));
		//camera stuff
		glm::mat4 cam_view = glm::lookAt(glm::vec3(0, -.1, -4), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
		glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);
		glm::mat4 go_model(1.0); // identity matrix for now

		//light uniforms
		glm::vec3 lightPos = glm::normalize(glm::vec3(1, -1, 1));
		glm::vec4 lightColor = glm::vec4(3.f, 1.6f, 2.5f, 1.f);

		int loc = 0, tslot = 0;
		setUniforms(s, loc, tslot, cam_proj, cam_view, modSpear, tex, lightPos, lightColor);
		s0_draw(f, s, soulSpear);

		loc = 0, tslot = 0;
		setUniforms(s, loc, tslot, cam_proj, cam_view, modSpear2, tex, lightPos, lightColor);
		s0_draw(f, s, soulSpear);

		loc = 0, tslot = 0;
		setUniforms(s, loc, tslot, cam_proj, cam_view, modSpear3, tex, lightPos, lightColor);
		s0_draw(f, s, soulSpear);

		loc = 0, tslot = 0;
		setUniforms(s, loc, tslot, cam_proj, cam_view, modquad, lava, lightPos, lightColor);
		s0_draw(f, s, quad);
	}

	freeShader(s);
	freeTexture(tex);
	freeTexture(lava);
	freeGeometry(soulSpear);
	freeGeometry(quad);

	return 0;
}