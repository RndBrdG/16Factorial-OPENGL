#ifndef SPHERE_H
#define SPHERE_H

#include "Primitiva.h"

class Sphere : public Primitiva {
	GLUquadric *sph;
	float radius;
	int slices, stacks;
public:
	Sphere(float radius, int slices, int stacks);
	void draw(float textS, float textT);
	void draw();
	~Sphere() {
		gluDeleteQuadric(sph);
	}
};

#endif
