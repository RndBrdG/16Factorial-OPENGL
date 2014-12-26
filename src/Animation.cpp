#include "Animation.h"
#include "Primitiva.h"
#include "CGFapplication.h"

Ponto::Ponto(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z; 
}

bool Ponto::operator >=(const Ponto &b) const{
	if (this->x >= b.x && this->y >= b.y && this->z >= b.z) return true;
	else return false;
}

bool Ponto::isGreater(const Ponto &b) const{
	return *this >= b;
}

Animation::Animation(string id, float span, const vector<Ponto*> pontosDeControlo){
	this->id = id;
	this->span = span;
	this->pontosDeControlo = pontosDeControlo;
	this->firstTime = true;
}

Animation::Animation(string id, float span){
	this->id = id;
	this->span = span;
}

unsigned int Animation::calculateDistance(Ponto* partida, Ponto* chegada){
	return sqrt((partida->x - chegada->x)*(partida->x - chegada->x) + (partida->y - chegada->y)*(partida->y - chegada->y) + (partida->z - chegada->z)*(partida->z - chegada->z));
}

LinearAnimation::LinearAnimation(string id, float span, const vector<Ponto*> pontosDeControlo) : Animation(id, span, pontosDeControlo){
	this->doReset = true;
	this->indicePontoControlo = 0;
	this->PontoActual = new Ponto(this->pontosDeControlo[0]->x, this->pontosDeControlo[0]->y, this->pontosDeControlo[0]->z);
	for (int i = 0; i < pontosDeControlo.size() - 1; i++){
		this->distancias.push_back(this->calculateDistance(pontosDeControlo[i], pontosDeControlo[i + 1]));
	}
	this->speed = 0.030* this->distancias[0] / (this->span / this->pontosDeControlo.size());
}

void LinearAnimation::init(unsigned long t){
	this->doReset = false;
	this->indicePontoControlo = 0;
	this->PontoActual->x = this->pontosDeControlo[0]->x;
	this->PontoActual->y = this->pontosDeControlo[0]->y;
	this->PontoActual->z = this->pontosDeControlo[0]->z;
	this->speed = (t - this->initialStart) * 0.001 * this->distancias[0] / (this->span / this->pontosDeControlo.size());
	if (firstTime) {
		this->initialStart = CGFapplication::getTime();
		firstTime = false;
	}
	else this->initialStart = t;
}
void LinearAnimation::reset(){
	this->doReset = true;
}
void LinearAnimation::update(unsigned long t){
	if (doReset){
		init(t);
	}
	else {
		if (this->indicePontoControlo + 1 < this->pontosDeControlo.size()){
			if (this->PontoActual->isGreater(*this->pontosDeControlo[this->indicePontoControlo + 1])){
				this->indicePontoControlo += 1;
				this->speed = (t - this->initialStart) * 0.001 * this->distancias[this->indicePontoControlo - 1] / (this->span / this->pontosDeControlo.size());
				
			}
			if (this->indicePontoControlo + 1 < this->pontosDeControlo.size()){
				if (this->pontosDeControlo[this->indicePontoControlo]->x != this->pontosDeControlo[this->indicePontoControlo + 1]->x)
					this->PontoActual->x += this->speed;
				else if (this->pontosDeControlo[this->indicePontoControlo]->y != this->pontosDeControlo[this->indicePontoControlo + 1]->y)
					this->PontoActual->y += this->speed;
				else this->PontoActual->z += this->speed;
			}
			else this->reset();
		}
		else this->reset();
	}
		this->initialStart = t;
}

void LinearAnimation::draw(){
	glTranslatef(this->PontoActual->x, this->PontoActual->y, this->PontoActual->z);
}

CircularAnimation::CircularAnimation(string id, float span, Ponto* ponto, float radius, float start_ang, float rot_ang): Animation(id, span){
	this->center = new Ponto(-1, -1, -1);
	this->center->x = ponto->x;
	this->center->y = ponto->y;
	this->center->z = ponto->z;
	this->start_ang = start_ang;
	this->rot_ang = rot_ang;
	this->radius = radius;
	this->obj_rotate = START_ANGLE;
	this->obj_radius = START_RADIUS;
	this->doReset = true;
}

void CircularAnimation::init(unsigned long t){
	this->obj_rotate = START_ANGLE;
	this->obj_radius = START_RADIUS;
	doReset = false;
	if (firstTime) {
		this->initialStart = CGFapplication::getTime();
		firstTime = false;
	}
	else this->initialStart = t;
}

void CircularAnimation::update(unsigned long t)
{
	if (doReset){
		init(t);
	}
	else
	{
		if ( (t - this->initialStart)*0.001 > this->span) 
			this->reset();
		else {
			obj_rotate += (t - this->initialStart)*0.001 * this->rot_ang / this->span;
			obj_radius += this->radius;
		}
		this->initialStart = t;
	}
}

void CircularAnimation::reset(){
	this->obj_rotate = START_ANGLE;
	this->obj_radius = START_RADIUS;
	doReset = true;
}

void CircularAnimation::draw()
{
	glTranslatef(this->obj_radius, 0, 0);
	glRotatef(this->obj_rotate, 0, 1, 0);
	glTranslatef(center->x, center->y, center->z);
}