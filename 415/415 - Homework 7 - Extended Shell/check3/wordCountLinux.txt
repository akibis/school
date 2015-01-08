#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFSIZE 81920 //80 kb
#define NUM_THREADS 1

void *countWords(void *);//multithreaded method for counting words
int wordCount = 0;//global variable
pthread_mutex_t mutex;//global lock because each thread is gonna use it
char data[BUFFSIZE];//global buffer


struct bufferPartition
{
    int start;
    int end;
};

int main(int argc, char *argv[])
{
    clock_t t1,t2;
    int bytesRead = 1;
    struct bufferPartition partitions[NUM_THREADS];
    pthread_t tid[NUM_THREADS];//array of thread ids
    int i,totalBytes;
    int offset=0;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_mutex_init(&mutex,NULL);
    

    if (argc != 2)
    {
        fprintf(stderr,"Error, wrong number of arguments\n");
        return(1);
    }
    
    int fd1 = open(argv[1],O_RDONLY);
    
    if (fd1 == -1)
    {
        fprintf(stderr,"Error opening of file\n");
        return(1);
    }
    
    while(bytesRead > 0)
    {
        bytesRead = read(fd1,data,BUFFSIZE);
        totalBytes = totalBytes + bytesRead;
    }
    
    if (bytesRead == -1)
    {
        fprintf(stderr,"Error reading file\n");
        return(1);
    }
    else
        close(fd1);
    
    
    int partitionSizes[NUM_THREADS];
    int bufferBytes = 0;
    
    //evenly as possible divide partitions----
    for (i=0; i < NUM_THREADS;i++)
    {
        partitionSizes[i] = totalBytes/NUM_THREADS;
    }
    for (i = 0; i < totalBytes % NUM_THREADS;i++)
    {
        partitionSizes[i] += 1;
    }
    //----------------------------------------
    
    
    t1 = clock();
    for(int i = 0; i < NUM_THREADS; i++)
    {
        if(i == 0)
        {
            //starting, make lower bound 0
            partitions[i].start = 0;
        }
        else
        {
            //make lower bound of current partition the upperbound+1 of previous part
            partitions[i].start = (partitions[i - 1].end) + 1;
        }
        //upperbound is the current partitions lower bound + a division of the bytes
        partitions[i].end = partitions[i].start + (partitionSizes[i]);
        
        //while the upperbound still lands in between a word, move the upperbound up 1
        while(isalnum(data[partitions[i].end]))
        {
            (partitions[i].end)++;
        }
        
        //create thread with currently set upper and lower bound partition
        pthread_create(&tid[i], &attr, countWords, &partitions[i]);
    }
    
    for(int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(tid[i], NULL);
    }
    t2 = clock();
    printf("Elapsed: %.4f\n", (t2 - t1) / (double) CLOCKS_PER_SEC);
    printf("Running with %d threads,\n", NUM_THREADS);
    printf("The file contains %d words.\n", wordCount);
    pthread_exit(NULL);
    return 0;
}

void* countWords(void* arg)
{
    //bring in the current partition struct from arg
    struct bufferPartition *currentPart = arg;
    pthread_mutex_lock(&mutex);
    //if the lower bound of current partition is a word,
    //should always count a word at start of partition,
    if(isalnum(data[currentPart->start]))
    {
        wordCount++;
    }
    //beginning from second char of partition(since first one was already counted)
    //up to the upperbound of partition -1
    for(int i = (currentPart->start) + 1; i < (currentPart->end) - 1; i++)
    {
        int j = i + 1;
        //increment if word char is found after a nonword char
        if(!isalnum(data[i]) && isalnum(data[j]))
        {
            wordCount++;
        }
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}
