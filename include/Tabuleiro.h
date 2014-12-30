#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "Animation.h"
#include "PecaTabuleiro.h"
#include <map>
#include <vector>
#include <stack>

using namespace std;

typedef struct Jogada {
	vector<int> cliques;
} jogada;

class Tabuleiro {
private:
	vector<vector<PecaTabuleiro*>> tabuleiro;
	vector<vector<PecaTabuleiro*>> pecas_por_jogar;
	stack<Jogada> jogadas;
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
	void atualizarPecas();
	void addClique(int clique);
	void resetTabuleiro();
	void setRotateAngle(float angle);
	stack<Jogada> &getJogadas();
	const vector<int> getCliques();
};

#endif
