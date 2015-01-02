#include "CGFappearance.h"
#include "CGFapplication.h"
#include "CGFaxis.h"
#include "DemoScene.h"
#include "Primitiva.h"
#include "TPinterface.h"
#include <cmath>

DemoScene::DemoScene(char* filename) : parser(XMLScene(filename)) {
	ultimaAtualizacao = CGFapplication::getTime();
	this->tabuleiro = Tabuleiro();
}

const Graph& DemoScene::getElementos() {
	return elementos;
}

Tabuleiro& DemoScene::getTabuleiro() {
	return tabuleiro;
}

void DemoScene::activateCamera(int id){
	elementos.setDefaultCamera(camaras[id]->getId());

	if (id == 0)
		tabuleiro.setRotateAngle(90);
	else tabuleiro.setRotateAngle(0);
}

vector<Camera*>& DemoScene::getCamaras() {
	return camaras;
}

void DemoScene::init() {
	elementos = parser.objetosDaCena;

	// Sets drawing settings
	glShadeModel(elementos.getGlobalsData()->getShadeModel());
	glClearColor(elementos.getGlobalsData()->getBkgColorR(), elementos.getGlobalsData()->getBkgColorG(), elementos.getGlobalsData()->getBkgColorB(), elementos.getGlobalsData()->getBkgColorA());

	// Sets culling settings
	if (elementos.getGlobalsData()->getCullFace() != NULL) {
		glCullFace(elementos.getGlobalsData()->getCullFace());
		glFrontFace(elementos.getGlobalsData()->getFrontFace());
	}
	else glDisable(GL_CULL_FACE);

	// Sets lighting settings
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, elementos.getGlobalsData()->getDblSidedLight());
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, elementos.getGlobalsData()->getLocalLight());
	if (elementos.getGlobalsData()->getLightEnabled()) glEnable(GL_LIGHTING); else glDisable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, CGFlight::background_ambient);

	// Sets lights
	for (auto it = elementos.getLuzes().cbegin(); it != elementos.getLuzes().cend(); it++) {
		glLightf(GL_LIGHT0 + it->second->getLightNum(), GL_SPOT_CUTOFF, it->second->getAngle());
		glLightf(GL_LIGHT0 + it->second->getLightNum(), GL_SPOT_EXPONENT, it->second->getExponent());
		if (it->second->getEnabled()) glEnable(GL_LIGHT0 + it->second->getLightNum());
		else glDisable(GL_LIGHT0 + it->second->getLightNum());
	}

	// Defines a default normal
	glNormal3f(0, 0, 1);

	for (auto it = elementos.getCamaras().begin(); it != elementos.getCamaras().end(); it++){
		camaras.push_back(it->second);
	}

	setUpdatePeriod(30);
}

void DemoScene::update(unsigned long t) {
	for (map<string, Animation*>::iterator it = this->elementos.getAnimations().begin(); it != this->elementos.getAnimations().end(); it++){
		it->second->update(t);
	}

	if (!tabuleiro.getRevive())
		tabuleiro.atualizarPecas();
	//cout << "UPDATE 2: " << tabuleiro.getJogadas().size() << endl;
}

void DemoScene::display() {
	// ---- BEGIN Background, camera and axis setup

	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformations)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int id = 0;
	for (unsigned int i = 0; i < camaras.size(); i++) {
		if (camaras[i]->getId() == elementos.getCameraDefault()) {
			id = i;
			CGFscene::activeCamera = camaras[i];
			break;
		}
	}

	// Trocar comentários das 2 linhas seguintes para aceder às câmaras da cena vs. câmara predefinida
	//activateCamera(id);
	CGFscene::activeCamera->applyView();

	// Draw (and update) lights
	for (auto it = elementos.getLuzes().cbegin(); it != elementos.getLuzes().cend(); it++) {

		if (it->second->onOff) it->second->enable();
		else it->second->disable();

		if (it->second->onOff && it->second->getMarker()) it->second->draw();
		else it->second->update();
	}

	glPushMatrix();

	glPushMatrix();
	glTranslatef(0, 4 * 4, 0);
	tabuleiro.drawPlacar();
	glPopMatrix();
	if (!tabuleiro.getRevive()){
		tabuleiro.draw();
		tabuleiro.drawPecas();
	}
	else {
		stack<Jogada> jogadas;
		while (!tabuleiro.getJogadas().empty()) {
			jogadas.push(tabuleiro.getJogadas().top());
			tabuleiro.getJogadas().pop();
		}
		tabuleiro.resetTabuleiro();
		while (!jogadas.empty()) {
			Jogada jog = jogadas.top();
			tabuleiro.addClique(jog.cliques[0]);
			tabuleiro.addClique(jog.cliques[1]);
			tabuleiro.addClique(jog.cliques[2]);
			tabuleiro.addClique(jog.cliques[3]);
			tabuleiro.atualizarPecas();
			tabuleiro.draw();
			tabuleiro.drawPecas();
			jogadas.pop();
		}
		tabuleiro.setRevive();
	}
	glPopMatrix();
	// Draw axes
	//axis.draw();

	// ---- END Background, camera and axis setup

	// ---- BEGIN feature demos
	glPolygonMode(GL_FRONT_AND_BACK, elementos.getGlobalsData()->getPolygonMode()); // Sets (variable) drawing mode.
	//elementos.draw();
	//system("pause");
	// ---- END feature demos

	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
}

DemoScene::~DemoScene() {
	delete(&parser);
	delete(&elementos);
}
