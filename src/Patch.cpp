#include "Patch.h"
#include <cmath>
#include <iostream>

Patch::Patch(int order, int partsU, int partsV, GLenum compute) {
	this->order = order + 1;
	this->partsU = partsU;
	this->partsV = partsV;
	this->compute = compute;
}

void Patch::addCtrlPoint(vector<float> point) {
	if (ctrlPoints.size() < pow(order + 1, 2.)) ctrlPoints.push_back(point);
}

void Patch::draw(float textS, float textT) {
	float* texturepoints = new float[ctrlPoints.size() * 2];
	for (int u = 0, i = 0; u < order; u++) {
		for (int v = 0; v < order; v++) {
			texturepoints[i++] = static_cast<float>(v) / order;
			texturepoints[i++] = static_cast<float>(u) / order;
		}
	}

	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0., 1., 2, order, 0., 1., 2 * order, order, texturepoints);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	draw();

	glDisable(GL_MAP2_TEXTURE_COORD_2);

	delete texturepoints;
}

void Patch::draw() {
	float* ctrlpoints = new float[ctrlPoints.size() * 3];
	for (int i = 0, j = 0; i < ctrlPoints.size() * 3;) {
		ctrlpoints[i++] = ctrlPoints[j][0];
		ctrlpoints[i++] = ctrlPoints[j][1];
		ctrlpoints[i++] = ctrlPoints[j++][2];
	}

	glFrontFace(GL_CW);
	glDisable(GL_CULL_FACE);

	glMap2f(GL_MAP2_VERTEX_3, 0., 1., 3, order, 0., 1., 3 * order, order, ctrlpoints);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);

	glMapGrid2f(partsU, 0., 1., partsV, 0., 1.);
	glEvalMesh2(compute, 0, partsU, 0, partsV);

	glDisable(GL_AUTO_NORMAL);
	glDisable(GL_MAP2_VERTEX_3);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	delete ctrlpoints;
}
