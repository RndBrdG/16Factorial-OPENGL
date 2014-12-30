#include "Light.h"

int Light::num = 0;

Light::Light(unsigned int lightid, float* pos, float* dir, float angle, float exponent) : lightNum(num), CGFlight(lightid, pos, dir) {
	this->angle = angle;
	this->exponent = exponent;
	enabled = true;
	marker = true;

	ambient[0] = 0.;
	ambient[1] = 0.;
	ambient[2] = 0.;
	ambient[3] = 0.;

	diffuse[0] = 0.;
	diffuse[1] = 0.;
	diffuse[2] = 0.;
	diffuse[3] = 0.;

	specular[0] = 0.;
	specular[1] = 0.;
	specular[2] = 0.;
	specular[3] = 0.;

	direction[0] = dir != NULL ? dir[0] : 0;
	direction[1] = dir != NULL ? dir[1] : 0;
	direction[2] = dir != NULL ? dir[2] : -1;

	num++;

	onOff = 1; //DEBUG
}

int Light::getLightNum() {
	return lightNum;
}

float Light::getAngle() {
	return angle;
}

bool Light::getEnabled() {
	return enabled;
}

bool Light::getMarker() {
	return marker;
}

float Light::getExponent() {
	return exponent;
}
