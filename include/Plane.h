#ifndef PLANE_H
#define PLANE_H

#include "Primitiva.h"

class Plane : public Primitiva {
protected:
	int parts;
public:
	Plane(int);

	void draw(float, float);
	void draw();
};

#endif
