#include "Tabuleiro.h"


Tabuleiro::Tabuleiro(){
	for (int i = 0; i < 4; i++){
		vector<Primitiva*> aux;
		for (int j = 0; j < 4; j++){
			Rectangle *a1 = new Rectangle(0, 4, 0, 3);
			aux.push_back(a1);
		}
		this->tabuleiro.push_back(aux);
	}
	
	for (int i = 0; i < 2; i++){
		vector<Primitiva*> aux;
		for (int i = 0; i < 4; i++){
			Rectangle *a1 = new Rectangle(0, 4, 0, 3);
			aux.push_back(a1);
		}
		this->pecas_por_jogar.push_back(aux);
	}
}

vector< vector<Primitiva*>> Tabuleiro::getTabuleiro() {
	return this->tabuleiro;
}

vector< vector<Primitiva*>> Tabuleiro::getPecas() {
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