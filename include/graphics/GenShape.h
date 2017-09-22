#pragma once


struct Geometry;

Geometry makeRectangle(float x, float y, float w, float h);

Geometry makeCheckerboard(int dim, float size);

Geometry makeNGon(size_t sides, float r);
Geometry makeNGon(size_t sides, float r, float x, float y);