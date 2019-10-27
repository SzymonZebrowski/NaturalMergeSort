#include <iostream>
#include "InputBuffer.h"


int main() {
	InputBuffer inputBuf("tape1.txt", 256);
	
	int i = 0;
	while (true) {
		i++;
		std::cout << i << ". " << inputBuf.getRecord() << std::endl;
		
	}
	return 0;
}