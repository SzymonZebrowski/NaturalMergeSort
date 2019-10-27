#include <iostream>
#include "InputBuffer.h"
#include "OutputBuffer.h"
#include "Controller.h"

void distribution(Controller* controller) {
	controller->increaseNumberOfDistributionPhases();
	std::string input = "c.txt";
	std::string output1 = "a.txt";
	std::string output2 = "b.txt";

	InputBuffer* tapeI = new InputBuffer(controller, input, controller->getBufferSize());
	OutputBuffer* tapeO1 = new OutputBuffer(controller, output1, controller->getBufferSize());
	OutputBuffer* tapeO2 = new OutputBuffer(controller, output2, controller->getBufferSize());

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

bool merging(Controller* controller) {
	controller->increaseNumberOfMergingPhases();
	std::string input1 = "a.txt";
	std::string input2 = "b.txt";
	std::string output = "c.txt";

	InputBuffer* tapeI1 = new InputBuffer(controller, input1, controller->getBufferSize());
	InputBuffer* tapeI2 = new InputBuffer(controller, input2, controller->getBufferSize());
	OutputBuffer* tapeO = new OutputBuffer(controller, output, controller->getBufferSize());

	

	Paralelogram *recordI1 = tapeI1->getRecord(), *recordI2 = tapeI2->getRecord();
	float prevValueI1 = 0, prevValueI2 = 0;

	if (recordI2 == nullptr) return false;
	while (1) {
		if (recordI1 != nullptr && recordI2 != nullptr) {
			
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

void rewriteSorted(Controller* controller) {
	std::string input = "a.txt";
	std::string output = "sorted.txt";

	InputBuffer* org = new InputBuffer(controller, input, controller->getBufferSize());
	OutputBuffer* copy = new OutputBuffer(controller, output, controller->getBufferSize());

	while (copy->putRecord(org->getRecord()));
	copy->saveRest();
	delete copy;
	delete org;

	remove("a.txt");
	remove("b.txt");
}

int main() {
	Controller* controller = new Controller(1200);
	
	while (true) {
		distribution(controller);
		if(!merging(controller)) break;
	}

	rewriteSorted(controller);

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