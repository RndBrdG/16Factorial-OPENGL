#include <math.h>
#include "Primitiva.h"

Rectangle::Rectangle(float x1, float x2, float y1, float y2) {
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
}

void Rectangle::draw(float textS, float textT) {
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glScalef((x2 - x1) / textS, (y2 - y1) / textT, 1);
	glMatrixMode(GL_MODELVIEW);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2d(0, 0);
	glVertex2f(x1, y1);
	glTexCoord2d(1, 0);
	glVertex2f(x2, y1);
	glTexCoord2d(1, 1);
	glVertex2f(x2, y2);
	glTexCoord2d(0, 1);
	glVertex2f(x1, y2);
	glEnd();
}

void Rectangle::draw() {
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glVertex3f(x1, y1,0);
	glVertex3f(x2, y1,0);
	glVertex3f(x2, y2,0);
	glVertex3f(x1, y2,0);
	glEnd();
}

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
		glVertex2f(x ,y );
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

Sphere::Sphere(float radius, int slices, int stacks) {
	this->radius = radius;
	this->slices = slices;
	this->stacks = stacks;
	GLUquadric* esfera = gluNewQuadric();
	this->sph = esfera;
}

void Sphere::draw(float textS, float textT) {
	gluQuadricTexture(this->sph, true);
	draw();
}

void Sphere::draw() {
	gluSphere(this->sph, this->radius, this->slices, this->stacks);
}

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
