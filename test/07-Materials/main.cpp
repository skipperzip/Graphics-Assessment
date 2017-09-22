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

	Context context;

	context.init(800, 600);
	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 } ,{ 0,0,1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 } ,{ 0,0,1,0 } },
		{ { -1,1,0,1 },{},{ 0,1 } ,{ 0,0,1,0 } } };

	unsigned quadidx[] = { 0,1,3,1,2,3 };

	solveTangents(vquad, 4, quadidx, 6);
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);
	Texture floor_normal = loadTexture("../../resources/textures/face.jpg");

	Texture normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	Texture diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	Texture spec = loadTexture("../../resources/textures/soulspear_specular.tga");
	float	gloss = 4.0f;
	
	Shader s = loadShader("../../resources/shaders/standard.vert",
		"../../resources/shaders/standard.frag");

	Framebuffer screen = { 0,800,600 };


	///////////////////////////////
	//Model Data
	//an array to store ALL THE THINGS
	SpecGloss sceneObjects[2];

	sceneObjects[0].geo = loadGeometry("../../resources/models/soulspear.obj");

	sceneObjects[0].model = glm::mat4();


	glm::vec3 targetPosition = { 0,0,0 };


	// Camera
	glm::mat4 cam_view = glm::lookAt(glm::vec3(targetPosition),glm::vec3(0, 1, 0),glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);

	// Model
	glm::mat4 go_model;

	// Light
	glm::vec3 light_direction = glm::normalize(glm::vec3(1, -1, 1));



	// Keys



	while (context.step())
	{
		clearFrameBuffer(screen);
		setFlags(RenderFlag::DEPTH);


		int x = 0, y = 0;
		if (context.getKey('W')) y += 1;
		if (context.getKey('S')) y -= 1;

		if (context.getKey('A')) x += 1;
		if (context.getKey('D')) x -= 1;

		glm::vec3 targetPosition = { x,y,0 };
		cam_view = glm::lookAt(glm::vec3(targetPosition), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

		int loc = 0, slot = 0;	
		setUniforms(s, loc, slot,
			cam_proj, cam_view,			// Camera information
			go_model, floor_normal,		// Surface information
			light_direction);			// Light Information

		s0_draw(screen, s, quad);
	}

	context.term();
}