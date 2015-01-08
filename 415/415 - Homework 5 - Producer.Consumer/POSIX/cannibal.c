/* 
 * File:    cannibal.c
 * Author:  Aleksandr Kibis
 * Date:    10/26/2014
 *
 * Compile: gcc -o run cannibal.c -lpthread
 * Run:     ./run <int bufSize> <int numProducers> <int numConsumers> <int itemsPerProducer>
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int threadCount, bufSize, itemsPerProducer;
static int index = 0;
int* buf;
sem_t empty;
sem_t full;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* producer(void* id);
void* consumer(void* id);

struct threadAttr {
    int id;
};

/*
 * 
 */
int main(int argc, char** argv) {
    
    clock_t t1, t2;
    
    t1 = clock();

    // exit if incorrect usage
    if (argc != 5){
        printf("Usage: ./run <buf size> <# of producers> <# of consumers> <items/producer>\n");
        exit(EXIT_FAILURE);
    }

    // grab command line args
    bufSize = atoi(argv[1]);
    int producerCount = atoi(argv[2]);
    int consumerCount = atoi(argv[3]);
    itemsPerProducer = atoi(argv[4]);
    threadCount = producerCount;

    // print line args
    printf("Buffer Size: %d\n"
            "Number of Producers: %d\n"
            "Number of Consumers: %d\n"
            "Items Per Producer: %d\n",
            bufSize, producerCount, consumerCount, itemsPerProducer);

    // init buffer
    buf = malloc(bufSize * sizeof (int));

    // init sync objects
    sem_init(&empty, 0, bufSize);
    sem_init(&full, 0, 0);

    // create threads
    int i, retval;
    pthread_attr_t pta;
    pthread_attr_init(&pta);
    pthread_t prods[producerCount];
    pthread_t cons[consumerCount];
    struct threadAttr *producers;
    struct threadAttr *consumers;

    for (i = 0; i < producerCount; i++) {
        producers = malloc(sizeof (struct threadAttr));
        (*producers).id = i;
        retval = pthread_create(&prods[i], &pta, producer, (void*) producers);
        //printf("Producer Thread %d\n", i);
        if (retval < 0) {
            printf("Error in creating producer thread.\n");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < consumerCount; i++) {
        consumers = malloc(sizeof (struct threadAttr));
        (*consumers).id = i;
        retval = pthread_create(&cons[i], &pta, consumer, (void*) consumers);
        //printf("Consumer Thread %d\n", i);
        if (retval < 0) {
            printf("Error in creating consumer thread.\n");
            exit(EXIT_FAILURE);
        }
    }


    // wait for threads

    for (i = 0; i < producerCount; i++) {
        //printf("Wait Producer %d\n", i);
        retval = pthread_join(prods[i], NULL);
        //printf("Producer Joined %d\n", i);
        if (retval < 0) {
            printf("Error in joining producer thread.");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < consumerCount; i++) {
        //printf("Wait Consumer %d\n", i);
        retval = pthread_join(cons[i], NULL);
        //printf("Consumer Joined %d\n", i);
        if (retval < 0) {
            printf("Error in joining consumer thread.");
            exit(EXIT_FAILURE);
        }
    }

    // exit 
    printf("\n\nAll tasks complete. Goodbye.\n");
    
    t2 = clock();
    printf("\nElapsed Time: %.6fs\n", (t2 - t1) / (double) CLOCKS_PER_SEC);

    // free memory
    free(producers);
    free(consumers);
    free(buf);

    return (EXIT_SUCCESS);
}

// produces items and fills buffer
void* producer(void* threadAttr) {
    int counter = 0;
    int item;

    struct threadAttr *prodAttr = (struct threadAttr*) threadAttr;
    int id = (*prodAttr).id;

    while (1) {

        // enter synchronized state
        sem_wait(&empty);
        pthread_mutex_lock(&lock);

        if (index < bufSize) {
            // create unique item number based on thread, id, and iteration
            item = counter * threadCount + id;
            // write to buffer
            buf[index] = item;
            if (index > bufSize) {
                //printf("Error\n");
                break;
            }
            index++;
            counter++;
        }
        pthread_mutex_unlock(&lock);
        sem_post(&full);

        if (counter == 1000) {
            //printf("Max reached.\n");
            break;
        }
//        if (id == 3){
//            printf("item: %d\n", item);
//        }
    }
    return NULL;
}

// consumes items within the buffer
void* consumer(void* threadAttr) {
    int itemsConsumed;
    int item;
    struct threadAttr *consAttr = (struct threadAttr*) threadAttr;
    // get thread id
    int id = (*consAttr).id;

    // loop until all items have been consumed
    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&lock);


        // *consume* item
        item = buf[index - 1];
        printf("Consumer #%d consumed item #%d\n", id, item);
        index--;
        itemsConsumed++;
        //printf("Consumer: %d\titemsConsumed: %d\n", id, itemsConsumed);
        if (index < 0) {
            //printf("Error in Consumer\n");
            break;
        }

        pthread_mutex_unlock(&lock);
        sem_post(&empty);

        if (itemsConsumed == 1000) {
            //printf("Consumer %d: All items consumed.\n", id);
            break;
        }
        //        if(id == 0 )
        //            printf("%d\n", itemsConsumed);
    }
    return NULL;
}


