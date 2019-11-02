#include "InputController.h"

InputController::InputController(int a, char* av[]) {
	argc = a;
	argv = av;
	is_valid = true;
	if (argc < 2) {
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
		std::cout << argv[i] << std::endl;
		if (std::string(argv[i]) == "--vp") showAfterEachPhase = true;
		else if (std::string(argv[i]) == "--v") showAfterSorting = true;
		else if (std::string(argv[i]) == "--random") input = "random";
		else if (std::string(argv[i]) == "--keyboard") input = "keyboard";
		else if (std::string(argv[i]).substr(0,6) == "--file") input = std::string(argv[i]).substr(7);
		else if (std::string(argv[i]).substr(0,6) == "--buff") bufferSize = atoi(std::string(argv[i]).substr(7).c_str());
	}

	std::cout << "InputController:" << std::endl;
	std::cout << "Show after each phase?: " << showAfterEachPhase << std::endl;
	std::cout << "Show before/after sorting?: " << showAfterSorting << std::endl;
	std::cout << "Input type: " << input << std::endl;
	std::cout << "Buffer size: " << bufferSize << std::endl;
}

void InputController::usage() {
	std::cout << "Usage" << std::endl;
}

