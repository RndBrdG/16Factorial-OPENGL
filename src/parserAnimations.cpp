#include "XMLScene.h"

void XMLScene::parserAnimations(){
	if (AnimElement == NULL)
		cout << "cameras block not found!" << endl;
	else
	{
		cout << "----------------------- \n" << " Processing Animations \n" << "-----------------------\n";

		TiXmlElement* drawingElement = AnimElement->FirstChildElement("animation");

		if (drawingElement){

			while (drawingElement){
				string id = "", type;
				float span = -1;

				id = drawingElement->Attribute("id");
				type = drawingElement->Attribute("type");
				drawingElement->QueryFloatAttribute("span", &span);

				if (type == "linear"){
					vector<Ponto*> pontosDeControlo;

					TiXmlElement* controlElement = drawingElement->FirstChildElement("controlpoint");
					while (controlElement){
						float xx, yy, zz;
						controlElement->QueryFloatAttribute("xx", &xx);
						controlElement->QueryFloatAttribute("yy", &yy);
						controlElement->QueryFloatAttribute("zz", &zz);
						Ponto* a1 = new Ponto(xx, yy, zz);
						pontosDeControlo.push_back(a1);
						controlElement = controlElement->NextSiblingElement();
					}
					LinearAnimation* newLinear = new LinearAnimation(id, span, pontosDeControlo);
					this->objetosDaCena.getAnimations().insert(std::make_pair(id, newLinear));
				}
				else {
					char* center = (char*) drawingElement->Attribute("center");
					float x, y, z;
					float radius, startang, rotang;
					sscanf(center, "%f %f %f", &x, &y, &z);
					drawingElement->QueryFloatAttribute("radius", &radius);
					drawingElement->QueryFloatAttribute("startang", &startang);
					drawingElement->QueryFloatAttribute("rotang", &rotang);
					Ponto* a2 = new Ponto(x, y, z);
					CircularAnimation* newCircular = new CircularAnimation(id, span, a2, radius, startang, rotang);
					this->objetosDaCena.getAnimations().insert(std::make_pair(id, newCircular));
				}
				drawingElement = drawingElement->NextSiblingElement();
			}
		}
		else {
			cout << "Error reading Animations" << endl;
		}
	}
}