#include "Controller.h"
#include <iostream>

Controller::Controller(int bufferSize_) {
	numberOfReads = 0;
	numberOfSaves = 0;
	numberOfPhases = 0;
	bufferSize = bufferSize_;
}
void Controller::increaseNumberOfSaves() {
	numberOfSaves++;
}
void Controller::increaseNumberOfReads() {
	numberOfReads++;
}
void Controller::increaseNumberOfPhases() {
	numberOfPhases++;
}

void Controller::log() {
	std::cout << "Number of saves: " << numberOfSaves << ", number of reads: " << numberOfSaves << std::endl;
	std::cout << "Number of phases: " << numberOfPhases << std::endl;
}

int Controller::getBufferSize() {
	return bufferSize;
}
