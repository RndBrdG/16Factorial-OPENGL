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

			app.setScene(new DemoScene("../res/scene_tab.anf"));
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
