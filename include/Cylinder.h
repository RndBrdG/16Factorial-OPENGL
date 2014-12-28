#ifndef CYLINDER_H
#define CYLINDER_H

#include "Primitiva.h"

class Cylinder : public Primitiva {
	GLUquadric *cylin;
	float base, top, height;
	int slices, stacks;
public:
	Cylinder(float base, float top, float height, int slices, int stacks);
	void draw(float textS, float textT);
	void draw();
	~Cylinder(){
		delete(cylin);
	}
};

#endif
