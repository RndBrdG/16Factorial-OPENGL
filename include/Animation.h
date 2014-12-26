#ifndef ANIMATION_H
#define ANIMATION_H

#define RADIUS_SPEED  0.5  // unidades de comprimento por segundo
#define ANGULAR_SPEED 0.5  // rotacoes por segundo
#define START_RADIUS  0.5  // raio inicial
#define START_ANGLE   0    // ângulo inicial

#include <string>
#include <vector>
#include <ctime>
#include <iostream>

using namespace std;

class Ponto {
public:
	float x, y, z;
	Ponto(float x, float y, float z);
	bool Ponto::operator >=(const Ponto &b) const;
	bool isGreater(const Ponto &b) const;
};


class Animation {
protected:
	string id;
	float span;
	vector<Ponto*> pontosDeControlo;
	vector<unsigned int> distancias;
	bool firstTime;
public:
	Animation(string id, float span);
	Animation(string id, float span, const vector<Ponto*> pontosDeControlo);
	unsigned int calculateDistance(Ponto* partida, Ponto* chegada);
	virtual void init(unsigned long t) = 0;
	virtual void reset() = 0;
	virtual void draw() = 0;
	virtual void update(unsigned long t) = 0;
};

class LinearAnimation :public Animation {
	unsigned int indicePontoControlo;
	float speed;
	unsigned long initialStart;
	bool doReset;
	Ponto* PontoActual;
public:
	LinearAnimation(string id, float span, const vector<Ponto*> pontosDeControlo);
	void init(unsigned long t);
	void reset();
	void update(unsigned long t);
	void draw();
};

class CircularAnimation : public Animation {
private:
	unsigned long initialStart;
	float  obj_radius, obj_rotate;
	float radius;
	float start_ang;
	float rot_ang;
	Ponto* center;
	bool doReset;
public:
	CircularAnimation(string id, float span, Ponto* ponto, float radius, float start_ang, float rot_ang);
	void init(unsigned long t);
	void reset();
	void update(unsigned long t);
	void draw();
};

#endif