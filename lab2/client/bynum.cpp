#include <Windows.h>
#include <iostream>
#include <ctime>

#define SUM_NUM 1
#define WHOAMI_NUM 2
#define TIMESTAMP_NUM 3
#define OBJECT_NUM 4

using namespace std;

int main () {
	HMODULE hLib = LoadLibraryA("lib.dll");
	if (!hLib) throw GetLastError();

	// Test for exported variable timestamp
	time_t timestamp = (time_t) GetProcAdress(hLib, MAKEINTRESOURCE(TIMESTAMP_NUM));
	cout << "Timestamp: " << timestamp << "\n\n";
	
	// Test for exported function sum
	int (*sum)(int, int);
	sum = (int (*)(int, int)) GetProcAdress(hLib, MAKEINTRESOURCE(SUM_NUM));
	cout << "2 + 5 = " << sum(2, 5) << "\n\n";

	// Test for exported function whoami
	void (*whoami)();
	whoami = (void (*)()) GetProcAdress(hLib, MAKEINTRESOURCE(WHOAMI_NUM));
	cout << "WHOAMI: " << whoami() << "\n\n";

	// Test for exported class MyObject
	MyObject* object = (*MyObject) GetProcAdress(hLib, MAKEINTRESOURCE(OBJECT_NUM));
	cout << "Initial name: " << object->getName() << "\n";
	object->setName("James, Ira, Kun");
	cout << "New name: " << object->getName() << "\n\n";

	FreeLibrary(hLib);
}