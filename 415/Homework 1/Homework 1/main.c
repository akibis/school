/**
File: main.c
Author: Aleksandr Kibis
Date: 9/1/2014

This program uses a high level system call to write a string to console on a 
Windows-based system.
**/

#include <windows.h>
#include <stdio.h>


#define NAME "Aleksandr Kibis"
int main(){
	char buf[50]; // create array to hold string
	int n; // number of bytes written to buffer
	DWORD bytesWritten; // number of bytes written by WriteFile function
	HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE); // get standard output handle

	n = sprintf(buf, "Hello %s, welcome to 415!\n", NAME);
	
	WriteFile(stdOut, buf, n, &bytesWritten, NULL);

	return 0;
}