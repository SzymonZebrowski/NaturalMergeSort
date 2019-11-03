#ifndef INPUTBUFFER_H
#define INPUTBUFFER_H
#include "Paralelogram.h"
#include "Controller.h"
#include <iostream>
#include <fstream>

class InputBuffer
{
	Controller* controller;
	Paralelogram* buffer;	//tab of records
	int bufferSize;			//size of records' tab
	int lastRecord;			//index of last record in buffer
	int actualRecord;		//index of next record to read

	int bookmark;			//index of previously read record (from file)
	bool eof;
	std::string file;		//name of file
	std::fstream input;

public:
	InputBuffer(Controller *c, std::string filename, int bufferSize_);
	~InputBuffer();
	Paralelogram* getRecord();
	void printBuffer(); 
	void loadBuffer();
};
#endif
