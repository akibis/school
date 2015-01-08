/*
File: main.c
Author: Aleksandr Kibis
Date: 9/29/2014

This program mimicks the windows command prompt
*/

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define BUFFER_SIZE 2048

int main()
{
	char* input;
	TCHAR command[BUFFER_SIZE];
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );


	while(1){
		// allocate memory and add cmd preprocessor
		char args[BUFFER_SIZE + 4] = "/c ";
		input = (char*)calloc(BUFFER_SIZE, sizeof(char));

		printf("netdom> ");

		// get user input and concatinate with preprocessor
		fgets(input, BUFFER_SIZE, stdin);
		if (strcmp(input, "exit\n") == 0) {   // exit shell upon keyword
			printf("<3\n");
			exit(EXIT_SUCCESS);
		}
		strcat(args, input);

		//printf("stringcat: %s\n",add);

		// convert args from char* to TCHAR*
		MultiByteToWideChar(CP_UTF8, 0, args, -1, command, BUFFER_SIZE + 4);

		if( !CreateProcess(TEXT("C:\\Windows\\System32\\cmd.exe"),   // Use Windows Command Prompt
			command,        // Pass command line args
			NULL,           // Process handle not inheritable
			NULL,           // Thread handle not inheritable
			FALSE,          // Set handle inheritance to FALSE
			0,              // default flags - Normal Priority
			NULL,           // Use parent's environment block
			NULL,           // Use parent's starting directory 
			&si,            // Pointer to STARTUPINFO structure
			&pi )           // Pointer to PROCESS_INFORMATION structure
			) 
		{
			printf( "CreateProcess failed (%d).\n", GetLastError() );
			exit(EXIT_FAILURE);
		}
		//printf("check\n");
		// Wait until child process exits.
		WaitForSingleObject( pi.hProcess, INFINITE );

		// Close process and thread handles. 
		CloseHandle( pi.hProcess );
		CloseHandle( pi.hThread );

		//printf("you typed: %s\n", input);
		free(input);
	}

	return 0;
}

