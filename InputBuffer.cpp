#include "InputBuffer.h"

InputBuffer::InputBuffer(Controller *c, std::string filename, int bufferSize_) {
	file = filename;
	bufferSize = bufferSize_;
	buffer = new Paralelogram*[bufferSize];
	actualRecord = bufferSize;
	lastRecord = 0;
	eof = false;
	bookmark = 0;
	controller = c;
	input = std::fstream(file);
}

InputBuffer::~InputBuffer() {
	input.close();
	delete[] buffer;
}

Paralelogram* InputBuffer::getRecord() {

	if (actualRecord == bufferSize) {	//buffer is empty, we need to read data from file
		//std::cout << "Buffer empty, loading data from tape." << std::endl;
		loadBuffer();		
	}

	//buffer is full, nothing more to read from file
	if (actualRecord >= lastRecord && eof)	return nullptr;
	else return buffer[actualRecord++];
}

void InputBuffer::printBuffer() {
	for (int i = actualRecord-1; i < lastRecord; i++) {
		std::cout << i << ". " << buffer[i] << std::endl;
	}
}

void InputBuffer::loadBuffer() {
	controller->increaseNumberOfReads();
	Paralelogram* new_paralelogram;
	float a, b, c;
	//input.seekg(bookmark, input.beg);

	lastRecord = 0;

	while ((lastRecord < bufferSize) && !eof) {
		if (input >> a >> b >> c) {
			new_paralelogram = new Paralelogram(a, b, c);
			buffer[lastRecord++] = new_paralelogram;
		}
		else {
			eof = true;
		}
	}

	//bookmark = input.tellg();
	//input.close();
	actualRecord = 0;
	bookmark++;
}