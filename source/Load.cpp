
#include "graphics\Load.h"
#include "graphics\RenderObject.h"
#include "graphics\Vertex.h"

#define STB_IMAGE_IMPLEMENTATION
#include "STB\stb_image.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "OBJ\tiny_obj_loader.h"

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <random>
using namespace std;

glm::vec4 randColor()
{
	return {
	rand() / (float)RAND_MAX,
	rand() / (float)RAND_MAX,
	rand() / (float)RAND_MAX, 1 };
}

Texture loadTexture(const char * path)
{
	Texture retval = { 0 };

	//width, heigh, comp(???)
	int w, h, c;
	unsigned char *pixels;

	//gotta do this so the pixels are ok for use with objs
	stbi_set_flip_vertically_on_load(true);

	pixels = stbi_load(path, &w, &h, &c, STBI_default);
	retval = makeTexture(w, h, c, pixels);
	//frees pixels' data
	stbi_image_free(pixels);

	return retval;
}

//helper function
//credit: http://www.nexcius.net/2012/11/20/how-to-load-a-glsl-shader-in-opengl-using-c/
std::string readFile(const char *filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
	cout << line;

	fileStream.close();
	return content;
}

Shader loadShader(const char * vPath, const char * fPath)
{
	Shader retval = { 0 };

	//load all the text as a char array for each shader
	string vString = readFile(vPath);
	string fString = readFile(fPath);
	const char *vsource = vString.c_str();
	const char *fsource = fString.c_str();

	retval = makeShader(vsource, fsource);

	return retval;
}

Geometry loadGeometry(const char * path)
{
	Geometry retval = { 0,0,0,0 };

	tinyobj::attrib_t attrib;				//Vertex Data
	vector<tinyobj::shape_t> shapes;		//Triangular Data, indices
	vector<tinyobj::material_t> materials;	//Paths to textures (not used right now?)
	string err;

	tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);

	size_t isize = shapes[0].mesh.indices.size();
	size_t *indices = new unsigned[isize];

	size_t vsize = isize;
	Vertex *verts = new Vertex[vsize];

	for (int i = 0; i < isize; i++)
	{
		indices[i] = i;

		int pi = shapes[0].mesh.indices[i].vertex_index;
		int ni = shapes[0].mesh.indices[i].normal_index;
		int ti = shapes[0].mesh.indices[i].texcoord_index;

		//p is the memory address of the 3 coordinates of the vertex starting at i
		const float *p = &attrib.vertices[pi * 3];	//3x
		const float *n = &attrib.normals[ni * 3];	//3x
		const float *t = &attrib.texcoords[ti * 2];	//2x

		verts[i].pos = { p[0],p[1],p[2],1 };
		verts[i].texCoord = { t[0],t[1] };
		verts[i].normal = { n[0],n[1],n[2],0 };

		verts[i].color = randColor();
	}

	solveTangents(verts, vsize, indices, isize);

	retval = makeGeometry(verts, vsize, indices, isize);
	delete[] verts;
	delete[] indices;

	return retval;
}
