#ifndef DEMOSHADER_H
#define DEMOSHADER_H

#include "CGFshader.h"
#include "CGFtexture.h"

class DemoShader : public CGFshader {
protected:
	CGFtexture* feupTexture;
	int feupImageLocation;
	int deltaTime;
	int wind;
public:
	DemoShader(std::string);
	~DemoShader();

	void bind(float dt);
	void unbind();
};

#endif
