#pragma once
class Controller
{
	unsigned int numberOfSaves;
	unsigned int numberOfReads;
	unsigned int numberOfPhases;
	int bufferSize;
public: 
	Controller(int);
	void increaseNumberOfSaves();
	void increaseNumberOfReads();
	void increaseNumberOfPhases();
	void log();

	int getBufferSize();

};

