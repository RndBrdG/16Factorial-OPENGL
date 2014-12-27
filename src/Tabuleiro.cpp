#include "Tabuleiro.h"

Tabuleiro::Tabuleiro(){
	for (int i = 0; i < 4; i++){
		vector<PecaTabuleiro*> aux;
		for (int j = 0; j < 4; j++){
			PecaTabuleiro *a1 = new PecaTabuleiro();
			aux.push_back(a1);
		}
		this->tabuleiro.push_back(aux);
	}
	
	for (int i = 0; i < 2; i++){
		vector<PecaTabuleiro*> aux;
		for (int i = 0; i < 4; i++){
			PecaTabuleiro *a1 = new PecaTabuleiro();
			aux.push_back(a1);
		}
		this->pecas_por_jogar.push_back(aux);
	}
}

const vector<vector<PecaTabuleiro*>>& Tabuleiro::getTabuleiro() const {
	return this->tabuleiro;
}

const vector<vector<PecaTabuleiro*>>& Tabuleiro::getPecas() const {
	return this->pecas_por_jogar;
}

void Tabuleiro::draw(){
	glPushMatrix();
	glPushName(-1);		// Load a default name
	glPopMatrix();

	for (int r = 0; r < 4; r++)
	{
		glPushMatrix();
		glTranslatef(0, r * 4, 0);
		glLoadName(r);
		for (int c = 0; c < 4; c++)
		{
			glPushMatrix();
			glTranslatef((c + 1) * 5, 0, 0);
			//glRotatef(90, 0, 1, 0);
			glPushName(c);
			this->tabuleiro[r][c]->draw();
			glPopName();
			glPopMatrix();
		}
		glPopMatrix();
	}
}

void Tabuleiro::drawPecas(){
	for (int r = 0; r < 2; r++)
	{
		glPushMatrix();
		if (r == 0)
			glTranslatef(-5, 0, 0);
		else glTranslatef(30, 0, 0);
		glLoadName(r+100);
		for (int c = 0; c < 4; c++)
		{
			glPushMatrix();
			glTranslatef(0, (c + 1) * 5, 0);
			//glRotatef(90, 0, 1, 0);
			glPushName(c);
			this->pecas_por_jogar[r][c]->draw();
			glPopName();
			glPopMatrix();
		}
		glPopMatrix();
	}
}
