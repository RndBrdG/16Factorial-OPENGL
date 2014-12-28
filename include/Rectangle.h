#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Primitiva.h"

class Rectangle : public Primitiva {
	float x1, x2;
	float y1, y2;
public:
	Rectangle(float x1, float x2, float y1, float y2);
	void draw(float textS, float textT);
	void draw();
};

#endif
