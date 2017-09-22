#pragma once

#include "RenderObject.h"

Texture loadTexture(const char *path);

Shader loadShader(const char * vPath, const char * fPath);


Geometry loadGeometry(const char *path);