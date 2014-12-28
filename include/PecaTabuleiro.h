#ifndef PECATABULEIRO_H
#define PECATABULEIRO_H

#include "CGFappearance.h"
#include "Primitiva.h"
#include "Rectangle.h"
#include <string>
#include <vector>

class PecaTabuleiro: public Primitiva {
private:
	static CGFappearance aparencia;
	static Rectangle forma;
	std::vector<std::vector<bool>> estrutura;
	float x, y;
public:
	PecaTabuleiro(float, float, std::vector<std::vector<bool>> = std::vector<std::vector<bool>>());

	const std::vector<std::vector<bool>>& getEstrutura() const;
	void setX(float), setY(float);
	float getX() const, getY() const;

	void draw(float, float);
	void draw();
};

#endif
