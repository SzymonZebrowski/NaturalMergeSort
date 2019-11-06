#include "OutputBuffer.h"

OutputBuffer::OutputBuffer(Controller* c, std::string filename, int bufferSize_, bool logs_) {
	bufferSize = bufferSize_;
	buffer = new Paralelogram*[bufferSize];
	actualRecord = 0;
	logs = logs_;
	controller = c;
	file = filename;
	remove(file.c_str());
	output = std::fstream(file, std::ios::out | std::ios::app);
}

OutputBuffer::~OutputBuffer() {
	if(actualRecord){
		controller->increaseNumberOfSaves();

	//std::ofstream output(file, std::ios::out | std::ios::app);
		for (int i = 0; i < actualRecord; i++) {
			output << buffer[i]->to_raw_data() << std::endl;
			delete buffer[i];
		}
	}
	output.close();
	delete [] buffer;
}

bool OutputBuffer::putRecord(Paralelogram* record) { //save record to file
	if (actualRecord == bufferSize) { //buffer if full, we need to save to file
		controller->increaseNumberOfSaves();

		//std::ofstream output(file, std::ios::out | std::ios::app);

		actualRecord = 0;

		if (logs) std::cout << "File after next phase: " << std::endl;
		for (int i = 0; i < bufferSize; i++) {
			output << buffer[i]->to_raw_data() << std::endl;
			if (logs) std::cout << buffer[i] << std::endl;
			delete buffer[i];
		}
		//output.close();
	}

	if (record == nullptr) return false;
	//save record to buffer
	buffer[actualRecord++] = record;
	return true;
}

void OutputBuffer::printBuffer() {
	for (int i = 0; i < actualRecord; i++) {
		std::cout << i << ". " << buffer[i] << std::endl;
	}
}


