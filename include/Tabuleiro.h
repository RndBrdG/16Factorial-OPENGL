#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "Animation.h"
#include "PecaTabuleiro.h"
#include <map>
#include <vector>

using namespace std;

class Tabuleiro {
private:
	vector<vector<PecaTabuleiro*>> tabuleiro;
	vector<vector<PecaTabuleiro*>> pecas_por_jogar;
	map<PecaTabuleiro*, Animation*> animacoes;
	vector<int> cliques;
	float rotateAngle;
public:
	string dificuldade;
	string TipoDeJogo;		// PVP - PLAYER VS PLAYER || PVC - PLAYER VS COMPUTER
	Tabuleiro();
	const vector<vector<PecaTabuleiro*>>& getTabuleiro() const;
	const vector<vector<PecaTabuleiro*>>& getPecas() const;
	const float &getRotateAngle() const;

	PecaTabuleiro* getPecaFromCoords(int, int);
	void draw();
	void drawPecas();
	void animar(unsigned long t);
	void addClique(int clique);
	void resetTabuleiro();
	void setRotateAngle(float angle);
	const vector<int> getCliques(){
		return this->cliques;
	}
};

#endif
