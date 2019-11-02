#include "InputController.h"

InputController::InputController(int a, char* av[]) {
	argc = a;
	argv = av;
	is_valid = true;
	if (argc < 3) {
		is_valid = false;
		usage();
	}
	if(is_valid) parseInput();
}

void InputController::parseInput() {
	/*
	1. buffer size -> --buff = 512
	2. type of input -> --random / --file = xxx.txt / --keyboard
	3. show before / after sorting -> --v
	4. show after each phase -> --vp
	*/
	
	for (int i = 1; i < argc; i++) {
		if (std::string(argv[i]) == "--vp") showAfterEachPhase = true;
		else if (std::string(argv[i]) == "--v") showAfterSorting = true;
		else if (std::string(argv[i]).substr(0,8) == "--random") input = "r" + std::string(argv[i]).substr(9);
		else if (std::string(argv[i]).substr(0,10) == "--keyboard") input = "k" + std::string(argv[i]).substr(11);
		else if (std::string(argv[i]).substr(0,6) == "--file") input = std::string(argv[i]).substr(7);
		else if (std::string(argv[i]).substr(0,6) == "--buff") bufferSize = atoi(std::string(argv[i]).substr(7).c_str());
	}
}

void InputController::usage() {
	std::cout << "Usage:" << std::endl;
	std::cout << "--buff= xxx -> set buffer size to xxx" << std::endl;
	std::cout << "--file= xxx -> set input file to xxx" << std::endl;
	std::cout << "--random= xxx -> generate xxx random records" << std::endl;
	std::cout << "--keyboard= xxx -> type xxx records" << std::endl;
	std::cout << "--v -> print records before and after sorting" << std::endl;
	std::cout << "--vp -> print records after each phase of sorting" << std::endl;
}

bool InputController::getShowAfterEachPhase() {
	return showAfterEachPhase;
}
bool InputController::getShowAfterSorting() {
	return showAfterSorting;
}
std::string InputController::getInputMethod() {
	return input;
}
int InputController::getBufferSize() {
	return bufferSize;
}