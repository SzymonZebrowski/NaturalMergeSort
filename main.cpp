#include <iostream>
#include <fstream>
#include "Controller.h"
#include "Paralelogram.h"

int main() {
	Controller* controller = new Controller(512);
	
	while (true) {
		controller->distribution();
		if(!controller->merging()) break;
	}

	controller->rewriteSorted();

	std::ifstream file("sorted.txt");
	float a, b, c;
	int i = 0;
	
	while (file >> a >> b >> c) {
		std::cout << Paralelogram(a, b, c) << std::endl;
	}
	
	file.close();
	controller->log();
	return 0;
}