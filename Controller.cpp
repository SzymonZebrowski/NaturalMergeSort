#include "Controller.h"
#include <iostream>

Controller::Controller() {
	numberOfReads = 0;
	numberOfSaves = 0;
}
void Controller::increaseNumberOfSaves() {
	numberOfSaves++;
}
void Controller::increaseNumberOfReads() {
	numberOfReads++;
}
void Controller::log() {
	std::cout << "Number of saves: " << numberOfSaves << ", number of reads: " << numberOfSaves << std::endl;
}
