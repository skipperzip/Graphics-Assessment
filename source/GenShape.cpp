
#include "graphics\RenderObject.h"
#include "graphics\Vertex.h"
#include "glm\glm.hpp"
#include <math.h>
#include "..\include\graphics\GenShape.h"


Geometry makeRectangle(float x, float y, float w, float h)
{
	Vertex v[4] =
	{ {{x - w, y + h, w + h / 2, 1}, {1,0,0,1}, { x - w, y + h }},
	{{x + w, y + h, w + h / 2, 1}, {1,0,0,1}, { x + w, y + h }},
	{{x + w, y - h, w + h / 2, 1}, {1,0,0,1}, { x + w, y - h }},
	{{x - w, y - h, w + h / 2, 1}, {1,0,0,1}, { x - w, y - h }} };
	unsigned idx[6] = { 0,1,2,2,3,0 };
	Geometry retval = makeGeometry(v, 4, idx, 6);

	return retval;
}

Geometry makeNGon(size_t sides, float r)
{
	//total vertices
	unsigned vsize;
	if (sides <= 4) vsize = sides;
	else vsize = sides + 1;

	//vsize = sides;

	//triangles * 3
	unsigned isize;
	if (sides <= 3) isize = sides;	//point/line/triangle
	else if (sides == 4) isize = 6;	//special case for rectangles
	else isize = sides * 3;			//circle of triangles
	
	Vertex *verts = new Vertex[vsize];
	unsigned *idxs = new unsigned[isize];


	//Populate vertices
	float a = (2 * 3.14159265359)/sides;

	verts[0] = { { 0,0,0,1 },{ 1,1,1,1 },{0,0} };
	for (unsigned i = 1; i < vsize; i++)
	{
		double x = sin((i - 1)*a) * r; //angle to vector
		double y = cos((i - 1)*a) * r;

		verts[i] = { {x,y,0,1},{x,y,.5,1},{x,y} };

	}
	//verts[vsize-1] = { { 0,0,0,0 },{ 1,0,0,1 } };

	//Populate indices
	//I can't math so this is what i do
	int count1 = 1;
	for (unsigned i = 0; i < isize; i++)
	{
		int count = i % 3;
		switch (count)
		{
		case 0: idxs[i] = 0; break;
		case 1: idxs[i] = count1; break;
		case 2: idxs[i] = ++count1; break;
		default:
			break;
		}
	}
	idxs[isize-1] = 1;

	Geometry retval = makeGeometry(verts, vsize, idxs, isize);
	
	delete[] verts;
	delete[] idxs;

	return retval;

}

Geometry makeNGon(size_t sides, float r, float x, float y)
{
	//total vertices
	unsigned vsize;
	if (sides <= 4) vsize = sides;
	else vsize = sides + 1;

	//vsize = sides;

	//triangles * 3
	unsigned isize;
	if (sides <= 3) isize = sides;	//point/line/triangle
	else if (sides == 4) isize = 6;	//special case for rectangles
	else isize = sides * 3;			//circle of triangles

	Vertex *verts = new Vertex[vsize];
	unsigned *idxs = new unsigned[isize];


	//Populate vertices
	float a = (2 * 3.14159265359) / sides;

	verts[0] = { { x,y,0,1 },{ 1,1,1,1 },{ 0,0 } };
	for (unsigned i = 1; i < vsize; i++)
	{
		double xOffset = sin((i - 1)*a) * r; //angle to vector
		double yOffset = cos((i - 1)*a) * r;

		verts[i] = { { x+xOffset,y+yOffset,0,1 },{ xOffset,yOffset,.5,1 },{ xOffset,yOffset } };

	}
	//verts[vsize-1] = { { 0,0,0,0 },{ 1,0,0,1 } };

	//Populate indices
	//I can't math so this is what i do
	int count1 = 1;
	for (unsigned i = 0; i < isize; i++)
	{
		int count = i % 3;
		switch (count)
		{
		case 0: idxs[i] = 0; break;
		case 1: idxs[i] = count1; break;
		case 2: idxs[i] = ++count1; break;
		default:
			break;
		}
	}
	idxs[isize - 1] = 1;

	Geometry retval = makeGeometry(verts, vsize, idxs, isize);

	delete[] verts;
	delete[] idxs;

	return retval;
}

Geometry makeCheckerboard(int dim, float size)
{
	unsigned vdim = dim + 1;

	unsigned vsize = vdim*vdim;			//# of vertices
	unsigned isize = 3 * 2 * dim * dim;	//# of triangles
	Vertex *verts = new Vertex[vsize];
	unsigned *idxs = new unsigned[isize];

	float step = size / dim;
	float offset = size/2;
	int l = 0;	//idk why 'l'

	for (int i = 0; i < vsize; i++)
	{
		float x = (i % vdim) * step - offset;
		float y = (i / vdim) * step - offset;

		verts[i].pos = { x,y,0,1 };
		verts[i].color = { rand() / (float)RAND_MAX,rand() / (float)RAND_MAX,rand() / (float)RAND_MAX,1 };
		verts[i].texCoord = { x,y };


		if (//(i == 1 && dim > 1)||	//SPECIAL cases for 1x1 and 2x2
			(i % vdim != vdim-1)&&		//right-end limit
			(i/vdim != vdim - 1)	//bottom limit
			)	
		{
			idxs[l++] = i;
			idxs[l++] = i + 1;
			idxs[l++] = i + vdim;
		
			idxs[l++] = i + 1;
			idxs[l++] = i + vdim;
			idxs[l++] = i + vdim + 1;
		}
	}

	Geometry retval = makeGeometry(verts, vsize, idxs, isize);

	delete[] verts;
	delete[] idxs;

	return retval;
}
