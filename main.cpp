#include <iostream>
#include "Paralelogram.h"


int main() {
	std::cout << "Hello World!" << std::endl;

	Paralelogram c = Paralelogram(5, 4, 3.1415/2);
	Paralelogram *n = new Paralelogram(1, 2, 0.7853);

	std::cout << c << std::endl;
	std::cout << n << std::endl;
	return 0;
}