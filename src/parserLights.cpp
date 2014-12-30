#include "XMLScene.h"

#include <sstream>

void XMLScene::parserLights() {
	if (lightsElement == NULL)
		printf("lights block not found!\n");
	else {
		cout << "\n----------------------- \n" << " Processing Lights \n" << "-----------------------" << endl;

		TiXmlElement* lightElement = lightsElement->FirstChildElement("light");

		if (lightElement != NULL) {
			if (Light::num < 8) {
				do {
					Light* newLight;

					float pos[4];
					sscanf(lightElement->Attribute("pos"), "%f %f %f", &pos[0], &pos[1], &pos[2]);
					pos[3] = 1.;

					std::string type = lightElement->Attribute("type");
					if (type == "omni") {
						newLight = new Light(GL_LIGHT0 + Light::num, pos);
					}
					else if (type == "spot") {
						float dir[3];
						sscanf(lightElement->Attribute("target"), "%f %f %f", &dir[0], &dir[1], &dir[2]);

						float angle;
						sscanf(lightElement->Attribute("angle"), "%f", &angle);

						float exponent;
						sscanf(lightElement->Attribute("exponent"), "%f", &exponent);

						newLight = new Light(GL_LIGHT0 + Light::num, pos, dir, angle, exponent);
					}
					else continue;

					std::string enabled = lightElement->Attribute("enabled");
					if (enabled == "true")
						newLight->enabled = true;
					else if (enabled == "false")
						newLight->enabled = false;

					std::string marker = lightElement->Attribute("marker");
					if (marker == "true")
						newLight->marker = true;
					else if (marker == "false")
						newLight->marker = false;

					TiXmlElement* component = lightElement->FirstChildElement("component");
					do {
						std::string type = component->Attribute("type");

						if (type == "ambient")
							sscanf(component->Attribute("value"), "%f %f %f %f", &newLight->ambient[0], &newLight->ambient[1], &newLight->ambient[2], &newLight->ambient[3]);
						else if (type == "diffuse")
							sscanf(component->Attribute("value"), "%f %f %f %f", &newLight->diffuse[0], &newLight->diffuse[1], &newLight->diffuse[2], &newLight->diffuse[3]);
						else if (type == "specular")
							sscanf(component->Attribute("value"), "%f %f %f %f", &newLight->specular[0], &newLight->specular[1], &newLight->specular[2], &newLight->specular[3]);
					} while (component = component->NextSiblingElement());
					cout << "Light " << newLight->id << " checked!" << endl;
					objetosDaCena.getLuzes().insert(std::make_pair(lightElement->Attribute("id"), newLight));
				} while (lightElement = lightElement->NextSiblingElement());
			}
		}
		else printf("light not found\n");
	}
}
