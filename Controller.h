#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <iostream>

class Controller
{
	unsigned int numberOfSaves;
	unsigned int numberOfReads;
	unsigned int numberOfPhases;

	int bufferSize;
	bool showAfterEachPhase;
	bool showAfterSorting;
public: 
	Controller(int, std::string, bool, bool);

	void increaseNumberOfSaves();
	void increaseNumberOfReads();
	void increaseNumberOfPhases();
	void log();

	void distribution();
	bool merging();
	void rewriteSorted();
	void sort();
	void printFile(std::string file);

	void fileInput(std::string);
	void userInput(int);
	void randomInput(int);

	int getBufferSize();

};
#endif
