#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "PecaTabuleiro.h"
#include "Primitiva.h"
#include <vector>

using namespace std;

class Tabuleiro {
private:
	vector< vector<PecaTabuleiro*> > tabuleiro;
	vector< vector<PecaTabuleiro*> > pecas_por_jogar;
public:
	static vector<int> cliques;

	Tabuleiro();
	const vector< vector<PecaTabuleiro*>>& getTabuleiro() const;
	const vector< vector<PecaTabuleiro*>>& getPecas() const;
	PecaTabuleiro* getPecaFromCoords(int, int);
	void draw();
	void drawPecas();
	void atualizarPecas();
};

#endif
