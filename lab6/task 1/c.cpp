#include <stdlib.h>
#include <conio.h>
#include <assert.h>
#include <Windows.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	// reading B's handle & pid from environment
	char buffer[200];
	assert(GetEnvironmentVariable("PID_B", buffer, sizeof(buffer)));
	DWORD bPid = (DWORD) atoi(buffer);
	assert(GetEnvironmentVariable("PHANDLE_B", buffer, sizeof(buffer)));
	HANDLE bHandle = (HANDLE) atoi(buffer);

	// showing welcome notification
	sprintf(s, "C resumed by A, B's Handle = %d, B's PID = %d", bHandle, bPid);
	MessageBox(NULL, TEXT(s), TEXT("Process C"), MB_OK);

	// creating duplicate handler
	HANDLE bHandleDuplicate = OpenProcess(PROCESS_DUP_HANDLE, FALSE, bPid);
	assert(bHandleDuplicate);
	assert(bHandleDuplicate != bHandle);

	// terminating process B
	if (TerminateProcess(bHandleDuplicate, 2))
		MessageBox(NULL, TEXT("Inherited Process B was terminated"), TEXT("Process C"), MB_OK);	 
	else
		MessageBox(NULL, TEXT("Process B failed to be terminated"), TEXT("Process C"), MB_OK);

	// closing handles to (un)terminated process
	CloseHandle(bHandle);
	CloseHandle(bHandleDuplicate);

	printf("\nCheers from Process C! Press any key to kill me!\n");
	getch();
	return 0;
}