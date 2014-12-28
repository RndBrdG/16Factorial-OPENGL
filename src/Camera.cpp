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

	this->position[0] = posX;
	this->position[1] = posY;
	this->position[2] = posZ;

	this->target[0] = tarX;
	this->target[1] = tarY;
	this->target[2] = tarZ;

	this->translate(2, far);
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

void Camera::updateProjectionMatrix(int width, int height){
	if (type == "ORTHO"){
		float aspect = (float) width / (float) height;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(left, right, bottom, top, near, far);
	}
	else{
		float aspect = (float) width / (float) height;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(angle, CGFapplication::xy_aspect, near, far);
	}
}

void Camera::applyView(){
	if (type == 0){
		if (direction == "x")
			gluLookAt(1, 0, 0, 0, 0, 0, 0, 1, 0);
		else if (direction == "y")
			gluLookAt(0, 1, 0, 0, 0, 0, 0, 0, -1);
		else
			gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
	}
	else{
		gluLookAt(position[0], position[1], position[2], target[0], target[1], target[2], 0, 1, 0);
	}
}
