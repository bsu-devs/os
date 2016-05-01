#include <stdlib.h>
#include <conio.h>
#include <assert.h>
#include <Windows.h>
#include <stdio.h>

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	STARTUPINFO si = { sizeof(si) };
	SECURITY_ATTRIBUTES saProcess, saThread;
	PROCESS_INFORMATION piProcessB, piProcessC;
	TCHAR commandLine[MAX_PATH];

	saProcess.nLength = sizeof(saProcess);
	saProcess.lpSecurityDescriptor = NULL;
	saProcess.bInheritHandle = FALSE;

	saThread.nLength = sizeof(saThread);
	saThread.lpSecurityDescriptor = NULL;
	saThread.bInheritHandle =FALSE;

	/**
	* @description Spawn Process B.
	* 
	* The handle returned by the CreateProcess function 
	* always  has PROCESS_ALL_ACCESS access to the process object.
	* 
	* The current directory specified by the lpcurrentDirectory parameter.
	* is the current directory for the child process.
	* 
	* The current directory specified in item 2 under the lpCommandLine parameter
	* is the current directory for the parent process.
	*/

	// copying the name of a process
	lstrcpy(commandLine, TEXT("b"));

	/**
	 * @parameter app name
	 * @parameter a line which will be executed from cmd and will create a process
	 * @parameter process security attributes
	 * @parameter thread security attributes
	 * @parameter allow/disallow a new handle to inherit all inheritable handles from the parent process
	 * @parameter creation mode: priority , suspended, er. mode, detached console. 0 = NORMAL_PRIORITY_CLASS.
	 * @parameter environment. NULL = the same as in parent process
	 * @parameter current directory
	 * @parameter pointer to startup info
	 * @parameter pointer to process information
	 */
	BOOL bCreated = CreateProcess(NULL, commandLine, &saProcess, &saThread,
	 	FALSE, 0, NULL, NULL, &si, &piProcessB);

	if (!bCreated) {
		MessageBox(NULL, TEXT("Creation of process B failed"), TEXT("Process A"), MB_OK);
		return 0;
	}

	/**
	 * @description The pi structure contains two handles  relative to Process A:
	 * > pi.hProcess, which identifies Process B's process object and is  inheritable; 
	 * > pi.hThread,  which identifies Process B's primary thread object and is NOT inheritable.
	 */
	CloseHandle(piProcessB.hThread);

	/**
	 * @description Prepare to spawn Process C from Process A.
	 *
	 * Since NULL is passed for the psaProcess and psaThread
	 * parameters, the handles to Process C's process and 
	 * primary thread objects default to "noninheritable."
	 *
	 * If Process A were to spawn another process, this new 
	 * process would NOT inherit handles to Process C's process 
	 * and thread objects.
	 *
	 * Because TRUE is passed for the bInheritHandles parameter,
	 * Process C will inherit all inheritable handles from A that is B's process handle.
	 *
	 * A has piProcessB.hProcess and B's pid be handled in C through the environment
	 */

	lstrcpy(commandLine, TEXT("c"));
	
	DWORD pId = GetCurrentProcessId();
	char s1[100], s2[100];
	sprintf(s1, "%d", pId);
	sprintf(s2, "%d", piProcessB.hProcess);
	if (!SetEnvironmentVariable("PID_A", s1) 
			|| !SetEnvironmentVariable("PHANDLE_B", s2)) {
		MessageBox(NULL, TEXT("Failed to set Environment variables"), TEXT("Process A"), MB_OK);
		return 1;
	}

	/**
	 * @description From MSDN: CREATE_SUSPENDED - The primary thread of the new 
	 * process is created in a suspended state, and does not run until the 
	 * ResumeThread function is called.
	 */
	BOOL cCreated = CreateProcess(NULL, commandLine, NULL, NULL, TRUE, 
		NORMAL_PRIORITY_CLASS | CREATE_SUSPENDED, NULL, NULL, &si, &piProcessC);

	if (!cCreated) {
		MessageBox(NULL, TEXT("Creation of process C failed"), TEXT("Process A"), MB_OK);
		return 0;
	}

	MessageBox(NULL, TEXT("Process C will be resumed in 2 secs"), TEXT("Process A"), MB_OK);
	Sleep(2000);

	if (!ResumeThread(piProcessC.hThread)) {
		MessageBox(NULL, TEXT("Process C failed to resume"), TEXT("Process A"), MB_OK);
		return 0;
	}

 	if (WAIT_FAILED == WaitForSingleObject(piProcessB.hProcess, INFINITE))
 		MessageBox(NULL, TEXT("WAIT_FAILED for Process B"), TEXT("Process A"), MB_OK);

 	if (WAIT_FAILED == WaitForSingleObject(piProcessC.hProcess, INFINITE))
 		MessageBox(NULL, TEXT("WAIT_FAILED for Process C"), TEXT("Process A"), MB_OK);

	CloseHandle(piProcessB.hProcess);
	CloseHandle(piProcessC.hProcess);
	CloseHandle(piProcessC.hThread);
	
	MessageBox(NULL, TEXT("Process A finished"), TEXT("Process A"), MB_OK);

	return 0;
}