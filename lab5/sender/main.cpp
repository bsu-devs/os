#include <iostream>
#include <Windows.h>
#include <string>
#include "../lib/lib.h" 

using namespace std;

int main () {
	cin >> str;
	PostMessage(HWND_BROADCAST, WM_COMMAND, (WPARAM)123, (LPARAM)456);
}