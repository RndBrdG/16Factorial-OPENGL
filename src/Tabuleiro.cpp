#include "Tabuleiro.h"

Tabuleiro::Tabuleiro() : cliques(vector<int>()), placar(0, 12, 0, 6), jogador(true) {
	PecaTabuleiro::addTextura("../res/glass.jpg");
	PecaTabuleiro::addTextura("../res/plastic.jpg");
	//PecaTabuleiro::addTextura("../res/stone.jpg");
	PecaTabuleiro::addTextura("../res/wood.jpg");
	PecaTabuleiro::setTextura(2);
	this->tipoDeJogo = "PVP";
	this->rotateAngle = 0;
	resetTabuleiro();
}

const vector<vector<PecaTabuleiro*>>& Tabuleiro::getTabuleiro() const {
	return this->tabuleiro;
}

const vector<vector<PecaTabuleiro*>>& Tabuleiro::getPecas() const {
	return this->pecas_por_jogar;
}

PecaTabuleiro* Tabuleiro::getPecaFromCoords(int i, int j) {
	if (i >= 100) return pecas_por_jogar[i - 100][j];
	else return tabuleiro[i][j];
}

stack<Jogada> &Tabuleiro::getJogadas(){
	return this->jogadas;
}

const vector<int> Tabuleiro::getCliques(){
	return this->cliques;
}

const float &Tabuleiro::getRotateAngle() const{
	return this->rotateAngle;
}

bool Tabuleiro::getJogador() const {
	return this->jogador;
}

string Tabuleiro::getDificuldade() const {
	return this->dificuldade;
}

string Tabuleiro::getTipoDeJogo() const {
	return this->tipoDeJogo;
}

void Tabuleiro::setRotateAngle(float rotateAngle) {
	this->rotateAngle = rotateAngle;
}

void Tabuleiro::setDificuldade(string dificuldade) {
	this->dificuldade = dificuldade;
}

void Tabuleiro::setTipoDeJogo(string tipoDeJogo) {
	this->tipoDeJogo = tipoDeJogo;
}

void Tabuleiro::draw() {
	glPushMatrix();
	glPushName(-1);		// Load a default name
	glPopMatrix();

	for (int r = 0; r < 4; r++)
	{
		glPushMatrix();
		glLoadName(r);
		for (int c = 0; c < 4; c++)
		{
			glPushMatrix();
			glTranslatef(tabuleiro[r][c]->getX(), tabuleiro[r][c]->getY(), 0);
			glPushName(c);
			this->tabuleiro[r][c]->draw();
			glPopName();
			glPopMatrix();
		}
		glPopMatrix();
	}
}

void Tabuleiro::drawPecas() {
	for (int r = 0; r < 4; r++)
	{
		glPushMatrix();
		glLoadName(r + 100);
		if (rotateAngle != 0){
			if (r < 2){
				glRotated(rotateAngle, 0, 0, 1);
				glTranslated(1.5, -17.5, 0);
			}
			else {
				glRotated(rotateAngle, 0, 0, 1);
				glTranslated(4.5, -17.5, 0);
			}
		}
		for (int c = 0; c < 4; c++)
		{
			glPushMatrix();
			glTranslatef(pecas_por_jogar[r][c]->getX(), pecas_por_jogar[r][c]->getY(), 0);
			glPushName(c);
			glRotated(-rotateAngle, 0, 0, 1);
			this->pecas_por_jogar[r][c]->draw();
			glPopName();
			glPopMatrix();
		}
		glPopMatrix();
	}
}

void Tabuleiro::drawPlacar() {
	CGFtexture texturaPlacar = jogador ? ("../res/placar_jog1.jpg") : (tipoDeJogo == "PVP" ? ("../res/placar_jog2.jpg") : ("../res/placar_cpu.jpg"));
	texturaPlacar.apply();
	placar.draw(12, 6);
}

void Tabuleiro::resetTabuleiro(){
	this->dificuldade = "EASY";
	float x = 0, y = 4 * 3;

	for (int i = 0; i < 4; i++, y -= 3) {
		vector<PecaTabuleiro*> aux;
		for (int j = 0; j < 4; j++, x += 3) {
			PecaTabuleiro *a1 = new PecaTabuleiro(x, y);
			aux.push_back(a1);
		}
		x = 0;
		this->tabuleiro.push_back(aux);
	}

	vector<PecaTabuleiro*> aux;
	vector<vector<bool>> config;
	PecaTabuleiro* a1;

	x = -8; y = 4 * 5;

	for (int i = 0; i < 3; i++)
		config.push_back(vector<bool>());
	config[0].push_back(true); config[0].push_back(true); config[0].push_back(true);
	config[1].push_back(true); config[1].push_back(false); config[1].push_back(true);
	config[2].push_back(true); config[2].push_back(true); config[2].push_back(true);
	a1 = new PecaTabuleiro(x, y, config);
	aux.push_back(a1);
	y -= 5;

	config.clear();
	for (int i = 0; i < 3; i++)
		config.push_back(vector<bool>());
	config[0].push_back(true); config[0].push_back(true); config[0].push_back(true);
	config[1].push_back(true); config[1].push_back(false); config[1].push_back(false);
	config[2].push_back(true); config[2].push_back(true); config[2].push_back(true);
	a1 = new PecaTabuleiro(x, y, config);
	aux.push_back(a1);
	y -= 5;

	config.clear();
	for (int i = 0; i < 3; i++)
		config.push_back(vector<bool>());
	config[0].push_back(true); config[0].push_back(true); config[0].push_back(true);
	config[1].push_back(true); config[1].push_back(false); config[1].push_back(true);
	config[2].push_back(false); config[2].push_back(true); config[2].push_back(true);
	a1 = new PecaTabuleiro(x, y, config);
	aux.push_back(a1);
	y -= 5;

	config.clear();
	for (int i = 0; i < 3; i++)
		config.push_back(vector<bool>());
	config[0].push_back(true); config[0].push_back(true); config[0].push_back(true);
	config[1].push_back(true); config[1].push_back(false); config[1].push_back(false);
	config[2].push_back(true); config[2].push_back(false); config[2].push_back(true);
	a1 = new PecaTabuleiro(x, y, config);
	aux.push_back(a1);

	x = -4; y = 4 * 5;
	pecas_por_jogar.push_back(aux);
	aux.clear();

	config.clear();
	for (int i = 0; i < 3; i++)
		config.push_back(vector<bool>());
	config[0].push_back(true); config[0].push_back(true); config[0].push_back(true);
	config[1].push_back(true); config[1].push_back(false); config[1].push_back(true);
	config[2].push_back(false); config[2].push_back(false); config[2].push_back(false);
	a1 = new PecaTabuleiro(x, y, config);
	aux.push_back(a1);
	y -= 5;

	config.clear();
	for (int i = 0; i < 3; i++)
		config.push_back(vector<bool>());
	config[0].push_back(true); config[0].push_back(true); config[0].push_back(true);
	config[1].push_back(false); config[1].push_back(false); config[1].push_back(true);
	config[2].push_back(false); config[2].push_back(true); config[2].push_back(true);
	a1 = new PecaTabuleiro(x, y, config);
	aux.push_back(a1);
	y -= 5;

	config.clear();
	for (int i = 0; i < 3; i++)
		config.push_back(vector<bool>());
	config[0].push_back(true); config[0].push_back(true); config[0].push_back(true);
	config[1].push_back(true); config[1].push_back(false); config[1].push_back(false);
	config[2].push_back(true); config[2].push_back(true); config[2].push_back(false);
	a1 = new PecaTabuleiro(x, y, config);
	aux.push_back(a1);
	y -= 5;

	config.clear();
	for (int i = 0; i < 3; i++)
		config.push_back(vector<bool>());
	config[0].push_back(true); config[0].push_back(true); config[0].push_back(true);
	config[1].push_back(true); config[1].push_back(false); config[1].push_back(false);
	config[2].push_back(true); config[2].push_back(false); config[2].push_back(false);
	a1 = new PecaTabuleiro(x, y, config);
	aux.push_back(a1);

	x = 13; y = 4 * 5;
	pecas_por_jogar.push_back(aux);
	aux.clear();

	config.clear();
	for (int i = 0; i < 3; i++)
		config.push_back(vector<bool>());
	config[0].push_back(true); config[0].push_back(true); config[0].push_back(true);
	config[1].push_back(true); config[1].push_back(false); config[1].push_back(false);
	config[2].push_back(false); config[2].push_back(false); config[2].push_back(false);
	a1 = new PecaTabuleiro(x, y, config);
	aux.push_back(a1);
	y -= 5;

	config.clear();
	for (int i = 0; i < 3; i++)
		config.push_back(vector<bool>());
	config[0].push_back(true); config[0].push_back(true); config[0].push_back(true);
	config[1].push_back(false); config[1].push_back(false); config[1].push_back(true);
	config[2].push_back(false); config[2].push_back(false); config[2].push_back(false);
	a1 = new PecaTabuleiro(x, y, config);
	aux.push_back(a1);
	y -= 5;

	config.clear();
	for (int i = 0; i < 3; i++)
		config.push_back(vector<bool>());
	config[0].push_back(true); config[0].push_back(true); config[0].push_back(true);
	config[1].push_back(false); config[1].push_back(false); config[1].push_back(false);
	config[2].push_back(false); config[2].push_back(false); config[2].push_back(false);
	a1 = new PecaTabuleiro(x, y, config);
	aux.push_back(a1);
	y -= 5;

	config.clear();
	for (int i = 0; i < 3; i++)
		config.push_back(vector<bool>());
	config[0].push_back(true); config[0].push_back(true); config[0].push_back(false);
	config[1].push_back(true); config[1].push_back(false); config[1].push_back(false);
	config[2].push_back(false); config[2].push_back(false); config[2].push_back(false);
	a1 = new PecaTabuleiro(x, y, config);
	aux.push_back(a1);

	x = 17; y = 4 * 5;
	pecas_por_jogar.push_back(aux);
	aux.clear();

	config.clear();
	for (int i = 0; i < 3; i++)
		config.push_back(vector<bool>());
	config[0].push_back(false); config[0].push_back(true); config[0].push_back(true);
	config[1].push_back(false); config[1].push_back(false); config[1].push_back(false);
	config[2].push_back(false); config[2].push_back(false); config[2].push_back(false);
	a1 = new PecaTabuleiro(x, y, config);
	aux.push_back(a1);
	y -= 5;

	config.clear();
	for (int i = 0; i < 3; i++)
		config.push_back(vector<bool>());
	config[0].push_back(true); config[0].push_back(true); config[0].push_back(false);
	config[1].push_back(false); config[1].push_back(false); config[1].push_back(false);
	config[2].push_back(false); config[2].push_back(false); config[2].push_back(false);
	a1 = new PecaTabuleiro(x, y, config);
	aux.push_back(a1);
	y -= 5;

	config.clear();
	for (int i = 0; i < 3; i++)
		config.push_back(vector<bool>());
	config[0].push_back(true); config[0].push_back(false); config[0].push_back(false);
	config[1].push_back(false); config[1].push_back(false); config[1].push_back(false);
	config[2].push_back(false); config[2].push_back(false); config[2].push_back(false);
	a1 = new PecaTabuleiro(x, y, config);
	aux.push_back(a1);
	y -= 5;

	config.clear();
	for (int i = 0; i < 3; i++)
		config.push_back(vector<bool>());
	config[0].push_back(false); config[0].push_back(true); config[0].push_back(false);
	config[1].push_back(false); config[1].push_back(false); config[1].push_back(false);
	config[2].push_back(false); config[2].push_back(false); config[2].push_back(false);
	a1 = new PecaTabuleiro(x, y, config);
	aux.push_back(a1);

	pecas_por_jogar.push_back(aux);
}

void Tabuleiro::addClique(int clique) {
	cliques.push_back(clique);
}

void Tabuleiro::atualizarPecas() {
	int movimentos = cliques.size() / 4;

	for (int i = 0; i < movimentos; i++) {
		PecaTabuleiro* pecaAMover = getPecaFromCoords(cliques[i * 4 + 0], cliques[i * 4 + 1]);
		PecaTabuleiro* pecaDestino = getPecaFromCoords(cliques[i * 4 + 2], cliques[i * 4 + 3]);

		if (cliques[i * 4 + 0] >= 100 && cliques[i * 4 + 2] < 100 && (pecaAMover->getAnimada() || (!pecaAMover->getFixa() && !pecaDestino->getFixa()))) {
			pecaAMover->setAnimada();
			pecaAMover->setFixa();
			pecaDestino->setFixa();

			if (pecaAMover->getX() > pecaDestino->getX())
				pecaAMover->getX() - pecaDestino->getX() >= .4 ? pecaAMover->setX(pecaAMover->getX() - .4) : pecaAMover->setX(pecaAMover->getX() - (pecaAMover->getX() - pecaDestino->getX()));
			else if (pecaAMover->getX() < pecaDestino->getX())
				pecaDestino->getX() - pecaAMover->getX() >= .4 ? pecaAMover->setX(pecaAMover->getX() + .4) : pecaAMover->setX(pecaAMover->getX() + (pecaDestino->getX() - pecaAMover->getX()));
			else if (pecaAMover->getY() > pecaDestino->getY())
				pecaAMover->getY() - pecaDestino->getY() >= .4 ? pecaAMover->setY(pecaAMover->getY() - .4) : pecaAMover->setY(pecaAMover->getY() - (pecaAMover->getY() - pecaDestino->getY()));
			else if (pecaAMover->getY() < pecaDestino->getY())
				pecaDestino->getY() - pecaAMover->getY() >= .4 ? pecaAMover->setY(pecaAMover->getY() + .4) : pecaAMover->setY(pecaAMover->getY() + (pecaDestino->getY() - pecaAMover->getY()));
			else {
				jogador = !jogador;
				tabuleiro[cliques[i * 4 + 2]][cliques[i * 4 + 3]] = pecaDestino;
				*pecaDestino = *pecaAMover;

				vector<int> aux1(cliques.begin(), cliques.begin() + i * 4), aux2(cliques.begin() + i * 4 + 3 + 1, cliques.end());
				aux1.insert(aux1.end(), aux2.begin(), aux2.end());
				aux1.swap(cliques);
				--movimentos;
			}
		}
		else {
			vector<int> aux1(cliques.begin(), cliques.begin() + i * 4), aux2(cliques.begin() + i * 4 + 3 + 1, cliques.end());
			aux1.insert(aux1.end(), aux2.begin(), aux2.end());
			aux1.swap(cliques);
			--movimentos;
		}
	}
}
