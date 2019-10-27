#pragma once
#include "Paralelogram.h"
#include "Controller.h"
#include <iostream>
#include <fstream>

class OutputBuffer
{
	Controller* controller;
	Paralelogram* buffer;	//tab of records
	int bufferSize;			//size of records' tab
	int lastRecord;			//index of last record in buffer
	int actualRecord;		//index of next record to read
	bool logs;				//display logs

	int bookmark;			//index of previously read record (from file)
	bool eof;
	std::string file;		//name of file

public:
	OutputBuffer(Controller* c, std::string filename, int bufferSize_, bool logs_ = false);
	~OutputBuffer();
	bool putRecord(Paralelogram* record);
	void saveRest();
	void printBuffer();
};

