#include "Cylinder.h"
#include <cmath>

Cylinder::Cylinder(float base, float top, float height, int slices, int stacks) {
	this->base = base;
	this->top = top;
	this->height = height;
	this->slices = slices;
	this->stacks = stacks;
	GLUquadric* cilindro = gluNewQuadric();
	this->cylin = cilindro;
}

void Cylinder::draw(float textS, float textT) {
	glBegin(GL_POLYGON);
	for (int i = slices; i > 0; i--) {
		float theta = 2. * acos(-1.) * float(i) / float(slices);

		float x = base * cosf(theta);
		float y = base * sinf(theta);

		glTexCoord2f(y * textT, x * textS);
		glNormal3f(x / sqrt(pow(x, 2) + pow(y, 2)), y / sqrt(pow(x, 2) + pow(y, 2)), 0);
		glVertex2f(x, y);
	}
	glEnd();

	gluQuadricTexture(this->cylin, GL_TRUE);
	gluCylinder(this->cylin, this->base, this->top, this->height, this->slices, this->stacks);

	glPushMatrix();
	glTranslatef(0., 0., height);
	glBegin(GL_POLYGON);
	for (int i = 0; i < slices; i++) {
		float theta = 2. * acos(-1.) * float(i) / float(slices);

		float x = top * cosf(theta);
		float y = top * sinf(theta);

		glTexCoord2f(y * textT, x * textS);
		glNormal3f(x / sqrt(pow(x, 2) + pow(y, 2)), y / sqrt(pow(x, 2) + pow(y, 2)), 0);
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();
};

void Cylinder::draw() {
	glBegin(GL_POLYGON);
	for (int i = slices; i > 0; i--) {
		float theta = 2. * acos(-1.) * float(i) / float(slices);

		float x = base * cosf(theta);
		float y = base * sinf(theta);

		glNormal3f(x / sqrt(pow(x, 2) + pow(y, 2)), y / sqrt(pow(x, 2) + pow(y, 2)), 0);
		glVertex2f(x, y);
	}
	glEnd();

	gluCylinder(this->cylin, this->base, this->top, this->height, this->slices, this->stacks);

	glPushMatrix();
	glTranslatef(0., 0., height);
	glBegin(GL_POLYGON);
	for (int i = 0; i < slices; i++) {
		float theta = 2. * acos(-1.) * float(i) / float(slices);

		float x = top * cosf(theta);
		float y = top * sinf(theta);

		glNormal3f(x / sqrt(pow(x, 2) + pow(y, 2)), y / sqrt(pow(x, 2) + pow(y, 2)), 0);
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();
}
