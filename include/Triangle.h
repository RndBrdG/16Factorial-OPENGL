#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Primitiva.h"

class Triangle : public Primitiva {
	float x1, x2, x3;
	float y1, y2, y3;
	float z1, z2, z3;
public:
	Triangle(float x1, float x2, float x3, float y1, float y2, float y3, float z1, float z2, float z3);
	void draw(float textS, float textT);
	void draw();
};

#endif
