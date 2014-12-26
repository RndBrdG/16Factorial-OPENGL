/* 
 * G0_Base: projeto inicial de LAIG
 * 
 */

#include <iostream>
#include <exception>
#include <sstream>

#include "CGFapplication.h"
#include "DemoScene.h"
#include "TPinterface.h"
#include "PickInterface.h"
#include "XMLScene.h"

using std::cout;
using std::exception;

int main(int argc, char* argv[]) {

	CGFapplication app = CGFapplication();

	try {
		app.init(&argc, argv);

		/*
		std::stringstream filename;
		filename << "../res/";
		std::cout << endl << "Introduza o nome do ficheiro .anf\nda cena presente em /res (sem extensao): ";
		std::string temp;
		getline(std::cin, temp);
		filename << temp << ".anf";
		std::cout << endl;*/

		app.setScene(new DemoScene(/*const_cast<char*>(filename.str().c_str())*/"../res/scene_tab.anf"));
		app.setInterface(new TPinterface());
		app.setInterface(new PickInterface());
		
		app.run();
	}
	catch (GLexception& ex) {
		cout << "Error: " << ex.what();
		return -1;
	}
	catch (exception& ex) {
		cout << "Unexpected error: " << ex.what();
		return -1;
	}

	return 0;
}
