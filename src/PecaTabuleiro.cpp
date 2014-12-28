#include "Graph.h"
#include "PecaTabuleiro.h"
#include "Rectangle.h"
#include "Sphere.h"

float ambiente[4] = { 1., 1., 1., 1. }, difusa[4] = { 1., 1., 1., 1. }, especular[4] = { 1., 1., 1., 1. };
float brilho = 0.;
std::vector<CGFtexture*> PecaTabuleiro::texturas = vector<CGFtexture*>();
CGFappearance PecaTabuleiro::aparencia(ambiente, difusa, especular, brilho);
Rectangle PecaTabuleiro::forma(0., 3., 0., 3.);

PecaTabuleiro::PecaTabuleiro(float x, float y, std::vector<std::vector<bool>> estrutura) : x(x), y(y), estrutura(estrutura) {
}

void PecaTabuleiro::addTextura(std::string textura) {
	texturas.push_back(new CGFtexture(textura));
}

void PecaTabuleiro::setTextura(int indice) {
	aparencia.setTexture(texturas[indice]);
}

const std::vector<std::vector<bool>>& PecaTabuleiro::getEstrutura() const {
	return estrutura;
}

void PecaTabuleiro::setX(float x) {
	this->x = x;
}

void PecaTabuleiro::setY(float y) {
	this->y = y;
}

float PecaTabuleiro::getX() const {
	return x;
}

float PecaTabuleiro::getY() const {
	return y;
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
