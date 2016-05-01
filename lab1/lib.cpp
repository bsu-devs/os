#include <iostream>
#include <Windows.h>

#include "lib.h"

extern "C" 
{
	DECLDIR int sum(int a, int b) {
		return a + b;
	}

	DECLDIR void printCopyright(void) {
		std::cout << "BSU FAMCS 2016 2 grade 4 semester (Ira, Kun, James)" << std::endl;
	}

	DECLDIR void showCopyright(void) {
		MessageBox(NULL, L"BSU FAMCS 2016 2 grade 4 semester (Ira, Kun, James)", NULL, NULL);
	}
}