#include "Globals.h"

Globals::Globals() {
	polygonMode = GL_FILL;
	shadeModel = GL_SMOOTH;
	bkgColorR = 0., bkgColorG = 0., bkgColorB = 0., bkgColorA = 0.;

	cullFace = GL_BACK;
	frontFace = GL_CCW;

	dblSidedLight = false;
	localLight = true;
	lightEnabled = true;
	ambLightR = .2, ambLightG = .2, ambLightB = .2, ambLightA = 1.;
}

void Globals::setPolygonMode(GLenum polygonMode) {
	this->polygonMode = polygonMode;
}

GLenum Globals::getPolygonMode() {
	return polygonMode;
}

GLenum Globals::getShadeModel() {
	return shadeModel;
}

float Globals::getBkgColorR() {
	return bkgColorR;
}

float Globals::getBkgColorG() {
	return bkgColorG;
}

float Globals::getBkgColorB() {
	return bkgColorB;
}

float Globals::getBkgColorA() {
	return bkgColorA;
}

GLenum Globals::getCullFace() {
	return cullFace;
}

GLenum Globals::getFrontFace() {
	return frontFace;
}

bool Globals::getDblSidedLight() {
	return dblSidedLight;
}

bool Globals::getLocalLight() {
	return localLight;
}

bool Globals::getLightEnabled() {
	return lightEnabled;
}

float Globals::getAmbLightR() {
	return ambLightR;
}

float Globals::getAmbLightG() {
	return ambLightG;
}

float Globals::getAmbLightB() {
	return ambLightB;
}

float Globals::getAmbLightA() {
	return ambLightA;
}
