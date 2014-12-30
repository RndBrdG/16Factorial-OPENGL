#include "Cylinder.h"
#include "Flag.h"
#include "Globals.h"
#include "Light.h"
#include "Patch.h"
#include "Plane.h"
#include "Rectangle.h"
#include "Sphere.h"
#include "Torus.h"
#include "Triangle.h"
#include "Vehicle.h"
#include "XMLScene.h"

void XMLScene::parserGraph(){

	if (graphElement == NULL)
		std::cout << "Graph block not found!\n";
	else
	{
		std::cout << "\n----------------------- \n" << " Processing nodes \n" << "-----------------------" << endl;
		std::string rootId = "";
		rootId = graphElement->Attribute("rootid");
		if (rootId != ""){
			TiXmlElement *node = graphElement->FirstChildElement();
			std::string id = "";

			while (node) {
				id = node->Attribute("id");
				Node* novoNode = new Node(id);
				if (id == rootId){
					novoNode->setRoot(true);
					this->objetosDaCena.setRoot(id);
				}
				else novoNode->setRoot(false);

				atualizarInserirNode(id, novoNode);

				char* displayL = NULL;
				displayL = (char*)node->Attribute("displayList");
				if (displayL != NULL && strcmp(displayL, "true") == 0){
					novoNode->setDisplayList(true);
				}
				else novoNode->setDisplayList(false);


				TiXmlElement *childs = node->FirstChildElement();

				while (childs){
					if (childs->ValueTStr() == "animationref"){
						string id = "";
						id = childs->Attribute("id");
						novoNode->getAnimations().push_back(id);
					}
					if (childs->ValueTStr() == "transforms"){
						parserGraphTransforms(novoNode, childs);
					}
					else if (childs->ValueTStr() == "appearanceref"){
						parserGraphAppearanceref(novoNode, childs);
					}
					else if (childs->ValueTStr() == "primitives"){
						parserGraphPrimitives(novoNode, childs);
					}
					else if (childs->ValueTStr() == "descendants"){
						parserGraphdescendants(novoNode, childs);
					}
					childs = childs->NextSiblingElement();
				} // end of child while
				atualizarInserirNode(id, novoNode);
				std::cout << "Node " << id << " checked!" << endl;
				node = node->NextSiblingElement();
			} // end of node while
		} // end if ( verification )
	}

	std::cout << "\n\n";
}

void XMLScene::parserGraphTransforms(Node* novoNode, TiXmlElement *childs){
	TiXmlElement* elem = childs->FirstChildElement();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	std::string type = "";
	while (elem){
		type = elem->Attribute("type");

		if (type == "translate"){
			std::string to = "";
			to = elem->Attribute("to");
			float x1, y1, z1;

			if (to != "" && sscanf(to.c_str(), "%f %f %f", &x1, &y1, &z1) == 3){
				glTranslatef(x1, y1, z1);
			}
			else
				std::cout << "Error reading perspective tag\n";
		}
		else if (type == "rotate"){
			std::string axis = "";
			axis = elem->Attribute("axis");
			float angle;

			if (axis != "" && (elem->QueryFloatAttribute("angle", &angle) == TIXML_SUCCESS)){
				if (axis == "x")
					glRotatef(angle, 1, 0, 0);
				else if (axis == "y")
					glRotatef(angle, 0, 1, 0);
				else if (axis == "z")
					glRotatef(angle, 0, 0, 1);
			}
			else
				std::cout << "Error reading perspective tag\n";
		}
		else if (type == "scale"){
			float fac1, fac2, fac3;
			std::string fac = "";
			fac = elem->Attribute("factor");

			if (fac != "" && sscanf(fac.c_str(), "%f %f %f", &fac1, &fac2, &fac3) == 3){
				glScalef(fac1, fac2, fac3);
			}
			else
				std::cout << "Error reading perspective tag\n";
		}
		elem = elem->NextSiblingElement();
	}
	float m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, &m[0]);
	novoNode->setMatrix(m);
}

void XMLScene::parserGraphAppearanceref(Node* novoNode, TiXmlElement *childs){
	std::string appReff = "";
	appReff = childs->Attribute("id");
	if (appReff != "") {
		novoNode->setAppRef(appReff);
	}
}

void XMLScene::parserGraphPrimitives(Node* novoNode, TiXmlElement *childs){
	TiXmlElement *primitivas = childs->FirstChildElement();
	if (primitivas){
		do {
			if (primitivas->ValueTStr() == "rectangle") {
				std::string xy1 = "", xy2 = "";
				float x1, x2, y1, y2;

				xy1 = primitivas->Attribute("xy1");
				xy2 = primitivas->Attribute("xy2");
				if (xy1 != "" && xy2 != "" && sscanf(xy1.c_str(), "%f %f", &x1, &y1) == 2 && sscanf(xy2.c_str(), "%f %f", &x2, &y2) == 2){
					Rectangle* a1 = new Rectangle(x1, x2, y1, y2);
					novoNode->getPrimitivas().push_back(a1);
				}
				else std::cout << "\n\nError reading rectangle!";
			}
			else if (primitivas->ValueTStr() == "triangle") {
				std::string xyz1 = "", xyz2 = "", xyz3 = "";
				float x1, x2, x3, y1, y2, y3, z1, z2, z3;

				xyz1 = primitivas->Attribute("xyz1");
				xyz2 = primitivas->Attribute("xyz2");
				xyz3 = primitivas->Attribute("xyz3");

				if (xyz1 != "" && xyz2 != "" &&  xyz3 != "" && (sscanf(xyz1.c_str(), "%f %f %f", &x1, &y1, &z1) == 3)
					&& (sscanf(xyz2.c_str(), "%f %f %f", &x2, &y2, &z2) == 3) && (sscanf(xyz3.c_str(), "%f %f %f", &x3, &y3, &z3) == 3)){
					Triangle* a1 = new Triangle(x1, x2, x3, y1, y2, y3, z1, z2, z3);
					novoNode->getPrimitivas().push_back(a1);
				}
				else std::cout << "\n\nWHOOPS... You did something wrong with triangle!";
			}
			else if (primitivas->ValueTStr() == "cylinder") {
				float base, top, height;
				int slices, stacks;
				if (primitivas->QueryFloatAttribute("base", &base) == TIXML_SUCCESS && primitivas->QueryFloatAttribute("top", &top) == TIXML_SUCCESS
					&& primitivas->QueryFloatAttribute("height", &height) == TIXML_SUCCESS && primitivas->QueryIntAttribute("slices", &slices) == TIXML_SUCCESS
					&& primitivas->QueryIntAttribute("stacks", &stacks) == TIXML_SUCCESS){
					Cylinder* a1 = new Cylinder(base, top, height, slices, stacks);
					novoNode->getPrimitivas().push_back(a1);
				}
				else std::cout << "\n\nWhoops! You did something wrong with Cylinders.";
			}
			else if (primitivas->ValueTStr() == "sphere") {
				float radius;
				int slices, stacks;
				if (primitivas->QueryFloatAttribute("radius", &radius) == TIXML_SUCCESS && primitivas->QueryIntAttribute("slices", &slices) == TIXML_SUCCESS
					&& primitivas->QueryIntAttribute("stacks", &stacks) == TIXML_SUCCESS){
					Sphere* a1 = new Sphere(radius, slices, stacks);
					novoNode->getPrimitivas().push_back(a1);
				}
				else std::cout << "\n\nWhoops! You did something wrong with Spheres.";
			}
			else if (primitivas->ValueTStr() == "torus") {
				float inner, outer;
				int slices, loops;
				if (primitivas->QueryFloatAttribute("inner", &inner) == TIXML_SUCCESS && primitivas->QueryFloatAttribute("outer", &outer) == TIXML_SUCCESS
					&& primitivas->QueryIntAttribute("slices", &slices) == TIXML_SUCCESS && primitivas->QueryIntAttribute("loops", &loops) == TIXML_SUCCESS){
					Torus* a1 = new Torus(inner, outer, slices, loops);
					novoNode->getPrimitivas().push_back(a1);
				}
				else std::cout << "\n\nWhoops! You did something wrong with Torus.";
			}
			else if (primitivas->ValueTStr() == "plane") {
				int parts;
				if (primitivas->QueryIntAttribute("parts", &parts) == TIXML_SUCCESS) {
					Plane* a1 = new Plane(parts);
					novoNode->getPrimitivas().push_back(a1);
				}
				else std::cout << "\n\nWhoops! You did something wrong with Torus.";
			}
			else if (primitivas->ValueTStr() == "patch") {
				int order, partsU, partsV;
				GLenum compute;

				std::string computeString = primitivas->Attribute("compute");
				if (computeString == "point")
					compute = GL_POINT;
				else if (computeString == "line")
					compute = GL_LINE;
				else if (computeString == "fill")
					compute = GL_FILL;

				if (primitivas->QueryIntAttribute("order", &order) == TIXML_SUCCESS && primitivas->QueryIntAttribute("partsU", &partsU) == TIXML_SUCCESS && primitivas->QueryIntAttribute("partsV", &partsV) == TIXML_SUCCESS) {
					Patch* a1 = new Patch(order, partsU, partsV, compute);
					TiXmlElement* pointElem = primitivas->FirstChildElement();
					while (pointElem != NULL) {
						float x, y, z;
						pointElem->QueryFloatAttribute("x", &x); pointElem->QueryFloatAttribute("y", &y); pointElem->QueryFloatAttribute("z", &z);
						vector<float> point;
						point.push_back(x); point.push_back(y); point.push_back(z);
						a1->addCtrlPoint(point);

						pointElem = pointElem->NextSiblingElement();
					}
					novoNode->getPrimitivas().push_back(a1);
				}
			}
			else if (primitivas->ValueTStr() == "vehicle") {
				Vehicle* a1 = new Vehicle();
				novoNode->getPrimitivas().push_back(a1);
			}
			else if (primitivas->ValueTStr() == "flag") {
				std::string textureString = primitivas->Attribute("texture");

				Flag* a1 = new Flag(textureString);
				novoNode->getPrimitivas().push_back(a1);
			}
			else {
				std::cout << "Weirds... No primitives found\n";
			}
		} while (primitivas = primitivas->NextSiblingElement());
	}
}

void XMLScene::parserGraphdescendants(Node* novoNode, TiXmlElement *childs){
	TiXmlElement *desc = childs->FirstChildElement();

	while (desc){
		std::string nodeIDref = "";
		nodeIDref = desc->Attribute("id");
		if (nodeIDref != "") {
			Node* nulo = new Node(nodeIDref);

			objetosDaCena.getGrafo().insert(std::make_pair(nulo->getId(), nulo));
			novoNode->getDescendencia().push_back(nulo->getId());
		}
		desc = desc->NextSiblingElement();
	}
};

void XMLScene::atualizarInserirNode(std::string id, Node* novoNode){
	std::map<std::string, Node*>::iterator it = objetosDaCena.getGrafo().find(id);

	if (it != objetosDaCena.getGrafo().end()){
		it->second = novoNode;
	}
	else {
		objetosDaCena.getGrafo().insert(std::make_pair(id, novoNode));
	}
}