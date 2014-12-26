#include "XMLScene.h"
#include "Globals.h"

void XMLScene::parserGlobals() {
	if (globElement == NULL)
		printf("globals block not found!\n");
	else {
		cout << "\n----------------------- \n" << " Processing Globals \n" << "-----------------------" << endl;

		parserGlobalsDrawing();
		parserGlobalsCulling();
		parserGlobalsLighting();
	}
}

void XMLScene::parserGlobalsDrawing() {
	TiXmlElement* drawingElement = globElement->FirstChildElement("drawing");

	if (drawingElement) {
		char *mode = NULL, *shading = NULL, *bkgValues = NULL;
		float r, g, b, a;

		mode = (char *)drawingElement->Attribute("mode");
		shading = (char *)drawingElement->Attribute("shading");
		bkgValues = (char *)drawingElement->Attribute("background");

		if (mode != NULL && shading != NULL && bkgValues != NULL && sscanf(bkgValues, "%f %f %f %f", &r, &g, &b, &a) == 4){
			cout << "Shading and mode checked!" << endl;
			if (!strcmp(mode, "fill"))
				objetosDaCena.getGlobalsData()->polygonMode = GL_FILL;
			else if (!strcmp(mode, "line"))
				objetosDaCena.getGlobalsData()->polygonMode = GL_LINE;
			else if (!strcmp(mode, "point"))
				objetosDaCena.getGlobalsData()->polygonMode = GL_POINT;

			if (!strcmp(shading, "gouraud"))
				objetosDaCena.getGlobalsData()->shadeModel = GL_SMOOTH;
			else if (!strcmp(shading, "flat"))
				objetosDaCena.getGlobalsData()->shadeModel = GL_FLAT;
			
			objetosDaCena.getGlobalsData()->bkgColorR = r;
			objetosDaCena.getGlobalsData()->bkgColorG = g;
			objetosDaCena.getGlobalsData()->bkgColorB = b;
			objetosDaCena.getGlobalsData()->bkgColorA = a;

			cout << "Background colors checked!" << endl;
		}
		else
			printf("Error parsing drawing\n");
	}
	else
		printf("drawing not found\n");
}

void XMLScene::parserGlobalsCulling() {
	TiXmlElement* cullingElement = globElement->FirstChildElement("culling");

	if (cullingElement) {
		char *face = NULL, *order = NULL;

		face = (char *)cullingElement->Attribute("face");
		order = (char *)cullingElement->Attribute("order");

		if (face != NULL && order != NULL) {
			cout << "Culling checked!" << endl;

			if (!strcmp(face, "none"))
				objetosDaCena.getGlobalsData()->cullFace = NULL;
			else if (!strcmp(face, "back"))
				objetosDaCena.getGlobalsData()->cullFace = GL_BACK;
			else if (!strcmp(face, "front"))
				objetosDaCena.getGlobalsData()->cullFace = GL_FRONT;
			else if (!strcmp(face, "both"))
				objetosDaCena.getGlobalsData()->cullFace = GL_FRONT_AND_BACK;

			if (!strcmp(order, "ccw"))
				objetosDaCena.getGlobalsData()->frontFace = GL_CCW;
			else if (!strcmp(order, "cw"))
				objetosDaCena.getGlobalsData()->frontFace = GL_CW;
		}
		else
			printf("Error parsing culling\n");
	}
	else
		printf("culling not found\n");
}

void XMLScene::parserGlobalsLighting() {
	TiXmlElement* lightingElement = globElement->FirstChildElement("lighting");

	if (lightingElement) {
		char *doubleSided = NULL, *local = NULL, *enabled = NULL, *ambient = NULL;
		float r, g, b, a;

		doubleSided = (char *)lightingElement->Attribute("doublesided");
		local = (char *)lightingElement->Attribute("local");
		enabled = (char *)lightingElement->Attribute("enabled");
		ambient = (char *)lightingElement->Attribute("ambient");

		if (doubleSided != NULL && local != NULL && enabled != NULL && ambient != NULL && sscanf(ambient, "%f %f %f %f", &r, &g, &b, &a) == 4) {
			cout << "Lighting checked!" << endl;
			
			if (!strcmp(doubleSided, "true"))
				objetosDaCena.getGlobalsData()->dblSidedLight = true;
			else if (!strcmp(doubleSided, "false"))
				objetosDaCena.getGlobalsData()->dblSidedLight = false;

			if (!strcmp(local, "true"))
				objetosDaCena.getGlobalsData()->localLight = true;
			else if (!strcmp(local, "false"))
				objetosDaCena.getGlobalsData()->localLight = false;

			if (!strcmp(enabled, "true"))
				objetosDaCena.getGlobalsData()->lightEnabled = true;
			else if (!strcmp(enabled, "false"))
				objetosDaCena.getGlobalsData()->lightEnabled = false;

			cout << "Background values checked!\n" << endl;

			float ambLight[4] = { r, g, b, a };
			memcpy(CGFlight::background_ambient, ambLight, sizeof(ambLight));
		}
		else
			printf("Error parsing lighting\n");
	}
	else
		printf("lighting not found\n");
}
