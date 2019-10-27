#include "Controller.h"
#include <iostream>

Controller::Controller(int bufferSize_) {
	numberOfReads = 0;
	numberOfSaves = 0;
	numberOfDistributionPhases = 0;
	numberOfMergingPhases = 0;
	bufferSize = bufferSize_;
}
void Controller::increaseNumberOfSaves() {
	numberOfSaves++;
}
void Controller::increaseNumberOfReads() {
	numberOfReads++;
}
void Controller::increaseNumberOfDistributionPhases() {
	numberOfDistributionPhases++;
}
void Controller::increaseNumberOfMergingPhases() {
	numberOfMergingPhases++;
}
void Controller::log() {
	std::cout << "Number of saves: " << numberOfSaves << ", number of reads: " << numberOfSaves << std::endl;
	std::cout << "Number of distribution phases: " << numberOfDistributionPhases << std::endl;
	std::cout << "Number of merging phases: " << numberOfMergingPhases << std::endl;
}

int Controller::getBufferSize() {
	return bufferSize;
}
