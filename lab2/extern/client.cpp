#include <Windows.h>
#include <iostream>
#include <ctime>

class IMyObject {
public:
	virtual char* getName() = 0;
	virtual void setName(const char*&) = 0;
};

using namespace std;

int main() {
	HMODULE hLib = LoadLibraryA("../Debug/extern.dll");
	//HMODULE hLib = LoadLibraryA("../Debug/pragma_linker.dll");
	if (!hLib) throw GetLastError();

	// Test for exported variable timestamp
	time_t timestamp = (time_t)GetProcAddress(hLib, "timestamp");
	cout << "Timestamp: " << timestamp << "\n\n";

	// Test for exported function sum
	int(*sum)(int, int);
	sum = (int(*)(int, int)) GetProcAddress(hLib, "sum");
	cout << "2 + 5 = " << sum(2, 5) << "\n\n";

	// Test for exported function whoami
	char*(*whoami)();
	whoami = (char*(*)()) GetProcAddress(hLib, "whoami");
	cout << "WHOAMI: " << whoami() << "\n\n";

	// Test for exported class MyObject
	IMyObject*(*createObject)(const char*&);
	createObject = (IMyObject*(*)(const char*&)) GetProcAddress(hLib, "createObject");
	const char *shit = "shit";
	IMyObject* object = createObject(shit);
	cout << "Initial name: " << object->getName() << "\n";
	const char* name = "James, Ira, Kun";
	object->setName(name);
	cout << "New name: " << object->getName() << "\n\n";

	FreeLibrary(hLib);
	system("pause");
}
