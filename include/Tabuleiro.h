#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "Socket.h"
#include "Animation.h"
#include "PecaTabuleiro.h"
#include <map>
#include <vector>
#include <stack>

#define VELOCIDADE 40 // 0.4

using namespace std;

typedef struct Jogada {
	vector<int> cliques;
} jogada;

class Tabuleiro {
private:
	Socket plogcon;
	Rect placar;
	vector<vector<PecaTabuleiro*>> tabuleiro;
	vector<vector<PecaTabuleiro*>> pecas_por_jogar;
	Rect pecaRodar;
	stack<Jogada> jogadas;
	vector<int> cliques;
	float rotateAngle;
	bool jogador; // true = 1, false = 2
	string dificuldade;
	string tipoDeJogo; // PVP - PLAYER VS PLAYER || PVC - PLAYER VS COMPUTER
	unsigned long tempoInicial;
	int* tempoDecorrido;
	bool revive;

public:
	Tabuleiro();

	const vector<vector<PecaTabuleiro*>>& getTabuleiro() const;
	const vector<vector<PecaTabuleiro*>>& getPecas() const;
	PecaTabuleiro* getPecaFromCoords(int, int);
	stack<Jogada> &getJogadas();
	const vector<int> getCliques();
	const float &getRotateAngle() const;
	bool getJogador() const;
	bool getRevive() const;

	string getDificuldade() const;
	string getTipoDeJogo() const;
	int* getTempoDecorrido() const;
	void setRotateAngle(float rotateAngle);
	void setDificuldade(string dificuldade);
	void setTipoDeJogo(string tipoDeJogo);
	void setJogador(bool value);

	void draw();
	void drawPecas();
	void drawPlacar();
	void atualizarPecas();
	void addClique(int clique);
	void resetTabuleiro();
	void undo();
	void setRevive();
	void clearCliques();
	void clearJogadas();
	string toString();
};

#endif
