#include "graphics\Context.h"
#include "graphics\RenderObject.h"
#include "graphics\Vertex.h"
#include "graphics\Draw.h"
#include "graphics\Load.h"
#include "graphics\GameObjects.h"
#include "glm\ext.hpp"
#include <ctime>

int main()
{
	//placeholders
	const size_t w = 1280, h = 720;

	Context context;
	context.init(w, h);

	//Make floor
	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 } ,{ 0,0,1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 } ,{ 0,0,1,0 } },
		{ { -1,1,0,1 },{},{ 0,1 } ,{ 0,0,1,0 } } };

	unsigned quadidx[] = { 0,1,3,1,2,3 };

	solveTangents(vquad, 4, quadidx, 6);
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	/////////////////////////
	//Make 8 objects
	SpecGloss objects[8];

	//floor
	objects[0].geo		= quad;
	objects[0].diffuse	= loadTexture("../../resources/textures/four_diffuse.tga");
	objects[0].specular = loadTexture("../../resources/textures/four_specular.tga");
	objects[0].normal	= loadTexture("../../resources/textures/four_normal.tga");
	objects[0].gloss = 4;
	objects[0].model = glm::scale(glm::vec3(5, 5, 5)) * glm::rotate(glm::radians(90.f), glm::vec3(-1, 0, 0));

	//soulspear
	objects[1].geo = loadGeometry("../../resources/models/soulspear.obj");
	objects[1].diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	objects[1].specular = loadTexture("../../resources/textures/soulspear_specular.tga");
	objects[1].normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	objects[1].gloss = 4;
	//objects[1].model = glm::rotate(glm::radians(90.f),glm::vec3(-1,0,0));

	//earth
	objects[2].geo = loadGeometry("../../resources/models/sphere.obj");
	objects[2].diffuse = loadTexture("../../resources/textures/earth_diffuse.jpg");
	objects[2].specular = loadTexture("../../resources/textures/earth_specular.jpg");
	objects[2].normal = loadTexture("../../resources/textures/earth_normal.jpg");
	objects[2].gloss = 4;
	objects[2].model = glm::scale(glm::vec3(2, 2, 2)) * glm::translate(glm::vec3(2, 1, -1));


	//Framebuffer
	Framebuffer screen{ 0,1280,720 };
	Framebuffer gbuffer = makeFramebuffer(w, h, 4, true, 2, 2);
	Framebuffer lbuffer = makeFramebuffer(w, h, 4, false, 2, 0);
	Framebuffer sbuffer = makeFramebuffer(w, h, 4, true, 2, 0);

	//Camera
	Camera cam;
	cam.view = glm::lookAt(glm::vec3(0,2,5),glm::vec3(0,1,0),glm::vec3(0,1,0));
	cam.proj = glm::perspective(45.f, 1280.f/720.f, 1.f, 10.f);

	//Lights
	DirectionalLight dlights[2];

	dlights[0].range = 10;
	dlights[0].intensity = 1;
	dlights[0].color = glm::vec4(1, 1, 0, 1);
	dlights[0].direction = glm::normalize(glm::vec3(1, 0, 0));	//left

	dlights[1].range = 10;
	dlights[1].intensity = 1;
	dlights[1].color = glm::vec4(0, 0, 1, 1);
	dlights[1].direction = glm::normalize(glm::vec3(-1, 0, 0));	//right

	//Shaders
	Shader gpass = loadShader("../../resources/shaders/gpass.vert", "../../resources/shaders/gpass.frag");
	Shader cpass = loadShader("../../resources/shaders/cpass.vert", "../../resources/shaders/cpass.frag");
	Shader lpassD = loadShader("../../resources/shaders/lpassD.vert", "../../resources/shaders/lpassD.frag");
	Shader spassD = loadShader("../../resources/shaders/shadow.vert", "../../resources/shaders/shadow.frag");

	int loc = 0, slot = 0;
	while(context.step())
	{
		/////////////////////////////
		//GPass - Geometry Pass
		clearFrameBuffer(gbuffer);
		setFlags(RenderFlag::DEPTH);
		for (int i = 0; i < 3; i++)
		{
			loc = slot = 0;
			setUniforms(gpass, loc, slot, cam, objects[i]); // 3mat, 3tex, 1flo
			s0_draw(gbuffer, gpass, objects[i].geo);
		}

		/////////////////////////////
		//LPass - Light Pass
		clearFrameBuffer(lbuffer);
		for (int i = 0; i < 1; i++)
		{
			/////////////////////////////
			//SPass - Pre-Pass Shadow
			clearFrameBuffer(sbuffer);
			setFlags(RenderFlag::DEPTH);
			for (int j = 0; j < 3; j++)
			{
				loc = slot = 0;
				setUniforms(spassD, loc, slot, dlights[i].getProj(), dlights[i].getView(), objects[j].model);
				s0_draw(sbuffer, spassD, objects[j].geo);
			}

			//LPass
			setFlags(RenderFlag::ADDITIVE);
			loc = slot = 0;
			setUniforms(lpassD, loc, slot, cam, dlights[i], gbuffer.targets[3], gbuffer.targets[2], sbuffer.depthTarget);
			s0_draw(lbuffer, lpassD, quad);
		}

		/////////////////////////////
		//CPass - Composite Pass ("main" pass)
		/*clearFrameBuffer(screen);
		setFlags(RenderFlag::DEPTH);*/
		loc = slot = 0;
		clearFrameBuffer(screen);
		setFlags(RenderFlag::NONE);
		setUniforms(cpass, loc, slot, gbuffer.targets[0], gbuffer.targets[0]);
		s0_draw(screen, cpass, quad);	//only draw the quad??????
	}

	context.term();

	return 0;
}