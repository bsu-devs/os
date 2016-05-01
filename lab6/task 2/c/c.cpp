#include <stdlib.h>
#include <conio.h>
#include <assert.h>
#include <Windows.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	// reading B's handle & A's pid from environment
	char buffer[200], s[200];
	assert(GetEnvironmentVariable("PID_A", buffer, sizeof(buffer)));
	DWORD aPid = (DWORD) atoi(buffer);
	assert(GetEnvironmentVariable("PHANDLE_B", buffer, sizeof(buffer)));
	HANDLE bHandle = (HANDLE) atoi(buffer);

	// showing welcome notification
	sprintf(s, "C resumed by A, B's Handle = %d, A's PID = %d", bHandle, aPid);
	MessageBox(NULL, TEXT(s), TEXT("Process C"), MB_OK);

	// creating duplicate handler
	HANDLE aHandle = OpenProcess(PROCESS_DUP_HANDLE, FALSE, aPid);
	assert(aHandle);

	HANDLE bHandleDuplicate = 0;
	DuplicateHandle(aHandle, bHandle, GetCurrentProcess(), &bHandleDuplicate, 0, FALSE, DUPLICATE_SAME_ACCESS);
	assert(bHandle);
	assert(bHandleDuplicate);
	assert(bHandle != bHandleDuplicate);

	// terminating process B
	if (TerminateProcess(bHandleDuplicate, 2))
		MessageBox(NULL, TEXT("Process B was terminated"), TEXT("Process C"), MB_OK);	 
	else
		MessageBox(NULL, TEXT("Process B failed to be terminated"), TEXT("Process C"), MB_OK);

	// closing handles to (un)terminated process
	CloseHandle(aHandle);
	CloseHandle(bHandle);
	CloseHandle(bHandleDuplicate);

	printf("\nCheers from Process C! Press any key to kill me!\n");
	getch();
	return 0;
}