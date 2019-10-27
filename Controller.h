#pragma once
class Controller
{
	unsigned int numberOfSaves;
	unsigned int numberOfReads;
public: 
	Controller();
	void increaseNumberOfSaves();
	void increaseNumberOfReads();
	void log();
};

