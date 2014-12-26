#include "Flag.h"
#include "CGFapplication.h"
#include <iostream>

Flag::Flag(std::string texture) {
	object = new Plane(20);
	shader = new DemoShader(texture);
}

Flag::~Flag() {
	delete object;
	delete shader;
}

void Flag::draw(float textS, float textT) {
	draw();
}


void Flag::draw() {
	static float i = 0.03;
	shader->bind(i);
	object->draw();
	shader->unbind();
	i += 0.01;
}
