#ifndef GLOBALS_H
#define GLOBALS_H

#include "CGFscene.h"

class Globals {
	friend class XMLScene;

protected:
	GLenum polygonMode;
	GLenum shadeModel;
	float bkgColorR, bkgColorG, bkgColorB, bkgColorA;

	GLenum cullFace;
	GLenum frontFace;

	bool dblSidedLight;
	bool localLight;
	bool lightEnabled;
	float ambLightR, ambLightG, ambLightB, ambLightA;

public:
	Globals();
	void setPolygonMode(GLenum polygonMode);
	GLenum getPolygonMode(), getShadeModel();
	float getBkgColorR(), getBkgColorG(), getBkgColorB(), getBkgColorA();

	GLenum getCullFace();
	GLenum getFrontFace();

	bool getDblSidedLight();
	bool getLocalLight();
	bool getLightEnabled();
	float getAmbLightR(), getAmbLightG(), getAmbLightB(), getAmbLightA();
};

#endif
