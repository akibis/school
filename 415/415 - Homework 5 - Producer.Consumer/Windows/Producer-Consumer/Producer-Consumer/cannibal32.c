/*
* File:		cannibal32.c
* Author:	Aleksandr Kibis
* Date:		10/28/2014
*
* Compile:  cl -o run cannibal32.c
* Run:		run.exe <int bufSize> <int # prods> <int # cons> <int items/prod>
*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

static int index = 0;

int threadCount, bufSize, itemsPerProducer, producerCount, consumerCount;
int* buf;

HANDLE lock, empty, full;
HANDLE prods[4];
HANDLE cons[4];

DWORD WINAPI producer(LPVOID id);
DWORD WINAPI consumer(LPVOID id);

struct threadAttr {
    int id;
};

/*
 * 
 */
int main(int argc, char** argv) {

    int i;
    struct threadAttr *producers;
    struct threadAttr *consumers;
	DWORD threadID;

    // exit if incorrect usage
    if (argc != 5){
        printf("Usage: ./run <buf size> <# of producers> <# of consumers> <items/producer>\n");
        exit(EXIT_FAILURE);
    }

    // grab command line args
    bufSize = atoi(argv[1]);
    producerCount = atoi(argv[2]);
    consumerCount = atoi(argv[3]);
    itemsPerProducer = atoi(argv[4]);
    threadCount = producerCount;

    // print line args
    printf("Buffer Size: %d\n"
            "Number of Producers: %d\n"
            "Number of Consumers: %d\n"
            "Items Per Producer: %d\n",
            bufSize, producerCount, consumerCount, itemsPerProducer);

    // init buffer
    buf = (int*)malloc(bufSize * sizeof(int));

    // init sync objects
	empty = CreateSemaphore(NULL, bufSize, bufSize, NULL);
	full = CreateSemaphore(NULL, 0, bufSize, NULL);
	lock = CreateMutex(NULL, FALSE, NULL);


    // create threads
	
    for (i = 0; i < producerCount; i++) {
    producers = (struct threadAttr*)malloc(sizeof (struct threadAttr));    
        (*producers).id = i;
		//printf("i: %d\n", (*producers).id);
		prods[i] = CreateThread(NULL, 0, producer, producers, 0, &threadID);
        //printf("Producer Thread %d\n", i);
    }
	
    for (i = 0; i < consumerCount; i++) {
    consumers = (struct threadAttr*)malloc(sizeof (struct threadAttr));    
        (*consumers).id = i;
		cons[i] = CreateThread(NULL, 0, consumer, consumers, 0, &threadID);
        //printf("Consumer Thread %d\n", i);
    }


    // wait for threads

    for (i = 0; i < producerCount; i++) {
        //printf("Wait Producer %d\n", i);
		WaitForSingleObject(prods[i], INFINITE);
        //printf("Producer Joined %d\n", i);
    }

    for (i = 0; i < consumerCount; i++) {
        //printf("Wait Consumer %d\n", i);
		WaitForSingleObject(cons[i], INFINITE);
        //printf("Consumer Joined %d\n", i);
    }

    // exit 
    printf("\n\nAll tasks complete. Goodbye.\n");

    // free memory
	CloseHandle(lock);
    free(buf);

    return (EXIT_SUCCESS);
}

// produces items and fills buffer
DWORD WINAPI producer(LPVOID threadAttr) {
    int itemsProduced = 0;
    int item;
	int id;
	
    struct threadAttr *prodAttr;
	prodAttr = (struct threadAttr*) threadAttr;
    
	id = (*prodAttr).id;
	//printf("ID: %d\n", id);
    while (1) {

        // enter synchronized state
        WaitForSingleObject(empty, INFINITE);
        WaitForSingleObject(lock, INFINITE);

        if (index < bufSize) {
            // create unique item number based on thread, id, and iteration
            item = itemsProduced * threadCount + id;
            // write to buffer
            buf[index] = item;
            if (index > bufSize) {
                //printf("Error\n");
                break;
            }
            index++;
            itemsProduced++;
        }
        ReleaseMutex(lock);
        ReleaseSemaphore(full, 1, NULL);

        if (itemsProduced == 1000) {
            //printf("Max reached.\n");
            break;
        }
//        if (id == 3){
//            printf("item: %d\n", item);
//        }
    }
    return EXIT_SUCCESS;
}

// consumes items within the buffer
DWORD WINAPI consumer(LPVOID threadAttr) {
    int itemsConsumed = 0;
    int item;
	int id;
    struct threadAttr *consAttr;
	consAttr = (struct threadAttr*) threadAttr;
    // get thread id
    id = (*consAttr).id;



    // loop until all items have been consumed
    while (1) {
        WaitForSingleObject(full, INFINITE);
        WaitForSingleObject(lock, INFINITE);


        // gobble item
        item = buf[index - 1];
        printf("Consumer #%d consumed item #%d\n", id, item);
        index--;
        itemsConsumed++;
        //printf("Consumer: %d\titemsConsumed: %d\n", id, itemsConsumed);
        if (index < 0) {
           //printf("Error in Consumer\n");
            break;
		}

        ReleaseMutex(lock);
        ReleaseSemaphore(empty, 1, NULL);

        if (itemsConsumed == 1000) {
            //printf("Consumer %d: All items consumed.\n", id);
            break;
        }
    }
    return EXIT_SUCCESS;
}


