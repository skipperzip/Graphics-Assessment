#pragma once

#include "glm\glm.hpp"

struct Vertex;

struct Geometry
{
	/*vertex array object,
	*vertex buffer object,
	*index buffer object,
	*# of indices that make up the model
	*/

	unsigned handle, vbo, ibo, size;
};

Geometry makeGeometry(const Vertex *verts, size_t vsize, const unsigned *idxs, size_t isize);
void freeGeometry(Geometry &g);


void solveTangents(Vertex *v, size_t vsize, const unsigned *idxs, size_t isize);

struct Shader
{
	unsigned handle;
};

Shader makeShader(const char *vertSource, const char *fragSource);
Shader makeShader(const char *vertSource, const char *tessctr_src, const char *tessevl_src, const char *fragSource);
void freeShader(Shader &s);

struct Texture
{
	unsigned handle;
};

//RGBA = 4 channels
/*
*w = width
*h = height
*c = channels
*/
Texture makeTexture(unsigned w, unsigned h, unsigned c, const unsigned char *pixels, bool isFloat = false);
void freeTexture(Texture &t);



struct Framebuffer
{
	unsigned handle, width, height, nTargets;
	Texture depthTarget;
	Texture targets[8];
};

Framebuffer makeFramebuffer(unsigned w, unsigned h, unsigned c,
	bool hasDepth, unsigned nTargets, unsigned nFloatTargets);
void freeFramebuffer(Framebuffer &fb);