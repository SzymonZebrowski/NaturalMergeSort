#define _USE_MATH_DEFINES
#include "Controller.h"
#include "InputBuffer.h"
#include "OutputBuffer.h"
#include "time.h"
#include <math.h>
#include "stdlib.h"

Controller::Controller(int bufferSize_, std::string input, bool saep, bool sas) {
	numberOfReads = 0;
	numberOfSaves = 0;
	numberOfPhases = 0;
	bufferSize = bufferSize_;
	showAfterEachPhase = saep;
	showAfterSorting = sas;

	if (input.length() > 4 && input.substr(input.length() - 4, input.length() - 1) == ".txt") fileInput(input);
	else if (input.substr(0, 1) == "k") userInput(atoi(input.substr(1).c_str()));
	else if (input.substr(0, 1) == "r") randomInput(atoi(input.substr(1).c_str()));
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

void Controller::distribution() {
	increaseNumberOfPhases();
	std::string input = "c.txt";
	std::string output1 = "a.txt";
	std::string output2 = "b.txt";

	InputBuffer* tapeI = new InputBuffer(this, input, getBufferSize());
	OutputBuffer* tapeO1 = new OutputBuffer(this, output1, getBufferSize());
	OutputBuffer* tapeO2 = new OutputBuffer(this, output2, getBufferSize());

	Paralelogram* record = nullptr;
	float prevValue = 0;
	OutputBuffer* tape = tapeO1;

	while (true) {
		record = tapeI->getRecord();

		if (record == nullptr) break;

		if (prevValue > record->get_field()) {	//end of series, need to switch tape
			tape == tapeO1 ? tape = tapeO2 : tape = tapeO1;
		}
		tape->putRecord(record);
		prevValue = record->get_field();
	}
	delete tapeI;
	delete tapeO1;
	delete tapeO2;
}

bool Controller::merging() {
	std::string input1 = "a.txt";
	std::string input2 = "b.txt";
	std::string output = "c.txt";

	InputBuffer* tapeI1 = new InputBuffer(this, input1, getBufferSize());
	InputBuffer* tapeI2 = new InputBuffer(this, input2, getBufferSize());
	OutputBuffer* tapeO = new OutputBuffer(this, output, getBufferSize());



	Paralelogram* recordI1 = tapeI1->getRecord(), * recordI2 = tapeI2->getRecord();
	float prevValueI1 = 0, prevValueI2 = 0;

	if (recordI2 == nullptr) { //tape "b" is empty - all records are on "a" tape (sorted)
		delete tapeI1;
		delete tapeI2;
		delete tapeO;
		return false;
	}
	while (true) {
		if (recordI1 != nullptr && recordI2 != nullptr) {
			if (recordI1->get_field() < prevValueI1) {
				while (recordI2 != nullptr && recordI2->get_field() > prevValueI2) {
					tapeO->putRecord(recordI2);
					prevValueI2 = recordI2->get_field();
					recordI2 = tapeI2->getRecord();
				}
				prevValueI1 = prevValueI2 = 0;
			}
			else if (recordI2->get_field() < prevValueI2) {
				while (recordI1 != nullptr && recordI1->get_field() > prevValueI1) {
					tapeO->putRecord(recordI1);
					prevValueI1 = recordI1->get_field();
					recordI1 = tapeI1->getRecord();
				}
				prevValueI1 = prevValueI2 = 0;
			}
			else {
				if (recordI1->get_field() <= recordI2->get_field()) {
					tapeO->putRecord(recordI1);
					prevValueI1 = recordI1->get_field();
					recordI1 = tapeI1->getRecord();
				}
				else if (recordI2->get_field() < recordI1->get_field()) {
					tapeO->putRecord(recordI2);
					prevValueI2 = recordI2->get_field();
					recordI2 = tapeI2->getRecord();
				}
			}
		}
		else if (recordI1 == nullptr) {
			while (recordI2 != nullptr) {
				tapeO->putRecord(recordI2);
				recordI2 = tapeI2->getRecord();
			}
			break;
		}
		else if (recordI2 == nullptr) {
			while (recordI1 != nullptr) {
				tapeO->putRecord(recordI1);
				recordI1 = tapeI1->getRecord();
			}
			break;
		}
	}
	delete tapeI1;
	delete tapeI2;
	delete tapeO;
	return true;
}
void Controller::rewriteSorted() {
	std::string input = "a.txt";
	std::string output = "sorted.txt";

	InputBuffer* org = new InputBuffer(this, input, getBufferSize());
	OutputBuffer* copy = new OutputBuffer(this, output, getBufferSize());

	while (copy->putRecord(org->getRecord()));
	copy->saveRest();
	delete copy;
	delete org;

	remove("a.txt");
	remove("b.txt");
	remove("c.txt");
}

void Controller::printFile(std::string file) {
	std::fstream input(file);
	float a, b, angle;
	std::cout << "============= Printing file =============" << std::endl;
	while (input >> a >> b >> angle) {
		std::cout << Paralelogram(a, b, angle).to_string() << std::endl;
	}
	input.close();
	std::cout << "============= Printing finished =============" << std::endl;
}

void Controller::sort() {
	if (showAfterSorting) printFile("c.txt");
	while (true) {
		distribution();
		if (!merging()) break;
		if (showAfterEachPhase) printFile("c.txt");
	}
	if (showAfterSorting) printFile("a.txt");
	log();
}

void Controller::fileInput(std::string file) {
	float a, b, angle;
	std::fstream input(file);
	std::fstream output("c.txt", std::ios::out | std::ios::app);
	while (input >> a >> b >> angle) {
		output << a << " " << b << " " << angle << std::endl;
	}
	input.close();
	output.close();
}

void Controller::userInput(int n) {
	std::cout << "Waiting for user input..." << std::endl;
	remove("original_input.txt");
	std::fstream output("c.txt", std::ios::out | std::ios::app);
	std::fstream org("original_input.txt", std::ios::out | std::ios::app);
	float a, b, angle;
	for (int i = 0; i < n; i++) {
		std::cin >> a >> b >> angle;
		output << a << " " << b << " " << angle << std::endl;
		org << a << " " << b << " " << angle << std::endl;
	}
	output.close();
	org.close();
}

void Controller::randomInput(int n) {
	srand(time(NULL));
	remove("original_input.txt");
	std::fstream output("c.txt", std::ios::out | std::ios::app);
	std::fstream org("original_input.txt", std::ios::out | std::ios::app);
	int s = 0;
	int e = 100;
	float c = M_PI;
	for(int i = 0; i < n; i++){
		float a = (e - s) * float(rand()) / float(RAND_MAX) + s;
		float b = (e - s) * float(rand()) / float(RAND_MAX) + s;
		float angle = c * float(rand()) / float(RAND_MAX);
		output << a << " " << b << " " << angle << std::endl;
		org << a << " " << b << " " << angle << std::endl;
	}
	output.close();
	org.close();
}