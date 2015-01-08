/* 
 * File:   pageReplacement.c
 * Author: Aleksandr Kibis
 *
 * Compile: gcc -o run pageReplacement.c
 * Run: ./run
 * 
 * Created on November 9, 2014, 2:54 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define NUMBER_OF_PAGES 16
#define NUMBER_OF_REFERENCES 100

int runFIFO(int numFrames);
int runLRU(int numFrames);

int inQueue(int numFrames, int searchIndex);
void rearrange(int numFrames, int newRef);
void rearrangeNewest(int numFrames, int existingRef);
void printFrames(int numFrames);
void printRefs();

void pageGen(); // last index = newest
int randomNumber(); // kernel-based randomization

int* pageQueue;
int* frameQueue;

/*
 *  This program generates 1 random string of page references. Then runs
 *  FIFO and LRU page replacement algorithms on the string with frame sizes
 *  1 to numFrames (Default is 16).
 * 
 *  Prints out number of faults after each calculation.
 */
int main(int argc, char** argv) {
    
    int numFrames = 16;
    int FIFO, LRU, i;
    
    // Get random string of references
    pageGen();
    printRefs();
    
    // Run FIFO tests
    printf("FIFO page-replacement results:\n");
    printf("Frame Buf Size\tFIFO\tLRU\n");
    for (i=1; i <= numFrames; i++){
        FIFO = runFIFO(i);
        LRU = runLRU(i);
        printf("%d\t\t%d\t%d\n", i, FIFO, LRU);
    }
    
    // Run LRU tests
//    printf("\n\nLRU page-replacement results:\n");
//    printf("Frame Buf Size\tFaults\n");
//    for (i=1; i <= numFrames; i++){
//        numberOfFaults = runLRU(i);
//        printf("%d\t\t%d\n", i, numberOfFaults);
//    }    
    


    free(pageQueue);
    free(frameQueue);

    return (EXIT_SUCCESS);
}

// Creates random numbers between 1 and NUMBER_OF_PAGES. 
// Returns single random number.

int randomNumber() {

    int number;
    srand((long)fopen("/dev/urandom", "r"));
    number = 1 + rand() % NUMBER_OF_PAGES;
    //printf("Random number: %d\n", number);

    return number;
}

// Creates array of random page references. Consecutive references are unique.

void pageGen() {

    pageQueue = malloc(NUMBER_OF_REFERENCES * sizeof (int));

    int i, number;
    for (i = 0; i < NUMBER_OF_REFERENCES; i++) {
        if (i == 0)
            pageQueue[i] = randomNumber();
        else {
            // keep getting new number while consecutive numbers are equal
            while (pageQueue[i - 1] == (number = randomNumber()))
                number = randomNumber();
            pageQueue[i] = number;
        }
        //printf("pageQueue[%d] = %d\n", i, pageQueue[i]);
    }
}

// First-In First-Out page replacement algorithm

int runFIFO(int numFrames) {
    int numFaults = 0;

    frameQueue = malloc(numFrames * sizeof (int));

    //printRefs();
    
    // run the rest of the replacement algo
    int i;
    for (i = 0; i < NUMBER_OF_REFERENCES; i++) {
        if ((inQueue(numFrames, pageQueue[i])) >= 0) {
            //do nothing
        } else {
            numFaults++;
            rearrange(numFrames, pageQueue[i]);
        }
        //printFrames(numFrames);
    }
    //printf("i: %d\n", i);

    return numFaults;
}

// Least-Recently-Used page replacement algorithm

int runLRU(int numFrames) {
    int numFaults = 0;
    int recentIndex;

    frameQueue = malloc(numFrames * sizeof (int));

    //printRefs();
    
    int i;
    for (i = 0; i < NUMBER_OF_REFERENCES; i++) {
        // move most recently used item to the top
        recentIndex = inQueue(numFrames, pageQueue[i]);
        if (recentIndex >= 0) {
            //printf("recent index: %d\n", recentIndex);
           rearrangeNewest(numFrames, recentIndex);
        } else {
            numFaults++;
            rearrange(numFrames, pageQueue[i]);
        }
        //printFrames(numFrames);
    }


    return numFaults;
}



// Checks whether reference exists in frameQueue.
// Returns index if yes, -1 if no.

int inQueue(int numFrames, int searchIndex) {
    int i;
    for (i = 0; i < numFrames; i++) {
        if (frameQueue[i] == searchIndex){
            //printf("return index: %d\n", i);
            return i;
        }
    }
    return -1;
}

// Erase oldest page reference, move up all other refs, add newest on top

void rearrange(int numFrames, int newRef) {
    int i;
    for (i = 0; i < numFrames; i++) {
        if (i + 1 == numFrames)
            frameQueue[i] = newRef;
        else
            frameQueue[i] = frameQueue[i + 1];

    }
}

// If existing index is used in LRU, move to top

void rearrangeNewest(int numFrames, int existingRef) {
    int i;
    // hold newest used frame
    int newestFrame = frameQueue[existingRef];

    //printf("Newest Frame: %d\t Index: %d\n", newestFrame, existingRef);
    
    // move up all items to existing reference
    for (i = existingRef; i < numFrames; i++) {
        if (i + 1 == numFrames) {
        }// do nothing
        else
            frameQueue[i] = frameQueue[i + 1];
    }
    // add most recently used to top of queue
    frameQueue[numFrames - 1] = newestFrame;
    //printFrames(numFrames);
}

void printFrames(int numFrames){
    int i;
    printf("{");
    for (i=0; i < numFrames; i++){
        if (i == numFrames - 1)
            printf("%d", frameQueue[i]);
        else            
            printf("%d, ", frameQueue[i]);
    }
    printf("}\n");
}

void printRefs(){
    int i;
    printf("\nRandomly Generated String of References:\n{");
    for (i=0; i < NUMBER_OF_REFERENCES; i++){
        if (i == NUMBER_OF_REFERENCES - 1)
            printf("%d", pageQueue[i]);
        else            
            printf("%d, ", pageQueue[i]);
    }
    printf("}\n\n");
}