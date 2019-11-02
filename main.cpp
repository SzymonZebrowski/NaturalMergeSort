#include <iostream>
#include <fstream>
#include "Controller.h"
#include "Paralelogram.h"
#include "InputController.h"

int main(int argc, char* argv[]) {
	/*
	1. buffer size -> --buff=512
	2. type of input -> --random/--file=xxx.txt/--keyboard
	3. show before/after sorting -> --v
	4. show after each phase -> --vp
	*/

	InputController inputController(argc, argv);

	Controller* controller = new Controller(inputController.getBufferSize(),
											inputController.getInputMethod(),
											inputController.getShowAfterEachPhase(),
											inputController.getShowAfterSorting());
	
	
	controller->sort();
	controller->rewriteSorted();

	return 0;
}