#pragma once

#include "glm\glm.hpp"

struct Vertex
{
	glm::vec4 pos;	// 4 floats = 16 bytes, pos starts at byte 0 and eats up to byte 15
	glm::vec4 color; // color starts at... 16
	glm::vec2 texCoord;
	//make sure the w (4th value) is set to 0 
	glm::vec4 normal;

	glm::vec4 tangent;
	glm::vec4 bitangent;  //aka bitangent
};