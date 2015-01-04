#include <sstream>
#include "PecaTabuleiro.h"
#include "TPinterface.h"
#include "DemoScene.h"

#define BUFSIZE 256
GLuint selectBuf[BUFSIZE];

void TPinterface::processMouse(int button, int state, int x, int y)
{
	CGFinterface::processMouse(button, state, x, y);

	// do picking on mouse press (GLUT_DOWN)
	// this could be more elaborate, e.g. only performing picking when there is a click (DOWN followed by UP) on the same place
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		performPicking(x, y);
}

void TPinterface::performPicking(int x, int y)
{
	// Sets the buffer to be used for selection and activate selection mode
	glSelectBuffer(BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT);

	// Initialize the picking name stack
	glInitNames();

	// The process of picking manipulates the projection matrix
	// so we will be activating, saving and manipulating it
	glMatrixMode(GL_PROJECTION);

	//store current projmatrix to restore easily in the end with a pop
	glPushMatrix();

	//get the actual projection matrix values on an array of our own to multiply with pick matrix later
	GLfloat projmat[16];
	glGetFloatv(GL_PROJECTION_MATRIX, projmat);

	// reset projection matrix
	glLoadIdentity();

	// get current viewport and use it as reference for 
	// setting a small picking window of 5x5 pixels around mouse coordinates for picking
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// this is multiplied in the projection matrix
	gluPickMatrix((GLdouble)x, (GLdouble)(CGFapplication::height - y), 5.0, 5.0, viewport);

	// multiply the projection matrix stored in our array to ensure same conditions as in normal render
	glMultMatrixf(projmat);

	// force scene drawing under this mode
	// only the names of objects that fall in the 5x5 window will actually be stored in the buffer
	scene->display();

	// restore original projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glFlush();

	// revert to render mode, get the picking results and process them
	GLint hits;
	hits = glRenderMode(GL_RENDER);
	processHits(hits, selectBuf);
}

void TPinterface::processHits(GLint hits, GLuint buffer[])
{
	GLuint *ptr = buffer;
	GLuint mindepth = 0xFFFFFFFF;
	GLuint *selected = NULL;
	GLuint nselected;

	// iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
	for (int i = 0; i < hits; i++) {
		int num = *ptr; ptr++;
		GLuint z1 = *ptr; ptr++;
		ptr++;
		if (z1 < mindepth && num>0) {
			mindepth = z1;
			selected = ptr;
			nselected = num;
		}
		for (int j = 0; j < num; j++)
			ptr++;
	}

	// if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
	if (selected != NULL)
	{
		// this should be replaced by code handling the picked object's ID's (stored in "selected"), 
		// possibly invoking a method on the scene class and passing "selected" and "nselected"
		printf("Picked IDs: ");
		for (unsigned int i = 0; i < nselected; i++) {
			static_cast<DemoScene*>(scene)->getTabuleiro().addClique(selected[i]);
			printf("%d ", selected[i]);
		}
		printf("\n");
	}
	else
		printf("Nothing selected while picking.\n");
}

TPinterface::TPinterface() {
	drawingMode = 0;
	cameraMode = 10;
	texMode = 20;
	difMode = 30;
	gameMode = 40;
	undoMode = 50;
	reviveMode = 60;
	glutReshapeWindow(800, 800);
}

void TPinterface::processKeyboard(unsigned char key, int x, int y) {
	// Uncomment below if you would like to process the default keys (e.g. 's' for snapshot, 'Esc' for exiting, ...)
	CGFinterface::processKeyboard(key, x, y);

	switch (key)
	{
	case 'a':
	{
		// This is an example of accessing the associated scene
		// To test, create the function toggleSomething in your scene to activate/deactivate something
		//((DemoScene *)scene)->toggleSomething();
		break;
	}
	}
}

void TPinterface::initGUI() {
	/*
	// Check CGFinterface.h and GLUI documentation for the types of controls available
	GLUI_Panel *varPanel = addPanel("Group", 1);
	addSpinnerToPanel(varPanel, "Val 1(interface)", 2, &testVar, 1);

	// You could also pass a reference to a variable from the scene class, if public
	addSpinnerToPanel(varPanel, "Val 2(scene)", 2, &(((DemoScene*)scene)->sceneVar), 2);
	*/

	GLUI_Panel* panelCam = addPanel("Camaras");
	GLUI_RadioGroup* radioCam = addRadioGroupToPanel(panelCam, &cameraMode, 10);

	for (unsigned int i = 0; i < static_cast<DemoScene*>(scene)->getCamaras().size(); i++) {
		if (static_cast<DemoScene*>(scene)->elementos.getCameraDefault() == static_cast<DemoScene*>(scene)->getCamaras()[i]->getId())
			cameraMode = i;
		addRadioButtonToGroup(radioCam, static_cast<DemoScene*>(scene)->getCamaras()[i]->getId());
	}

	GLUI_Panel* panelTex = addPanel("Texturas");
	GLUI_RadioGroup* radioTextures = addRadioGroupToPanel(panelTex, &texMode, 20);
	for (auto it = static_cast<DemoScene*>(scene)->elementos.getTexturas().cbegin(); it != static_cast<DemoScene*>(scene)->elementos.getTexturas().cend(); it++) {
		stringstream textName;
		textName << it->first;
		addRadioButtonToGroup(radioTextures, const_cast<char*>(textName.str().c_str()));
	}
	texMode = 0;

	addColumn();

	GLUI_Panel* panelLuzes = addPanel("Luzes");
	for (auto it = static_cast<DemoScene*>(scene)->elementos.getLuzes().cbegin(); it != static_cast<DemoScene*>(scene)->elementos.getLuzes().cend(); it++) {
		int id = 2;
		stringstream lightName;
		lightName << it->first;
		addCheckboxToPanel(panelLuzes, const_cast<char*>(lightName.str().c_str()), &it->second->onOff, id++);
	}
	addSeparator();
	GLUI_Spinner* spinnerTempo = addSpinner("Segundos max. jogada", GLUI_SPINNER_INT, static_cast<DemoScene*>(scene)->getTabuleiro().getTempoJogada());
	spinnerTempo->set_int_limits(10, 120);
	GLUI_StaticText* textoTempoDecorrido = addStaticText("Tempo decorrido:");
	GLUI_EditText* textoMinutos = addEditText("Minutos", static_cast<int*>(static_cast<DemoScene*>(scene)->getTabuleiro().getMinutosDecorridos()));
	GLUI_EditText* textoSegundos = addEditText("Segundos", static_cast<int*>(static_cast<DemoScene*>(scene)->getTabuleiro().getSegundosDecorridos()));

	addColumn();

	GLUI_Listbox *listaTexturas = addListbox("Dificuldade", &difMode, 30);
	listaTexturas->add_item(31, "Easy");
	listaTexturas->add_item(32, "Medium");
	listaTexturas->add_item(33, "Hard");
	listaTexturas->set_int_val(31);
	addSeparator();
	GLUI_Listbox *tipoJogo = addListbox("Tipo de jogo", &gameMode, 40);
	tipoJogo->add_item(41, "PVP");
	tipoJogo->add_item(42, "PVC");
	tipoJogo->add_item(43, "CVC");
	tipoJogo->set_int_val(41);
	addSeparator();
	GLUI_Button* undo = addButton("Anular", undoMode);
	addSeparator();
	GLUI_Button* revive = addButton("Relembrar o jogo", reviveMode);
	addSeparator();
	GLUI_Button* close = addButton("Sair", 70);
}

void TPinterface::processGUI(GLUI_Control *ctrl) {
	printf("GUI control id: %d\n", ctrl->user_id);
	switch (ctrl->user_id) {
	case 1:
		static_cast<DemoScene*>(scene)->elementos.getGlobalsData()->setPolygonMode(drawingMode == 0 ? GL_FILL : drawingMode == 1 ? GL_LINE : GL_POINT);
		break;
	case 10:
		static_cast<DemoScene*>(scene)->activateCamera(cameraMode);
		break;
	case 20:
		cout << "Texture: " << texMode << endl;
		PecaTabuleiro::setTextura(texMode);
		break;
	case 30:
		difMode == 31 ? dificuldadePretendida = "EASY" : difMode == 32 ? dificuldadePretendida = "MEDIUM" : dificuldadePretendida = "HARD";
		if (dificuldadePretendida != static_cast<DemoScene*>(scene)->tabuleiro.getDificuldade() && static_cast<DemoScene*>(scene)->tabuleiro.getTipoDeJogo() == "PVP"){
			cout << "Alterada a dificuldade de jogada do computador." << endl;
			static_cast<DemoScene*>(scene)->tabuleiro.resetTabuleiro();
		}
		else cout << "A alteracao nao faz qualquer sentido." << endl;
		break;
	case 40:
		gameType = "";
		gameMode == 41 ? gameType = "PVP" : gameType = "PVC";

		if (gameType != static_cast<DemoScene*>(scene)->tabuleiro.getTipoDeJogo()){
			static_cast<DemoScene*>(scene)->tabuleiro.resetTabuleiro();
			static_cast<DemoScene*>(scene)->tabuleiro.setTipoDeJogo(gameType);
			static_cast<DemoScene*>(scene)->tabuleiro.clearJogadas();
			static_cast<DemoScene*>(scene)->tabuleiro.setJogador(true);
			cout << "Changing game mode done." << endl;
		}
		else cout << "No need to change the mode. Already on this one!" << endl;
		break;
	case 50:
		cout << "UNDO MODE" << endl;
		static_cast<DemoScene*>(scene)->tabuleiro.undo();
		break;
	case 60:
		cout << "REVIVE MODE ACTIVATED" << endl;
		if (!static_cast<DemoScene*>(scene)->tabuleiro.getJogadas().empty()){
			static_cast<DemoScene*>(scene)->tabuleiro.setRevive();
			static_cast<DemoScene*>(scene)->tabuleiro.resetTabuleiro();
			static_cast<DemoScene*>(scene)->tabuleiro.setJogador(true);
			static_cast<DemoScene*>(scene)->backup = static_cast<DemoScene*>(scene)->tabuleiro.getJogadas();
		}
		else cout << "You need to play atleast once." << endl;
		break;
	case 70:
		static_cast<DemoScene*>(scene)->tabuleiro.getSocket().quit();
		exit(0);
	}
}
