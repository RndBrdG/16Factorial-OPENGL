#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#include "CGFscene.h"
#include "CGFshader.h"
#include "Graph.h"
#include "XMLScene.h"
#include "Animation.h"
#include "Tabuleiro.h"

class DemoScene : public CGFscene {
	friend class TPinterface;
public:
	void init();
	void display();
	void update(unsigned long t);
	void activateCamera(int id);
	const Graph& getElementos();
	vector<Camera*>& getCamaras();

	DemoScene(char* filename);
	~DemoScene();
private:
	XMLScene parser;
	Graph elementos;
	Tabuleiro tabuleiro;
	vector<Camera*> camaras;
	int wind;
};

#endif
