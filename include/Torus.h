#ifndef TORUS_H
#define TORUS_H

#include "Primitiva.h"

class Torus : public Primitiva {
	float inner, outer;
	int slices, loops;
public:
	Torus(float inner, float outer, int slices, int loops);
	void draw(float textS, float textT);
	void draw();
};

#endif
