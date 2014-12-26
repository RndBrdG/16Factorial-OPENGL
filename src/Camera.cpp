#include "Camera.h"

Camera::Camera(char *id, char *type, float near, float far, float angle, float tarX, float tarY, float tarZ, float posX, float posY, float posZ){
	this->id = id;
	this->type = type;
	this->direction = "null";
	this->near = near;
	this->far = far;
	this->angle = angle;
	this->tarX = tarX;
	this->tarY = tarY;
	this->tarZ = tarZ;
	this->posX = posX;
	this->posY = posY;
	this->posZ = posZ;

}

Camera::Camera(char *id, char *type, char* direction, float left, float right, float top, float bottom, float near, float far){
	this->id = id;
	this->type = type;
	this->direction = direction;
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
	this->near = near;
	this->far = far;
}


char* Camera::getId(){
	return id;
}

char* Camera::getType(){
	return type;
}

float Camera::getNear(){
	return near;
}

float Camera::getFar(){
	return far;
}

float Camera::getAngle(){
	return angle;
}

float Camera::getTarX(){
	return tarX;
}

float Camera::getTarY(){
	return tarY;
}

float Camera::getTarZ(){
	return tarZ;
}

float Camera::getPosX(){
	return this->posX;
}

float Camera::getPosY(){
	return this->posY;
}

float Camera::getPosZ(){
	return this->posZ;
}

char* Camera::getDirection(){
	return direction;
}

float Camera::getLeft(){
	return left;
}

float Camera::getRight(){
	return right;
}
float Camera::getBottom(){
	return bottom;
}
float Camera::getTop(){
	return top;
}
