#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "Primitiva.h"
#include <vector>

using namespace std;

class Tabuleiro {
private:
	vector< vector<Primitiva*> > tabuleiro;
	vector< vector<Primitiva*> > pecas_por_jogar;

public:
	Tabuleiro();
	vector< vector<Primitiva*>> getTabuleiro();
	vector< vector<Primitiva*>> getPecas();
	void draw();
	void drawPecas();
};

#endif
