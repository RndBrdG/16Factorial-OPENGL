#include "XMLScene.h"

void XMLScene::parserAppearance(){

	if (appsElement == NULL)
		cout << "Appearance block not found!\n";
	else
	{
		cout << "\n----------------------- \n" << " Processing Appearances \n" << "-----------------------" << endl;

		TiXmlElement* readAppearance = appsElement->FirstChildElement("appearance");
		do{
			string id;
			if (readAppearance != NULL) {
				id = readAppearance->Attribute("id");
				float shininess;
				char* textRef = (char*)readAppearance->Attribute("textureref");
				if (id.size() > 0 && readAppearance->QueryFloatAttribute("shininess", &shininess) == TIXML_SUCCESS){
					TiXmlElement* component = readAppearance->FirstChildElement("component");
					string type, values;
					float ambient[4], difusa[4], especular[4];
					do {
						type = component->Attribute("type");
						values = component->Attribute("value");
						if (type == "ambient" && sscanf(values.c_str(), "%f %f %f %f", &ambient[0], &ambient[1], &ambient[2], &ambient[3]))
							continue;
						else if (type == "diffuse" && sscanf(values.c_str(), "%f %f %f %f", &difusa[0], &difusa[1], &difusa[2], &difusa[3]))
							continue;
						else if (type == "specular" && sscanf(values.c_str(), "%f %f %f %f", &especular[0], &especular[1], &especular[2], &especular[3]))
							continue;
					} while (component = component->NextSiblingElement());
					if (textRef == NULL || strcmp(textRef,"") == 0)
						textRef = "null";
					Aparencia* ap = new Aparencia(id, shininess, textRef,ambient,difusa,especular);
					objetosDaCena.getAparencias().insert(std::make_pair(id, ap));
					cout << "Appearance " << id << " checked!" << endl;
				}
				else {
					cout << "THERE WAS A ERROR IN YOU APPEARANCE! GO CHECK THIS " << id << " APPEARANCE !\n\n" << endl;
					system("pause");
					exit(1);
				}
			}
		} while (readAppearance = readAppearance->NextSiblingElement());
	}
}
