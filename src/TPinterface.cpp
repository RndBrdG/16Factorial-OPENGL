#include <sstream>
#include "TPinterface.h"
#include "DemoScene.h"

TPinterface::TPinterface() {
	drawingMode = 0;
	cameraMode = 10;
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

	addColumn();

	GLUI_Panel* panelDesenho = addPanel("Modo de desenho");
	GLUI_RadioGroup* radioDesenho = addRadioGroupToPanel(panelDesenho, &drawingMode, 1);
	addRadioButtonToGroup(radioDesenho, "Preencher");
	addRadioButtonToGroup(radioDesenho, "Linhas");
	addRadioButtonToGroup(radioDesenho, "Pontos");

	GLUI_Spinner* spinnerWind = addSpinner("Vento", 2, &static_cast<DemoScene*>(scene)->wind);

	addColumn();

	GLUI_Panel* panelLuzes = addPanel("Luzes");
	for (auto it = static_cast<DemoScene*>(scene)->elementos.getLuzes().cbegin(); it != static_cast<DemoScene*>(scene)->elementos.getLuzes().cend(); it++) {
		int id = 2;
		std::stringstream lightName;
		lightName << it->first;
		addCheckboxToPanel(panelLuzes, const_cast<char*>(lightName.str().c_str()), &it->second->onOff, id++);
	}
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
	}
}
