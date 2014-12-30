#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#include "tinyxml.h"
#include "Graph.h"

class XMLScene
{
public:
	XMLScene(char *filename);
	~XMLScene();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);

	Graph objetosDaCena;
private:
	// globals tag
	void parserGlobals();
	void parserGlobalsDrawing();
	void parserGlobalsCulling();
	void parserGlobalsLighting();
	// camera tag
	void parserCameras();
	// lights tag
	void parserLights();
	// Textures tags
	void parserTextures();
	// Appearances tag
	void parserAppearance();
	// Animations tag
	void parserAnimations();
	// graph tag
	void parserGraph();
	void parserGraphTransforms(Node* novoNode, TiXmlElement *childs);
	void parserGraphAppearanceref(Node* novoNode, TiXmlElement *childs);
	void parserGraphPrimitives(Node* novoNode, TiXmlElement *childs);
	void parserGraphdescendants(Node* novoNode, TiXmlElement *childs);
	void atualizarInserirNode(std::string id, Node* novoNode);
protected:
	TiXmlDocument* doc;
	TiXmlElement* globElement; 
	TiXmlElement* camElement;
	TiXmlElement* lightsElement;
	TiXmlElement* texElement;
	TiXmlElement* appsElement;
	TiXmlElement* AnimElement;
	TiXmlElement* graphElement;
};

#endif
