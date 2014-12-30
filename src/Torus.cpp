#include "Torus.h"
#include <cmath>

Torus::Torus(float inner, float outer, int slices, int loops) {
	this->inner = inner;
	this->outer = outer;
	this->slices = slices;
	this->loops = loops;
}

void Torus::draw(float textS, float textT) {
	int i, j;
	GLfloat theta, phi, theta1;
	GLfloat cosTheta, sinTheta;
	GLfloat cosTheta1, sinTheta1;
	GLfloat ringDelta, sideDelta;

	ringDelta = 2.0 * acos(-1.0) / loops;
	sideDelta = 2.0 * acos(-1.0) / slices;

	theta = 0.0;
	cosTheta = 1.0;
	sinTheta = 0.0;
	for (i = loops - 1; i >= 0; i--) {
		theta1 = theta + ringDelta;
		cosTheta1 = cos(theta1);
		sinTheta1 = sin(theta1);
		glBegin(GL_QUAD_STRIP);
		phi = 0.0;
		for (j = slices; j >= 0; j--) {
			GLfloat cosPhi, sinPhi, dist;

			phi += sideDelta;
			cosPhi = cos(phi);
			sinPhi = sin(phi);
			dist = outer + inner * cosPhi;

			glNormal3f(cosTheta1 * cosPhi, -sinTheta1  *cosPhi, sinPhi);
			glTexCoord2f(((i + 1) / loops)*textS, (dist / slices)*textT);
			glVertex3f(cosTheta1  *dist, -sinTheta1  *dist, inner * sinPhi);
			glNormal3f(cosTheta  *cosPhi, -sinTheta  *cosPhi, sinPhi);
			glTexCoord2f(((i + 0) / loops)*textS, (dist / slices)*textT);
			glVertex3f(cosTheta  *dist, -sinTheta * dist, inner * sinPhi);
		}
		glEnd();
		theta = theta1;
		cosTheta = cosTheta1;
		sinTheta = sinTheta1;
	}
}

void Torus::draw() {
	int i, j;
	GLfloat theta, phi, theta1;
	GLfloat cosTheta, sinTheta;
	GLfloat cosTheta1, sinTheta1;
	GLfloat ringDelta, sideDelta;

	ringDelta = 2.0 * acos(-1.0) / loops;
	sideDelta = 2.0 * acos(-1.0) / slices;

	theta = 0.0;
	cosTheta = 1.0;
	sinTheta = 0.0;
	for (i = loops - 1; i >= 0; i--) {
		theta1 = theta + ringDelta;
		cosTheta1 = cos(theta1);
		sinTheta1 = sin(theta1);
		glBegin(GL_QUAD_STRIP);
		phi = 0.0;
		for (j = slices; j >= 0; j--) {
			GLfloat cosPhi, sinPhi, dist;

			phi += sideDelta;
			cosPhi = cos(phi);
			sinPhi = sin(phi);
			dist = outer + inner * cosPhi;

			glNormal3f(cosTheta1 * cosPhi, -sinTheta1  *cosPhi, sinPhi);
			glVertex3f(cosTheta1  *dist, -sinTheta1  *dist, inner * sinPhi);
			glNormal3f(cosTheta  *cosPhi, -sinTheta  *cosPhi, sinPhi);
			glVertex3f(cosTheta  *dist, -sinTheta * dist, inner * sinPhi);
		}
		glEnd();
		theta = theta1;
		cosTheta = cosTheta1;
		sinTheta = sinTheta1;
	}
}
