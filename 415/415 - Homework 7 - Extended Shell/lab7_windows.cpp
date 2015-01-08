#include <stdio.h>
#include <string.h>
#include <windows.h>

int main() {
	char buffer[2048];
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	while (1) {
		printf("My Shell>");
		fgets(buffer, 2048, stdin);
		// Check that it is not exit command
		if (buffer[0] == 'e' && buffer[1] == 'x' && buffer[2] == 'i' && buffer[3] == 't' &&
			buffer[4] == '\n' && buffer[5] == 0) {
			break;
		}

		// the last character will be '\n' and we need to erase it before launching the command
		buffer[strlen(buffer) - 1] = 0;

		PROCESS_INFORMATION pi;
		ZeroMemory(&pi, sizeof(pi));
		PROCESS_INFORMATION pi1;
		ZeroMemory(&pi1, sizeof(pi1));

		STARTUPINFO si;
		STARTUPINFO si1;
		ZeroMemory(&si, sizeof(si));
		ZeroMemory(&si1, sizeof(si1));
		si.cb = sizeof(si);
		si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
		si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
		si1.cb = sizeof(si1);
		si1.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		si1.hStdError = GetStdHandle(STD_ERROR_HANDLE);
		si1.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
		int cnt = 0;
		char* ptr;
		HANDLE hfile = INVALID_HANDLE_VALUE;
		HANDLE pipe_r, pipe_w;
		if (strstr(buffer, " > ")) {
			ptr = strstr(buffer, " > ");
			char* filename = ptr + 3;
			hfile = CreateFile(filename,                // name of the file
				GENERIC_WRITE,          // open for writing
				0,                      // do not share
				&sa,                   // default security
				CREATE_ALWAYS,             // open and file always
				FILE_ATTRIBUTE_NORMAL,  // normal file
				NULL);                  // no attr. template
			if (hfile == INVALID_HANDLE_VALUE) {
				printf("Cannot open the output file\n");
				continue;
			}
			si.hStdOutput = hfile;
			cnt++;
			*ptr = 0;
		}

		if (strstr(buffer, " >> ")) {
			ptr = strstr(buffer, " >> ");
			char* filename = ptr + 4;
			hfile = CreateFile(filename,                // name of the file
				FILE_APPEND_DATA,          // open for writing
				0,                      // do not share
				&sa,                   // default security
				OPEN_ALWAYS,             // open and file always
				FILE_ATTRIBUTE_NORMAL,  // normal file
				NULL);                  // no attr. template
			if (hfile == INVALID_HANDLE_VALUE) {
				printf("Cannot open the output file\n");
				continue;
			}
			si.hStdOutput = hfile;
			cnt++;
			*ptr = 0;
		}

		if (strstr(buffer, " 2> ")) {
			ptr = strstr(buffer, " 2> ");
			char* filename = ptr + 4;
			hfile = CreateFile(filename,                // name of the file
				GENERIC_WRITE,          // open for writing
				0,                      // do not share
				&sa,                   // default security
				CREATE_ALWAYS,             // open and file always
				FILE_ATTRIBUTE_NORMAL,  // normal file
				NULL);                  // no attr. template
			if (hfile == INVALID_HANDLE_VALUE) {
				printf("Cannot open the output file\n");
				continue;
			}
			si.hStdError = hfile;
			cnt++;
			*ptr = 0;
		}

		if (strstr(buffer, " 2>> ")) {
			ptr = strstr(buffer, " 2>> ");
			char* filename = ptr + 5;
			hfile = CreateFile(filename,                // name of the file
				FILE_APPEND_DATA,          // open for writing
				0,                      // do not share
				&sa,                   // default security
				OPEN_ALWAYS,             // open and file always
				FILE_ATTRIBUTE_NORMAL,  // normal file
				NULL);                  // no attr. template
			if (hfile == INVALID_HANDLE_VALUE) {
				printf("Cannot open the output file\n");
				continue;
			}
			si.hStdError = hfile;
			cnt++;
			*ptr = 0;
		}

		if (strstr(buffer, " < ")) {
			ptr = strstr(buffer, " < ");
			char* filename = ptr + 3;
			hfile = CreateFile(filename,                // name of the file
				GENERIC_READ,          // open for read
				0,                      // do not share
				&sa,                   // default security
				OPEN_EXISTING,             // open existing file only
				FILE_ATTRIBUTE_NORMAL,  // normal file
				NULL);                  // no attr. template
			if (hfile == INVALID_HANDLE_VALUE) {
				printf("Cannot open the input file\n");
				continue;
			}
			si.hStdInput = hfile;
			cnt++;
			*ptr = 0;
		}
		int second_process_created = 0;
		char* process2_name;
		if (strstr(buffer, " | ")) {
			CreatePipe(&pipe_r, &pipe_w, &sa, 0);
			si.hStdOutput = pipe_w;
			si1.hStdInput = pipe_r;
			ptr = strstr(buffer, " | ");
			process2_name = ptr + 3;
			cnt++;
			*ptr = 0;
			second_process_created = 1;
		}

		int run_background = 0;
		if (strstr(buffer, "&")) {
			ptr = strstr(buffer, "&");
			cnt++;
			*ptr = 0;
			run_background = 1;
		}

		if (cnt > 1) {
			printf("Combinations of several special characters are not supported, try again.\n");
			continue;
		}

		if (cnt == 1) {
			si.dwFlags = STARTF_USESTDHANDLES;
			si1.dwFlags = STARTF_USESTDHANDLES;
		}

		// Start the child process. 
		if (!CreateProcess(NULL,   // No module name (use command line)
			buffer,        // Command line
			NULL,           // Process handle not inheritable
			NULL,           // Thread handle not inheritable
			TRUE,          // Set handle inheritance to TRUE
			0,              // No creation flags
			NULL,           // Use parent's environment block
			NULL,           // Use parent's starting directory 
			&si,            // Pointer to STARTUPINFO structure
			&pi)           // Pointer to PROCESS_INFORMATION structure
			)
		{
			printf("CreateProcess failed (%d).\n", GetLastError());
		}
		// Wait until child process exits if '&' is not in the end of the string.
		if (!run_background) {
			WaitForSingleObject(pi.hProcess, INFINITE);
			if (second_process_created) {
				// Start the child process. 
				if (!CreateProcess(NULL,   // No module name (use command line)
					process2_name,        // Command line
					NULL,           // Process handle not inheritable
					NULL,           // Thread handle not inheritable
					TRUE,          // Set handle inheritance to TRUE
					0,              // No creation flags
					NULL,           // Use parent's environment block
					NULL,           // Use parent's starting directory 
					&si1,            // Pointer to STARTUPINFO structure
					&pi1)           // Pointer to PROCESS_INFORMATION structure
					)
				{
					printf("CreateProcess failed (%d).\n", GetLastError());
					continue;
				}
				WaitForSingleObject(pi1.hProcess, INFINITE);
			}
		}

		// Close process handle. We can do it since Closehandle does not terminate the process
		CloseHandle(pi.hProcess);

		if (second_process_created) {
			CloseHandle(pi1.hProcess);
			CloseHandle(pipe_r);
			CloseHandle(pipe_w);
		}

		if (hfile != INVALID_HANDLE_VALUE) {
			CloseHandle(hfile);
		}
	}

	return 0;
}