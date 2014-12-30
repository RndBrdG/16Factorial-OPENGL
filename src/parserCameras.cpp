#include "XMLScene.h"
#include "Camera.h"

void XMLScene::parserCameras() {
	if (camElement == NULL)
		printf("cameras block not found!\n");
	else
	{
		cout << "----------------------- \n" << " Processing cameras \n" << "-----------------------\n";
		char *initial = NULL;
		initial = (char *) camElement->Attribute("initial");
		this->objetosDaCena.setDefaultCamera(initial);
		if (initial == NULL){
			printf("Error parsing camera\n");
		}
		// Procurar câmaras.
		camElement = camElement->FirstChildElement();

		do {
			if (camElement->ValueTStr() == "perspective") { // Tag "perspective"
					char *id = NULL, *position = NULL, *target = NULL;
					float near, far, angle, posX, posY, posZ, targetX, targetY, targetZ;

					id = (char *) camElement->Attribute("id");
					position = (char *) camElement->Attribute("pos");
					target = (char *) camElement->Attribute("target");

					if (id != NULL && (camElement->QueryFloatAttribute("near", &near) == TIXML_SUCCESS) &&
						(camElement->QueryFloatAttribute("far", &far) == TIXML_SUCCESS) && (camElement->QueryFloatAttribute("angle", &angle) == TIXML_SUCCESS)
						&& (position != NULL && sscanf(position, "%f %f %f", &posX, &posY, &posZ) == 3) && (target != NULL && sscanf(target, "%f %f %f", &targetX, &targetY, &targetZ) == 3)){
						cout << "Camara " << id << " checked!" << endl;
						Camera* a1 = new Camera(id, "perspective", near, far, angle, targetX, targetY, targetZ, posX, posY, posZ);
						this->objetosDaCena.getCamaras().insert(std::make_pair(a1->getId(), a1));
					}
					else
						printf("Error reading perspective tag\n");
			}
			else if (camElement->ValueTStr() == "ortho") { // Tag "ortho"

					char *id = NULL, *dir = NULL;
					float near, far, left, right, top, bottom;

					id = (char *) camElement->Attribute("id");
					dir = (char *) camElement->Attribute("direction");

					if (id != NULL && dir != NULL && (camElement->QueryFloatAttribute("near", &near) == TIXML_SUCCESS) && (camElement->QueryFloatAttribute("left", &left) == TIXML_SUCCESS)
						&& (camElement->QueryFloatAttribute("far", &far) == TIXML_SUCCESS) && (camElement->QueryFloatAttribute("right", &right) == TIXML_SUCCESS)
						&& (camElement->QueryFloatAttribute("top", &top) == TIXML_SUCCESS) && (camElement->QueryFloatAttribute("bottom", &bottom) == TIXML_SUCCESS)){
						cout << "Camara " << id << " checked!" << endl;
						Camera* a1 = new Camera(id, "ortho", dir, left, right, top, bottom,near,far);
						this->objetosDaCena.getCamaras().insert(std::make_pair(a1->getId(), a1));
					}
					else
						printf("Error reading ortho tag\n");
			}
			else {
				printf("Unknown camera tag found\n");
			}
		} while (camElement = camElement->NextSiblingElement());
	}
}
