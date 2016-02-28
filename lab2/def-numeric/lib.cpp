#include <iostream>
#include <Windows.h>
#include <ctime>
#include <ctring>

#include "lib.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD callReason, LPVOID lp)
{
	switch (callReason) {

		case DLL_PROCESS_ATTACH:
			object = new MyObject("Kun, Ira, James");
			timestamp = time();
			std::cout << "DLL process attached" << std::endl;
			break;
		case DLL_THREAD_ATTACH: break;
		case DLL_THREAD_DETACH: break;
		case DLL_PROCESS_DETACH:
			delete object;
			std::cout << "DLL process detached" << std::endl;
		}
		break;
	}
	return TRUE;
}

timestamp = 0;
object = 0;

LIBAPI int sum(int a, int b) {
	return a + b;
}

LIBAPI const char& whoami() {
	return "Kun, Ira, James";
}

MyObject::MyObject(const char& s) {
	setName(s);
}

char* MyObject::getName() {
	return name;
}

void MyObject::setName(const char& s) {
	name = new char[strlen(s) + 1];
	memset(name, 0, strlen(s) + 1);
	strcpy(name, s);
}
    	
MyObject::~MyObject() {
	delete[] name;
}