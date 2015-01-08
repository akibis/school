/* 
* File:   wordCounter.c
* Author: Aleksandr Kibis
*
* Multi-threaded word count application. Used clock() instead of time()
* because it provides more accurate data.
* 
* Compile: cl -o wordCount wordCounter.c
* 
* Run: wordCount.exe <text file>
* 
* Created on October 3, 2014, 6:53 PM
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define BUFFER_SIZE 1024 * 80
#define THREAD_COUNT 8

int getFile(char* file);
DWORD WINAPI counter(void *attributes);

// specifies data range to work on for each thread

struct threadAttr {
	int begin;
	int end;
	int id;
};

char* text;
int* countArray;
int wordCount;

/*
* 
*/
int main(int argc, char** argv) {

	int fileSize;
	int chunkSize;

	HANDLE threadArray[THREAD_COUNT];
	DWORD threadIdArray[THREAD_COUNT];
	struct threadAttr *input;

	int i;
	int offset = 0;

	if (argv[1] == NULL) {
		printf("Usage: ./wordCount <text file>\n");
		exit(EXIT_FAILURE);
	}

	countArray = (int*)malloc(THREAD_COUNT * sizeof (int));
	text = (char*)malloc(BUFFER_SIZE * sizeof (char));

	// write input file to global memory

	fileSize = getFile(argv[1]);
	//printf("File size: %d\n", fileSize);

	// exit if write to buffer is unsuccessful
	if (fileSize < 0) {
		free(text);
		return (EXIT_FAILURE);
	}
	// count number of words
	else {

		// split data into evenly size chunks
		chunkSize = fileSize / THREAD_COUNT;
		//printf("Split check: %c\n", text[chunkSize]);

		// create threads and run word count on each chunk


		// thread initialization

		for (i = 0; i < THREAD_COUNT; i++) {
			// each thread must have it's own struct so that data won't be overwritten
			input = (struct threadAttr*)malloc(sizeof (struct threadAttr));
			(*input).begin = i * chunkSize;
			if (i == THREAD_COUNT - 1)
				(*input).end = fileSize;
			else
				(*input).end = i * chunkSize + chunkSize;
			(*input).id = i;
			//retval = pthread_create(&threadArray[i], &pta, counter, (void*) input);
			threadArray[i] = CreateThread(NULL, 0, counter, input, 0, &threadIdArray[i]);
		}

		// wait for all threads to finish
		for (i = 0; i < THREAD_COUNT; i++) {
			//pthread_join(threadArray[i], NULL);
			WaitForSingleObject(threadArray[i], INFINITE);

		}

		// ITERATIVE IMPLEMENTATION

		//        int wordCount = 0;
		//        
		//        for (i = 0; i < fileSize; i++){
		//            // space char is delimiter
		//            if((int)text[i] == 32)
		//                wordCount++;
		//            
		//            // first word exception
		//            if((int)text[i] > 64 && (int)text[i] < 91 && (int)text[i-1] != 32)
		//                wordCount++;
		//        }
		//        countArray[0] = wordCount;
		//        printf("Word Count: %d\n", countArray[0]);

		printf("Number of Words: %d\n", wordCount);
		free(input);
		free(text);
		return (EXIT_SUCCESS);

	}


}

int getFile(char* file) {
	int count = 0;
	size_t readCount;
	FILE *fd;
	int ch;

	//printf("Input file name: %s\n", file);


	fd = fopen("text", "r");
	while (1) {
		ch = fgetc(fd);
		if (ch == EOF)
			break;
		++count;
	}
	rewind(fd);
	//printf("Number of chars in file: %d\n", count);


	readCount = fread(text, 1, count, fd);
	fclose(fd);

	if (count == (int) readCount) {
		        //printf("Read file into buffer: SUCCESS\n");
		        //printf("************************************************\n");
		//printf("%s\n", text);
		return count;
	} else {
		printf("Buffer read error. Exiting.\n");
		return -1;
	}

	//printf("Chars read: %d\n", (int)readCount);



}

DWORD WINAPI counter(void *attributes) {
	int localCount = 0;
	HANDLE mutex;
	struct threadAttr *newOne;
	int begin;
	int end;
	int id;
	int i;

	newOne = (struct threadAttr*) attributes;

	// assign struct values to new vars for cleaner code
	begin = (*newOne).begin;
	end = (*newOne).end;
	id = (*newOne).id;

	// if start of chunk is not a space or capital letter, increment starting point
	while ((int) text[begin] != 32) {
		if ((int) text[begin] > 64 && (int) text[begin] < 91)
			break;
		else {
			begin++;
		}
	}
	//printf("Thread Id: %d\tStart: %d\tEnd: %d\n", id, begin, end);
	for (i = begin; i <= end; i++) {
		// space char is delimiter
		if ((int) text[i] == 32)
			localCount++;

		// first word exception
		if ((int) text[i] > 64 && (int) text[i] < 91 && (int) text[i - 1] != 32)
			localCount++;
	}

	// use mutex lock before adding local count to global variable    
	mutex = CreateMutex(NULL, FALSE, NULL);
	WaitForSingleObject(mutex, INFINITE);
	wordCount += localCount;
	ReleaseMutex(mutex);
	CloseHandle(mutex);

	return 0;
}

