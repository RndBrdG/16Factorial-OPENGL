#ifndef PRIMITIVA_H
#define PRIMITIVA_H

#include "CGFobject.h"

class Primitiva {
public:
	virtual void draw(float textS, float textT) = 0;
	virtual void draw() = 0;
};

class Rectangle : public Primitiva {
	float x1, x2;
	float y1, y2;
public:
	Rectangle(float x1, float x2, float y1, float y2);
	void draw(float textS, float textT);
	void draw();
};

class Triangle : public Primitiva {
	float x1, x2, x3;
	float y1, y2, y3;
	float z1, z2, z3;
public:
	Triangle(float x1, float x2, float x3, float y1, float y2, float y3, float z1, float z2, float z3);
	void draw(float textS, float textT);
	void draw();
};

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

class Sphere : public Primitiva {
	GLUquadric *sph;
	float radius;
	int slices, stacks;
public:
	Sphere(float radius, int slices, int stacks);
	void draw(float textS, float textT);
	void draw();
	~Sphere(){
		delete(sph);
	}
};

class Torus : public Primitiva {
	float inner, outer;
	int slices, loops;
public:
	Torus(float inner, float outer, int slices, int loops);
	void draw(float textS, float textT);
	void draw();
};

#endif
