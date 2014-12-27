#ifndef PECATABULEIRO_H
#define PECATABULEIRO_H

#include "CGFappearance.h"
#include "Primitiva.h"
#include <string>
#include <vector>

class PecaTabuleiro: public Primitiva {
private:
	static CGFappearance aparencia;
	static Rectangle forma;
	std::vector<bool> estrutura;
public:
	PecaTabuleiro(/*const std::vector<bool>&*/);

	const std::vector<bool>& getEstrutura() const;

	void draw(float, float);
	void draw();
};

#endif
