#include <cstdlib>
#include <GL/glew.h>
#include <GL/glut.h>
#include "DemoShader.h"

DemoShader::DemoShader(std::string texture) {
	init("../res/shader.vert", "../res/shader.frag");

	CGFshader::bind();

	feupImageLocation = glGetUniformLocation(id(), "feupImage");
	glUniform1i(feupImageLocation, 0);

	deltaTime = glGetUniformLocation(id(), "time");
	glUniform1i(deltaTime,0);

	wind = glGetUniformLocation(id(), "wind");
	glUniform1i(wind, 10);

	feupTexture = new CGFtexture(texture);

	CGFshader::unbind();
}

DemoShader::~DemoShader() {
	delete feupTexture;
}

void DemoShader::bind(float dt) {
	CGFshader::bind();

	glUniform1i(deltaTime, dt);
	glUniform1i(wind, 2);

	glActiveTexture(GL_TEXTURE0);
	feupTexture->apply();
}

void DemoShader::unbind() {
	CGFshader::unbind();
}
