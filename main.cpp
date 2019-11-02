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

	InputController(argc, argv);

	return 0;
	Controller* controller = new Controller(100);
	
	while (true) {
		controller->distribution();
		if(!controller->merging()) break;
	}

	controller->rewriteSorted();

	/*
	std::ifstream file("sorted.txt");
	float a, b, c;
	int i = 0;
	
	while (file >> a >> b >> c) {
		std::cout << Paralelogram(a, b, c) << std::endl;
	}
	
	file.close();
	controller->log();
	*/
	return 0;
}