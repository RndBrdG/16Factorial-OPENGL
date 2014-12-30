#include <Graph.h>

bool Node::firstTime = true;
bool Node::controlList = false;

Textura::Textura(std::string id, std::string file, float texlength_s, float texlength_t){
	this->id = id;
	this->file = file;
	this->texlength_s = texlength_s;
	this->texlength_t = texlength_t;
}

Textura::~Textura(){
	delete(this);
}

string Textura::getId(){
	return this->id;
}

string Textura::getFile(){
	return this->file;
}

float Textura::getTexLenS(){
	return this->texlength_s;
}

float Textura::getTexLenT(){
	return this->texlength_t;
}

Aparencia::Aparencia(std::string id, float shininess, std::string textRef, float ambient[4], float difusa[4], float especular[4]) : CGFappearance(ambient, difusa, especular, shininess){
	this->id = id;
	this->shininess = shininess;
	this->textRef = textRef;
}

string Aparencia::getId(){
	return this->id;
}
string Aparencia::getTextRef(){
	return this->textRef;
}

Globals* Graph::getGlobalsData() {
	return globalsData;
}

map<std::string, Node*>& Graph::getGrafo(){
	return this->grafo;
}

map<std::string, Light*>& Graph::getLuzes() {
	return luzes;
}


Node::Node(std::string id){
	this->id = id;
	this->controlList = false;
}

Node::~Node(){
	delete(this);
}

string Node::getId(){
	return this->id;
}

string Node::getAppRef(){
	return this->appRef;
}

vector<string>& Node::getAnimations(){
	return this->animacoes;
}

vector<std::string>& Node::getDescendencia(){
	return this->descendencia;
}

vector<Primitiva*>& Node::getPrimitivas(){
	return primitivas;
}

bool Node::getRoot(){
	return this->root;
}

void Node::setMatrix(float matrix[16]){
	for (int i = 0; i < 16; i++)
		this->matrix[i] = matrix[i];
}

void Node::setId(std::string id){
	this->id = id;
}

void Node::setAppRef(std::string appRef){
	this->appRef = appRef;
}

void Node::setRoot(bool root){
	this->root = root;
}

bool Node::getDisplayList(){
	return this->displayList;
}

void Node::setDisplayList(bool displayList){
	this->displayList = displayList;
}

void Node::setIndex(GLuint index){
	this->index = index;
}

void Node::draw(map<string, Node*>& grafo, map<string, Aparencia*>& aparencias, string referenciaApp, map<string, Textura*>& texturas, map<string, Animation*> anime){

	if (this->firstTime){
		createDisplayList(grafo, aparencias, referenciaApp, texturas,anime);
		this->firstTime = false;
	}
	else if (this->displayList){
		glPushMatrix();
		glCallList(this->index);
		typedef vector<string>::iterator iter;
		for (iter it = this->getDescendencia().begin(); it != this->getDescendencia().end(); it++){
			glPushMatrix();
			grafo[*it]->draw(grafo, aparencias, this->appRef, texturas,anime);
			glPopMatrix();
		}
		glPopMatrix();
	}
	else if (!this->displayList && this->insideList && this->controlList){
		glPushMatrix();
		
		unsigned int size = this->primitivas.size();
		typedef vector<string>::iterator iter;
		for (iter it = this->getDescendencia().begin(); it != this->getDescendencia().end(); it++){
			glPushMatrix();
			grafo[*it]->draw(grafo, aparencias, this->appRef, texturas,anime);
			glPopMatrix();
		}
		glPopMatrix();
	}
	else {
		glPushMatrix();
		glMultMatrixf(&this->matrix[0]);
		if (this->appRef != "inherit"){
			aparencias[this->appRef]->apply();
		}
		else {
			aparencias[referenciaApp]->apply();
			this->appRef = referenciaApp;
		}

		if (this->animacoes.size() != 0){
			for (int i = 0; i < this->animacoes.size(); i++){ // alterar
				anime[animacoes[i]]->draw();
			}
		}

		unsigned int size = this->primitivas.size();
		for (unsigned int i = 0; i < size; i++){
			if (aparencias[appRef]->getTextRef() != "null"){
				float texS = texturas[aparencias[appRef]->getTextRef()]->getTexLenS();
				float texT = texturas[aparencias[appRef]->getTextRef()]->getTexLenT();
				primitivas[i]->draw(texS, texT);
			}
			else primitivas[i]->draw();
		}
		typedef std::vector<std::string>::iterator iter;
		for (iter it = this->getDescendencia().begin(); it != this->getDescendencia().end(); it++){
			glPushMatrix();
			grafo[*it]->draw(grafo, aparencias, this->appRef, texturas,anime);
			glPopMatrix();
		}
		glPopMatrix();
	}
}

string Graph::getRoot(){
	return this->root;
}

map<std::string, Aparencia*>& Graph::getAparencias(){
	return this->aparencias;
}

void Graph::setRoot(std::string root){
	this->root = root;
}

void Graph::draw(){

	Node *noActual = this->getGrafo()[this->getRoot()];

	noActual->draw(this->getGrafo(), this->getAparencias(), this->getGrafo()[this->getRoot()]->getAppRef(), this->texturas,this->animacoes);
}

map<std::string, Textura*>& Graph::getTexturas(){
	return this->texturas;
}

map < std::string, Camera*>& Graph::getCamaras(){
	return this->camaras;
}

map<string, Animation*>& Graph::getAnimations(){
	return this->animacoes;
}
void Graph::setDefaultCamera(std::string cameraDefault){
	this->cameraDefault = cameraDefault;
}

string Graph::getCameraDefault(){
	return this->cameraDefault;
}


void Node::createDisplayList(map<string, Node*>& grafo, map<string, Aparencia*>& aparencias, string referenciaApp, map<string, Textura*>& texturas,map<string, Animation*> anime){
	
	if (this->displayList){
		this->controlList = true;
		this->index = glGenLists(1);
		this->insideList = false;
		glNewList(this->index, GL_COMPILE);
		glPushMatrix();
		glMultMatrixf(&this->matrix[0]);

		if (this->appRef != "inherit"){
			aparencias[this->appRef]->apply();
		}
		else {
			aparencias[referenciaApp]->apply();
			this->appRef = referenciaApp;
		}
		unsigned int size = this->primitivas.size();
		for (unsigned int i = 0; i < size; i++){
			if (aparencias[appRef]->getTextRef() != "null"){
				float texS = texturas[aparencias[appRef]->getTextRef()]->getTexLenS();
				float texT = texturas[aparencias[appRef]->getTextRef()]->getTexLenT();
				primitivas[i]->draw(texS, texT);
			}
			else primitivas[i]->draw();
		}
		typedef vector<string>::iterator iter;
		for (iter it = this->getDescendencia().begin(); it != this->getDescendencia().end(); it++){
			glPushMatrix();
			grafo[*it]->createDisplayList(grafo, aparencias, this->appRef, texturas,anime);
			glPopMatrix();
		}
		glPopMatrix();
		glEndList();
	}
	else {
		glMultMatrixf(&this->matrix[0]);
		if (this->controlList) this->insideList = true; else this->insideList = false;
		if (this->appRef != "inherit"){
			aparencias[this->appRef]->apply();
		}
		else {
			aparencias[referenciaApp]->apply();
			this->appRef = referenciaApp;
		}
		unsigned int size = this->primitivas.size();
		for (unsigned int i = 0; i < size; i++){
			if (aparencias[appRef]->getTextRef() != "null"){
				float texS = texturas[aparencias[appRef]->getTextRef()]->getTexLenS();
				float texT = texturas[aparencias[appRef]->getTextRef()]->getTexLenT();
				primitivas[i]->draw(texS, texT);
			}
			else primitivas[i]->draw();
		}
		typedef std::vector<std::string>::iterator iter;
		for (iter it = this->getDescendencia().begin(); it != this->getDescendencia().end(); it++){
			glPushMatrix();
			grafo[*it]->createDisplayList(grafo, aparencias, this->appRef, texturas,anime);
			glPopMatrix();
		}
	}
}
