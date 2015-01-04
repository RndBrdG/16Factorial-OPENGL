#include "CGFapplication.h"
#include <sstream>
#include <time.h>
#include "Tabuleiro.h"

Tabuleiro::Tabuleiro() : cliques(vector<int>()), placar(0, 12, 0, 6), pecaRodar(0, 3, 0, 3), jogador(true), fimJogo(false), dificuldade("EASY"), tipoDeJogo("PVP"), tempoInicial(CGFapplication::getTime()), tempoInicialJogada(tempoInicial), minutosDecorridos(new int(0)), segundosDecorridos(new int(0)), tempoJogada(new int(30)), revive(false) {
	srand(time(NULL));
	PecaTabuleiro::addTextura("../res/wood.jpg");
	//PecaTabuleiro::addTextura("../res/stone.jpg");
	PecaTabuleiro::addTextura("../res/plastic.jpg");
	PecaTabuleiro::addTextura("../res/glass.jpg");
	PecaTabuleiro::setTextura(0);
	addTexturaPlacar("../res/placar_jog1.jpg");
	addTexturaPlacar("../res/placar_jog2.jpg");
	addTexturaPlacar("../res/placar_cpu.jpg");
	addTexturaPlacar("../res/placar_fim_jog1.jpg");
	addTexturaPlacar("../res/placar_fim_jog2.jpg");
	addTexturaPlacar("../res/placar_fim_cpu.jpg");
	if (!plogcon.socketConnect()) {
		cout << "Prolog server is required. Exiting" << endl;
		system("pause");
		exit(1);
	}

	resetTabuleiro();
}

Socket& Tabuleiro::getSocket() {
	return plogcon;
}

const vector<vector<PecaTabuleiro*>>& Tabuleiro::getTabuleiro() const {
	return this->tabuleiro;
}

const vector<vector<PecaTabuleiro*>>& Tabuleiro::getPecas() const {
	return this->pecas_por_jogar;
}

PecaTabuleiro* Tabuleiro::getPecaFromCoords(int i, int j) {
	if (i == 105) return NULL;
	else if (i >= 100) return pecas_por_jogar[i - 100][j];
	else return tabuleiro[i][j];
}

stack<Jogada> &Tabuleiro::getJogadas(){
	return this->jogadas;
}

const vector<int> Tabuleiro::getCliques(){
	return this->cliques;
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

int* Tabuleiro::getMinutosDecorridos() const {
	return minutosDecorridos;
}

int* Tabuleiro::getSegundosDecorridos() const {
	return segundosDecorridos;
}

int* Tabuleiro::getTempoJogada() const {
	return tempoJogada;
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
		for (int c = 0; c < 4; c++)
		{
			if (pecas_por_jogar[r][c]->getFixa() && !pecas_por_jogar[r][c]->getAnimada()) continue; // Nao desenhar as pecas laterais se ja tiverem sido colocadas
			glPushMatrix();
			glTranslatef(pecas_por_jogar[r][c]->getX(), pecas_por_jogar[r][c]->getY(), 0);
			glPushName(c);
			this->pecas_por_jogar[r][c]->draw();
			glPopName();
			glPopMatrix();
		}
		glPopMatrix();
	}

	CGFtexture texturaRodar("../res/rodar.jpg");
	glLoadName(105);
	glPushMatrix();
	glTranslatef(4.5, 0, 0);
	glPushName(0);
	pecaRodar.draw(3, 3);
	glPopName();
	glPopMatrix();
}

void Tabuleiro::drawPlacar() {
	CGFtexture* texturaPlacar;
	if (!fimJogo)
		texturaPlacar = texturasPlacar[jogador ? 0 : tipoDeJogo == "PVP" ? 1 : 2];
	else texturaPlacar = texturasPlacar[jogador ? 4 : tipoDeJogo == "PVP" ? 3 : 5];
	texturaPlacar->apply();

	glPushMatrix();
	glTranslatef(0, 4 * 4, 0);
	glPushName(104);
	placar.draw(12, 6);
	glPopName();
	glPopMatrix();
}

void Tabuleiro::resetTabuleiro(){
	fimJogo = false;
	float x = 0, y = 4 * 3;

	// Clear all the board
	tabuleiro.clear();
	pecas_por_jogar.clear();

	// Insert pieces.
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

void Tabuleiro::addTexturaPlacar(string textura) {
	texturasPlacar.push_back(new CGFtexture(textura));
}

void Tabuleiro::addClique(int clique) {
	if (clique == 104) {
		if (fimJogo) {
			setJogador(true);
			clearJogadas();
			resetTabuleiro();
		}
	}
	else cliques.push_back(clique);
}

void Tabuleiro::atualizarPecas() {
	int tempoDecorrido = (CGFapplication::getTime() - tempoInicial) / 1000; // Atualizar o tempo decorrido
	*minutosDecorridos = tempoDecorrido / 60;
	*segundosDecorridos = tempoDecorrido % 60;

	int movimentos = cliques.size() / 4;

	if (movimentos == 0 && static_cast<int>(CGFapplication::getTime() - tempoInicialJogada) / 1000 >= *tempoJogada) {
		jogador = !jogador;
		tempoInicialJogada = CGFapplication::getTime();
	}

	for (int i = 0; i < movimentos; i++) {
		PecaTabuleiro* pecaAMover = getPecaFromCoords(cliques[i * 4 + 0], cliques[i * 4 + 1]);
		PecaTabuleiro* pecaDestino = getPecaFromCoords(cliques[i * 4 + 2], cliques[i * 4 + 3]);

		if (cliques[i * 4 + 0] >= 100 && cliques[i * 4 + 0] <= 103 && cliques[i * 4 + 2] == 105)
			pecaAMover->rodar();

		if (cliques[i * 4 + 0] >= 100 && cliques[i * 4 + 0] != 105 && cliques[i * 4 + 2] < 100 && (pecaAMover->getAnimada() || (!pecaAMover->getFixa() && !pecaDestino->getFixa()))) {
			pecaAMover->setAnimada(true);
			pecaAMover->setFixa();
			pecaDestino->setFixa();

			if (pecaAMover->getX() > pecaDestino->getX())
				pecaAMover->getX() - pecaDestino->getX() >= VELOCIDADE ? pecaAMover->setX(pecaAMover->getX() - VELOCIDADE) : pecaAMover->setX(pecaAMover->getX() - (pecaAMover->getX() - pecaDestino->getX()));
			else if (pecaAMover->getX() < pecaDestino->getX())
				pecaDestino->getX() - pecaAMover->getX() >= VELOCIDADE ? pecaAMover->setX(pecaAMover->getX() + VELOCIDADE) : pecaAMover->setX(pecaAMover->getX() + (pecaDestino->getX() - pecaAMover->getX()));
			else if (pecaAMover->getY() > pecaDestino->getY())
				pecaAMover->getY() - pecaDestino->getY() >= VELOCIDADE ? pecaAMover->setY(pecaAMover->getY() - VELOCIDADE) : pecaAMover->setY(pecaAMover->getY() - (pecaAMover->getY() - pecaDestino->getY()));
			else if (pecaAMover->getY() < pecaDestino->getY())
				pecaDestino->getY() - pecaAMover->getY() >= VELOCIDADE ? pecaAMover->setY(pecaAMover->getY() + VELOCIDADE) : pecaAMover->setY(pecaAMover->getY() + (pecaDestino->getY() - pecaAMover->getY()));
			else {
				stringstream ss;
				string temp;
				char ans[128];
				bool jogadaValida = true;
				if (!this->revive) {
					ss << "verificarJogadaValida(" << toString() << "," << cliques[i * 4 + 2] << "," << cliques[i * 4 + 3] << "," << pecaAMover->toString() << ").\n";

					plogcon.envia(const_cast<char*>(ss.str().c_str()), strlen(ss.str().c_str()));
					plogcon.recebe(ans);

					jogador = !jogador;
					tempoInicialJogada = CGFapplication::getTime();
					pecaAMover->setAnimada(false);
					tabuleiro[cliques[i * 4 + 2]][cliques[i * 4 + 3]] = pecaDestino;
					*pecaDestino = *pecaAMover;
				}
				cout << "Peca escolhida: " << (cliques[i * 4 + 0] - 100) * 4 + cliques[i * 4 + 1] << endl;

				if (!this->revive) {
					Jogada a1;
					a1.cliques = vector<int>();
					a1.cliques.push_back(cliques[i * 4 + 0]);
					a1.cliques.push_back(cliques[i * 4 + 1]);
					a1.cliques.push_back(cliques[i * 4 + 2]);
					a1.cliques.push_back(cliques[i * 4 + 3]);
					this->jogadas.push(a1);
				}
				else {
					cout << "Ok" << endl;
				}

				if (!this->revive) {
					temp = string(ans);

					if (temp[0] == '2'){
						undo();
						jogadaValida = false;
					}

					ans[0] = '\0';

					int aux = 0;
					string temp1 = "[";
					for (int i = 0; i < 4; i++){
						for (int j = 0; j < 4; j++){
							if (!pecas_por_jogar[i][j]->getFixa() && !pecas_por_jogar[i][j]->getAnimada()){
								if (aux != 0){
									temp1.append(",");
								}
								temp1.append(pecas_por_jogar[i][j]->toString());
								aux++;
							}
						}
					}
					temp1.append("]");

					ss.str(string());

					ss << "verificarFimJogo(" << toString() << "," << temp1 << ").\n";

					plogcon.envia(const_cast<char*>(ss.str().c_str()), strlen(ss.str().c_str()));
					plogcon.recebe(ans);

					ss.str(string());
					temp = string(ans);
					ans[0] = '\0';

					if (temp[0] == '1')
						fimJogo = true;
					else if (!this->jogador && this->tipoDeJogo == "PVC" && !this->revive){
						while (true){
							int linha = rand() % 4;
							int coluna = rand() % 4;
							int padraoColuna = rand() % 4;
							int padraoLinha = rand() % 4;
							cout << "Linha: " << linha << "Coluna:" << coluna << "padraoColuna: " << padraoColuna << "padraoLinha:" << padraoLinha << endl;
							if (!pecas_por_jogar[padraoLinha][padraoColuna]->getFixa() && !pecas_por_jogar[padraoLinha][padraoColuna]->getAnimada()){
								ss << "verificarJogadaValida(" << toString() << "," << linha << "," << coluna << "," << pecas_por_jogar[padraoLinha][padraoColuna]->toString() << ").\n";
								plogcon.envia(const_cast<char*>(ss.str().c_str()), strlen(ss.str().c_str()));
								plogcon.recebe(ans);
								temp = string(ans);
								if (temp[0] != '2'){
									Jogada a1;
									a1.cliques = vector<int>();
									a1.cliques.push_back(padraoLinha+100);
									a1.cliques.push_back(padraoColuna);
									a1.cliques.push_back(linha);
									a1.cliques.push_back(coluna);
									this->jogadas.push(a1);
									pecaAMover = getPecaFromCoords(padraoLinha + 100, padraoColuna);
									pecaAMover->setAnimada(false);
									pecaDestino = getPecaFromCoords(linha, coluna);
									pecaDestino->setAnimada(false);
									float x = pecaDestino->getX(), y = pecaDestino->getY();
									*pecaDestino = *pecaAMover;
									pecaDestino->setX(x); pecaDestino->setY(y);
									pecaDestino->setFixa();
									pecaAMover->setFixa();
									cout << tabuleiro[linha][coluna]->toString() << endl;
									jogador = !jogador;
									break;
								}
								ans[0] = '\0';
								ss.str(string());
								cout <<"----"<<  ans << endl;
							}
						}
					}
				}

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

void Tabuleiro::undo(){
	cout << "UNDO: " << jogadas.size() << endl;
	if (!jogadas.empty()){
		vector<int> coords = jogadas.top().cliques;
		cout << "[" << coords[0] << "," << coords[1] << "] -> [" << coords[2] << ", " << coords[3] << "]" << endl;
		PecaTabuleiro* pecaDefault = new PecaTabuleiro(getPecaFromCoords(coords[2], coords[3])->getX(), getPecaFromCoords(coords[2], coords[3])->getY());

		// NOVA PECA
		PecaTabuleiro* pecaAMover = new PecaTabuleiro(getPecaFromCoords(coords[2], coords[3])->getX(), getPecaFromCoords(coords[2], coords[3])->getY(), getPecaFromCoords(coords[2], coords[3])->getEstrutura());
		pecaAMover->setX(getPecaFromCoords(coords[2], coords[3])->getXinicial());
		pecaAMover->setY(getPecaFromCoords(coords[2], coords[3])->getYinicial());

		// GUARDAR PEÇA
		pecas_por_jogar[coords[0] - 100][coords[1]] = pecaAMover;
		tabuleiro[coords[2]][coords[3]] = pecaDefault;
		jogadas.pop();
		jogador = !jogador;
		tempoInicialJogada = CGFapplication::getTime();
	}
}

void Tabuleiro::setRevive() {
	this->revive = !revive;
}

bool Tabuleiro::getRevive() const {
	return this->revive;
}

void Tabuleiro::clearCliques() {
	this->cliques.clear();
}

void Tabuleiro::clearJogadas() {
	while (!jogadas.empty())
		jogadas.pop();
}

string Tabuleiro::toString(){
	string tab = "[";

	for (size_t i = 0; i < 4; i++){
		tab.append("[");

		for (size_t j = 0; j < 4; j++){
			tab.append(tabuleiro[i][j]->toString());
			if (j != 3) tab.append(", ");
		}
		tab.append("]\n");
		if (i != 3) tab.append(", ");
	}
	tab.append("]");

	return tab;
}

void Tabuleiro::setJogador(bool value){
	this->jogador = value;
}
