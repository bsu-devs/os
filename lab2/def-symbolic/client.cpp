#include <Windows.h>
#include <iostream>
#include <ctime>

using namespace std;

int main () {
	HMODULE hLib = LoadLibraryA("lib.dll");
	if (!hLib) throw GetLastError();

	// Test for exported variable timestamp
	time_t timestamp = (time_t) GetProcAdress(hLib, "timestamp");
	cout << "Timestamp: " << timestamp << "\n\n";
	
	// Test for exported function sum
	int (*sum)(int, int);
	sum = (int (*)(int, int)) GetProcAdress(hLib, "sum");
	cout << "2 + 5 = " << sum(2, 5) << "\n\n";

	// Test for exported function whoami
	void (*whoami)();
	whoami = (void (*)()) GetProcAdress(hLib, "whoami");
	cout << "WHOAMI: " << whoami() << "\n\n";

	// Test for exported class MyObject
	MyObject* object = (*MyObject) GetProcAdress(hLib, "object");
	cout << "Initial name: " << object->getName() << "\n";
	object->setName("James, Ira, Kun");
	cout << "New name: " << object->getName() << "\n\n";

	FreeLibrary(hLib);
}