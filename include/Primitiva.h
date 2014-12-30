#ifndef PRIMITIVA_H
#define PRIMITIVA_H

#include "CGFobject.h"

class Primitiva {
public:
	virtual void draw(float textS, float textT) = 0;
	virtual void draw() = 0;
};

#endif
