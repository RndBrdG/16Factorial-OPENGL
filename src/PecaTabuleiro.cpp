#include "Graph.h"
#include "PecaTabuleiro.h"
#include "Rectangle.h"
#include "Sphere.h"

float ambiente[4] = { 1., 1., 1., 1. }, difusa[4] = { 1., 1., 1., 1. }, especular[4] = { 1., 1., 1., 1. };
float brilho = 0.;
std::vector<CGFtexture*> PecaTabuleiro::texturas = vector<CGFtexture*>();
CGFappearance PecaTabuleiro::aparencia(ambiente, difusa, especular, brilho);
Rectangle PecaTabuleiro::forma(0., 3., 0., 3.);

PecaTabuleiro::PecaTabuleiro(float x, float y, std::vector<std::vector<bool>> estrutura) : x(x), y(y), estrutura(estrutura), fixa(false), animada(false) {
	this->x_inicial = x;
	this->y_inicial = y;
}

void PecaTabuleiro::addTextura(std::string textura) {
	texturas.push_back(new CGFtexture(textura));
}

void PecaTabuleiro::setTextura(int indice) {
	aparencia.setTexture(texturas[indice]);
}

void PecaTabuleiro::setX(float x) {
	this->x = x;
}

void PecaTabuleiro::setY(float y) {
	this->y = y;
}

void PecaTabuleiro::setFixa() {
	fixa = true;
}

void PecaTabuleiro::setAnimada(bool animada) {
	this->animada = animada;
}

const std::vector<std::vector<bool>>& PecaTabuleiro::getEstrutura() const {
	return estrutura;
}

float PecaTabuleiro::getX() const {
	return x;
}

float PecaTabuleiro::getY() const {
	return y;
}

bool PecaTabuleiro::getFixa() const {
	return fixa;
}

bool PecaTabuleiro::getAnimada() const {
	return animada;
}

void PecaTabuleiro::draw(float textS, float textT) {
	draw();
}

void PecaTabuleiro::draw() {
	aparencia.apply();
	forma.draw(3., 3.);
	float translX = .5, translY = .5 * 5;

	for (auto it = estrutura.cbegin(); it != estrutura.cend(); it++) {
		for (auto it2 = it->cbegin(); it2 != it->cend(); it2++) {
			if (*it2) {
				glPushMatrix();
				glTranslatef(translX, translY, .25 * .3);
				glScalef(1, 1, .25);

				Sphere bola(.3, 10, 10);
				bola.draw();

				glPopMatrix();
			}

			translX += .5 * 2;
		}

		translX = .5;
		translY -= .5 * 2;
	}
}

void PecaTabuleiro::rodar() {
	std::vector<std::vector<bool>> novaEstrutura(3, vector<bool>(3));
	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 3; ++j)
			novaEstrutura[i][j] = estrutura[3 - 1 - j][i];
	estrutura = novaEstrutura;
}

float PecaTabuleiro::getXinicial() const {
	return this->x_inicial;
}

float PecaTabuleiro::getYinicial() const{
	return this->y_inicial;
}

void PecaTabuleiro::setXinicial(float x_inicial){
	this->x_inicial = x_inicial;
}

void PecaTabuleiro::setYinicial(float y_inicial){
	this->y_inicial = y_inicial;
}

string PecaTabuleiro::toString(){
	string peca = "";

	if (estrutura.size() != 0){
		peca.append("[");
		for (size_t i = 0; i < 3; i++)
		{
			peca.append("[");
			for (size_t j = 0; j < 3; j++)
			{
				if (estrutura[i][j] == true)
				{
					if (j == 0) peca.append("o");
					else peca.append(",'o'");
				}
				else{
					if (j == 0) peca.append("' '");
					else peca.append(",' '");
				}
			}
			if (i != 2) peca.append("],");
			else peca.append("]");
		}
		peca.append("]");
	}
	else{
		peca.append("[");
		for (size_t i = 0; i < 3; i++)
		{
			if( i != 2) peca.append("[' ',' ',' '],");
			else peca.append("[' ',' ',' ']");
		}
		peca.append("]");
	}

	return peca;
}
