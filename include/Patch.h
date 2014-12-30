#ifndef PATCH_H
#define PATCH_H

#include "CGFscene.h"
#include "Primitiva.h"

class Patch : public Primitiva {
protected:
	int order;
	int partsU;
	int partsV;
	GLenum compute;
	std::vector<std::vector<float> > ctrlPoints;
public:
	Patch(int, int, int, GLenum);

	void addCtrlPoint(std::vector<float>);
	void draw(float, float);
	void draw();
};

#endif
