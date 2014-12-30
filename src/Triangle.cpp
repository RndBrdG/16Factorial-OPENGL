#include "Triangle.h"
#include <cmath>

Triangle::Triangle(float x1, float x2, float x3, float y1, float y2, float y3, float z1, float z2, float z3) {
	this->x1 = x1;
	this->x2 = x2;
	this->x3 = x3;
	this->y1 = y1;
	this->y2 = y2;
	this->y3 = y3;
	this->z1 = z1;
	this->z2 = z2;
	this->z3 = z3;
}

void Triangle::draw(float textS, float textT) {
	float a = sqrt(pow((x1 - x3), 2) + pow((y1 - y3), 2) + pow((z1 - z3), 2));
	float b = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2) + pow((z2 - z1), 2));
	float c = sqrt(pow((x3 - x2), 2) + pow((y3 - y2), 2) + pow((z3 - z2), 2));
	float teta = (a*a + b*b - c*c) / (2 * a*b);
	float beta = (a*a - b*b + c*c) / (2 * a*c);
	float alpha = (-a*a + b*b + c*c) / (2 * b*c);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glScalef(1 / textS, 1 / textT, 1);
	glMatrixMode(GL_MODELVIEW);
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0, 1);
	glTexCoord2d(0, 0);
	glVertex3f(this->x1, this->y1, this->z1);
	glTexCoord2d(c - a*beta, a*beta);
	glVertex3f(this->x2, this->y2, this->z2);
	glTexCoord2d(c, 0);
	glVertex3f(this->x3, this->y3, this->z3);
	glEnd();
}

void Triangle::draw() {
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0, 1);
	glVertex3f(this->x1, this->y1, this->z1);
	glVertex3f(this->x2, this->y2, this->z2);
	glVertex3f(this->x3, this->y3, this->z3);
	glEnd();
}
