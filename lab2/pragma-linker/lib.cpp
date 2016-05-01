#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cstring>

#include "lib.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD callReason, LPVOID lp)
{
	const char* name = NULL;
	switch (callReason) {
	case DLL_PROCESS_ATTACH:
		name = "Kun, Ira, James";
		object = new MyObject(name);
		timestamp = time(NULL);
		std::cout << "DLL process attached" << std::endl;
		break;
	case DLL_THREAD_ATTACH: break;
	case DLL_THREAD_DETACH: break;
	case DLL_PROCESS_DETACH:
		delete object;
		std::cout << "DLL process detached" << std::endl;
	}
	return TRUE;
}
int timestamp = 0;
MyObject* object = NULL;

int sum(int a, int b) {
	return a + b;
}

char* whoami() {
	return (char*)"Kun, Ira, James";
}

MyObject::MyObject(const char*& s) {
	setName(s);
}

char* MyObject::getName() {
	return name;
}

void MyObject::setName(const char*& s) {
	name = new char[strlen(s) + 1];
	memset(name, 0, strlen(s) + 1);
	strcpy(name, s);
}

MyObject::~MyObject() {
	delete[] name;
}

IMyObject* createObject(const char*& s) {
	IMyObject* obj = new MyObject(s);
	return obj;
}
