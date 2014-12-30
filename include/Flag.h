#ifndef FLAG_H
#define FLAG_H

#include <string>
#include "DemoShader.h"
#include "Plane.h"
#include "Primitiva.h"

class Flag : public Primitiva {
protected:
	Plane* object;
	DemoShader* shader;
public:
	Flag(std::string);
	~Flag();

	void draw(float, float);
	void draw();
};

#endif
