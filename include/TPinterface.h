#ifndef TPinterface_H
#define TPinterface_H

#include "CGFinterface.h"

class TPinterface : public CGFinterface {
public:
	TPinterface();

	virtual void initGUI();
	virtual void processGUI(GLUI_Control *ctrl);

	virtual void processKeyboard(unsigned char key, int x, int y);
	virtual void processMouse(int button, int state, int x, int y);
	void performPicking(int x, int y);
	void processHits(GLint hits, GLuint buffer []);

private:
	int drawingMode;
	int cameraMode;
	int texMode;
	int difMode;
	int gameMode;
	int undoMode;
	int reviveMode;

	string textura;
	string dificuldadePretendida;
	string gameType;
};

#endif
