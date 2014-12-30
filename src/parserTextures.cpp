#include <XMLScene.h>

void XMLScene::parserTextures(){
	if (texElement == NULL)
		printf("Textures block not found!\n");
	else
	{
		cout << "\n----------------------- \n" << " Processing Textures \n" << "-----------------------" << endl;
		TiXmlElement* textureElement = texElement->FirstChildElement("texture");
		std::string id;
		std::string file;
		float texlength_s;
		float texlength_t;
		do{
			id = textureElement->Attribute("id");
			file = textureElement->Attribute("file");
			textureElement->QueryFloatAttribute("texlength_s", &texlength_s);
			textureElement->QueryFloatAttribute("texlength_t", &texlength_t);
			Textura* a1 = new Textura(id, file, texlength_s, texlength_t);
			objetosDaCena.getTexturas().insert(std::make_pair(id, a1));
			cout << "Texture " << id << " checked!" << endl;
		} while (textureElement = textureElement->NextSiblingElement());

		std::map<std::string, Aparencia*>::iterator itera;
		for (itera = this->objetosDaCena.getAparencias().begin(); itera != this->objetosDaCena.getAparencias().end(); itera++){
			if (itera->second->getTextRef() == "null") continue;
			itera->second->setTexture(this->objetosDaCena.getTexturas()[itera->second->getTextRef()]->getFile());
		}

	}
}