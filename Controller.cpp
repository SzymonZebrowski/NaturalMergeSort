#include "Controller.h"
#include <iostream>
#include "InputBuffer.h"
#include "OutputBuffer.h"

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

		if (prevValue > record->get_field()) {	//switch tape
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

	if (recordI2 == nullptr) {
		delete tapeI1;
		delete tapeI2;
		delete tapeO;
		return false;
	}
	while (1) {
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
					//std::cout << "Zapisano: " << recordI1 << std::endl;
					prevValueI1 = recordI1->get_field();
					recordI1 = tapeI1->getRecord();
				}
				else if (recordI2->get_field() < recordI1->get_field()) {
					tapeO->putRecord(recordI2);
					//std::cout << "Zapisano: " << recordI2 << std::endl;
					prevValueI2 = recordI2->get_field();
					recordI2 = tapeI2->getRecord();
				}
			}
		}
		else if (recordI1 == nullptr) {
			while (recordI2 != nullptr) {
				tapeO->putRecord(recordI2);
				//std::cout << "Zapisano: " << recordI2 << std::endl;
				recordI2 = tapeI2->getRecord();
			}
			break;
		}
		else if (recordI2 == nullptr) {
			while (recordI1 != nullptr) {
				tapeO->putRecord(recordI1);
				//std::cout << "Zapisano: " << recordI1 << std::endl;
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
}