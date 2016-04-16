#include <iostream>
#include <Windows.h>
#include <string>
#include "../lib/lib.h" 

using namespace std;

int main () {
	wstring wstr;
	wcin >> sharedString;
	// wcsncpy_s(sharedStringPtr, 100, wstr.c_str(), 100);
	PostMessage(HWND_BROADCAST, WM_COMMAND, (WPARAM)123, (LPARAM)456);
}