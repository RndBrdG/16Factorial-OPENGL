#include "Graph.h"
#include "PecaTabuleiro.h"

float ambiente[4] = { 1., 1., 1., 1. }, difusa[4] = { 1., 1., 1., 1. }, especular[4] = { 1., 1., 1., 1. };
float brilho = 0.;
CGFappearance PecaTabuleiro::aparencia(ambiente, difusa, especular, brilho);
Rectangle PecaTabuleiro::forma = Rectangle(0., 3., 0., 3.);

PecaTabuleiro::PecaTabuleiro(/*const std::vector<bool>& estrutura*/) {
	aparencia.setTexture("../res/madeirapeca.jpg");
}

void PecaTabuleiro::draw(float textS, float textT) {
	draw();
}

void PecaTabuleiro::draw() {
	aparencia.apply();
	forma.draw(3., 3.);
}
