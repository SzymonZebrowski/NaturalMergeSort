#pragma once
class Controller
{
	unsigned int numberOfSaves;
	unsigned int numberOfReads;
	int bufferSize;
public: 
	Controller(int);
	void increaseNumberOfSaves();
	void increaseNumberOfReads();
	void log();

	int getBufferSize();

};

