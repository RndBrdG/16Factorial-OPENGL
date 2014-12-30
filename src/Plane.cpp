#include "Plane.h"

Plane::Plane(int parts) {
	this->parts = parts;
}

void Plane::draw(float textS, float textT) {
	GLfloat ctrlvertex[4][3] = {
		{ 0., 0., 0. },
		{ 1., 0., 0. },
		{ 0., 0., 1. },
		{ 1., 0., 1. }
	};

	GLfloat ctrlnormal[4][3] = {
		{ 0., 1., 0. },
		{ 0., 1., 0. },
		{ 0., 1., 0. },
		{ 0., 1., 0. }
	};

	GLfloat ctrltex[4][2] = {
		{ 0., 0. },
		{ 0., 1. },
		{ 1., 0. },
		{ 1., 1. }
	};

	glMap2f(GL_MAP2_VERTEX_3, 0., 1., 3, 2, 0., 1., 6, 2, &ctrlvertex[0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMap2f(GL_MAP2_NORMAL, 0., 1., 3, 2, 0., 1., 6, 2, &ctrlnormal[0][0]);
	glEnable(GL_MAP2_NORMAL);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0., 1., 2, 2, 0.0, 1.0, 4, 2, &ctrltex[0][0]);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	glMapGrid2f(parts, 0., 1., parts, 0., 1.);
	glEvalMesh2(GL_FILL, 0, parts, 0, parts);
	
	glDisable(GL_MAP2_TEXTURE_COORD_2);
	glDisable(GL_MAP2_NORMAL);
	glDisable(GL_MAP2_VERTEX_3);
}

void Plane::draw() {
	draw(0., 0.);
}
