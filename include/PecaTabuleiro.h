#ifndef PECATABULEIRO_H
#define PECATABULEIRO_H

#include "CGFappearance.h"
#include "Rect.h"
#include <string>
#include <vector>

class PecaTabuleiro: public Primitiva {
private:
	static Rect forma;
	static std::vector<CGFtexture*> texturas;
	static CGFappearance aparencia;
	vector<vector<bool>> estrutura;
	float x, y;
	float x_inicial, y_inicial;
	bool fixa, animada;
	int rotacoes;
public:
	PecaTabuleiro(float, float, std::vector<std::vector<bool>> = std::vector<std::vector<bool>>());

	static void addTextura(std::string);
	static void setTextura(int);

	void setX(float), setY(float), setFixa(), setAnimada(bool);
	string toString();

	const vector<vector<bool>>& getEstrutura() const;
	float getX() const, getY() const;
	float getXinicial() const, getYinicial() const;
	bool getFixa() const, getAnimada() const;
	int getRotacoes() const;

	void draw(float, float);
	void draw();
	void rodar();
};

#endif
