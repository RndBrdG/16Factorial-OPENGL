#include "XMLScene.h"

XMLScene::XMLScene(char *filename)
{
	/* Inicializar grafo */
	objetosDaCena = Graph();

	// Read XML from file

	doc = new TiXmlDocument(filename);
	bool loadOkay = doc->LoadFile();

	if (!loadOkay)
	{
		printf("Could not load file '%s'. Error='%s'. Exiting.\n", filename, doc->ErrorDesc());
		system("pause");
		exit(1);
	}

	TiXmlElement* dgxElement = doc->FirstChildElement("anf");

	if (dgxElement == NULL)
	{
		printf("Main anf block element not found! Exiting!\n");
		system("pause");
		exit(1);
	}

	globElement = dgxElement->FirstChildElement("globals");
	camElement = dgxElement->FirstChildElement("cameras");
	lightsElement = dgxElement->FirstChildElement("lights");
	texElement = dgxElement->FirstChildElement("textures");
	appsElement = dgxElement->FirstChildElement("appearances");
	AnimElement = dgxElement->FirstChildElement("animations");
	graphElement = dgxElement->FirstChildElement("graph");

	parserGlobals();
	parserCameras();
	parserAppearance();
	parserTextures();
	parserAnimations();
	parserLights();
	parserGraph();

	cout << "--------------------------------------" << endl;
	cout << "It went all good! You're good to go :)" << endl;
	cout << "--------------------------------------" << endl;
}

XMLScene::~XMLScene()
{
	delete(&objetosDaCena);
	delete(doc);
	delete(globElement);
	delete(camElement);
	delete(lightsElement);
	delete(texElement);
	delete(appsElement);
	delete(graphElement);
}

//-------------------------------------------------------

TiXmlElement *XMLScene::findChildByAttribute(TiXmlElement *parent, const char * attr, const char *val)
// Searches within descendants of a parent for a node that has an attribute _attr_ (e.g. an id) with the value _val_
// A more elaborate version of this would rely on XPath expressions
{
	TiXmlElement *child = parent->FirstChildElement();
	int found = 0;

	while (child && !found)
		if (child->Attribute(attr) && strcmp(child->Attribute(attr), val) == 0)
			found = 1;
		else
			child = child->NextSiblingElement();

	return child;
}
