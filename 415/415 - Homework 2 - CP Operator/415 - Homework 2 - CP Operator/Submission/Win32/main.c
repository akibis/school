/*
@File: main.c
@Author: Aleksandr Kibis
@Date: 9/15/2014

This is a windows implementation of a copy operator. Given 1 or two text documents, this 
program copies the first document under the name of the second. The number of bytes read is returned.
*/

#include <stdio.h>
#include <Windows.h>
#include <strsafe.h>

#pragma comment(lib,"user32.lib");

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define BUF_SIZE 256

void getError(LPTSTR lpszFunction);

int main(int argc, char* argv[]) {

	// input and file handlers
	char* inputFile;
	char* copiedFile;
	char* buf;
	HANDLE input;
	HANDLE output;

	// read/write counters
	int nbytes;
	DWORD bytes_read;
	DWORD bytes_written;
	int readReturn;
	int writeReturn;
	int totalBytes = 0;

	if (argc == 3) {       
		inputFile = argv[1];
		copiedFile = argv[2];

		//printf("inputFile: %s\n", inputFile);
		//printf("copiedFile: %s\n", copiedFile);

		// OPEN FILE TO BE COPIED
		input = CreateFile(inputFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		//printf("input: %d\n", (int)input);

		//getError(TEXT("GetProcessId"));


		// OPEN DESTINATION FILE, CREATE IF DOESN'T EXIST
		output = CreateFile(copiedFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		buf = (char*)malloc(BUF_SIZE * sizeof (char));       

		//getError(TEXT("GetProcessId"));

		// COPY FILE TEXT

		while (1) {
			nbytes = BUF_SIZE;
			readReturn = ReadFile(input, buf, nbytes, &bytes_read, NULL);
			//getError(TEXT("GetProcessId"));
			totalBytes += bytes_read;
			//printf("Check: %d\n", bytes_read);
			if (bytes_read < BUF_SIZE) {
				writeReturn = WriteFile(output, buf, bytes_read, &bytes_written, NULL);
				break;
			}
			//printf("chunkSize: %d\n", bytes_read);
			writeReturn = WriteFile(output, buf, nbytes, &bytes_written, NULL);
			//printf("%s", buf);

		}
		// PRINT TOTAL BYTES COPIED
		printf("copied %d bytes\n", totalBytes);

		// COMPARE THE TWO FILES


		// FREE RESOURCES
		memset(buf, 0, sizeof(char));
		free(buf);
		CloseHandle(input);
		CloseHandle(output);
		fflush(stdin);
		fflush(stdout);

		exit(EXIT_SUCCESS);
	} else {
		fprintf(stderr, "Please enter two arguments.\n");
		exit(EXIT_FAILURE);
	}


	//return (EXIT_SUCCESS);
}

// implementation of a getError function. Code borrowed from: 
// http://msdn.microsoft.com/en-us/library/windows/desktop/ms680582(v=vs.85).aspx
void getError(LPTSTR lpszFunction) {
	DWORD error = GetLastError();
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0, NULL );

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
	StringCchPrintf((LPTSTR)lpDisplayBuf, 
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"), 
		lpszFunction, error, lpMsgBuf); 
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}