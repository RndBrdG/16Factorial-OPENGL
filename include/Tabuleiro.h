#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "PecaTabuleiro.h"
#include <vector>

using namespace std;

class Tabuleiro {
private:
	vector< vector<PecaTabuleiro*> > tabuleiro;
	vector< vector<PecaTabuleiro*> > pecas_por_jogar;
public:
	static vector<int> cliques;

	Tabuleiro();
	vector< vector<PecaTabuleiro*>> getTab(){
		return this->tabuleiro;
	};
	const vector< vector<PecaTabuleiro*>>& getTabuleiro() const;
	const vector< vector<PecaTabuleiro*>>& getPecas() const;
	PecaTabuleiro* getPecaFromCoords(int, int);
	void draw();
	void drawPecas();
	void atualizarPecas();
};

#endif
