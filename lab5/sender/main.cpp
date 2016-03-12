#include <iostream>
#include <Windows.h>
#include <string>
#include "./lib/lib.h" 

using namespace std;

int main () {
	wstring str;
	wcin >> str;
	WCHAR* str = str.c_str();
	sharedString = str;
	PostMessage(receiver, WM_COMMAND, (WPARAM)123, (LPARAM)456);
}