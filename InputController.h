#pragma once
#include <iostream>

class InputController
{

	/*
	1. buffer size -> --buff=512
	2. type of input -> --random/--file=xxx.txt/--keyboard
	3. show before/after sorting -> --v
	4. show after each phase -> --vp
	*/

	int argc;
	char** argv;
	bool is_valid;

	bool showAfterEachPhase = false;
	bool showAfterSorting = false;
	std::string input;
	int bufferSize;

public:
	InputController(int, char**);
	void parseInput();
	void usage();
};

