#pragma once
class Controller
{
	unsigned int numberOfSaves;
	unsigned int numberOfReads;
	unsigned int numberOfMergingPhases;
	unsigned int numberOfDistributionPhases;
	int bufferSize;
public: 
	Controller(int);
	void increaseNumberOfSaves();
	void increaseNumberOfReads();
	void increaseNumberOfDistributionPhases();
	void increaseNumberOfMergingPhases();
	void log();

	int getBufferSize();

};

