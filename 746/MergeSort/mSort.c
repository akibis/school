/*
  File: mSort.c
  Compile: gcc mSort.c -o mSort
  Use: mSort N
       [N is the number of elements in random list to be sorted]

   or: mSort N P
       [N is the number of elements in random list to be sorted]
       [P is the number of threads]

  Description: generates and sorts a list of random integers
               using merge sort; checks if list is sorted

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
int N = 10; 
int P = 1;

void mergeSort(int *, int);
void merge(int *, int, int *, int);
void checkSort(int *, int);
void allSort(int *, int);

int *x;

int main(int argc, char **argv) {
  int i;
  clock_t t1, t2;

  if (argc != 2 && argc != 3) {
    printf("Usage: mSort [# elements] [optional: # threads]\n");
    exit(0);
  }

  N = atoi(argv[1]);
  printf("Sorting %d integers\n", N);

  if (argc == 3) {
    P = atoi(argv[2]);
  }

  x = (int *) calloc(N, sizeof(int));

  for (i=0; i<N; i++) {
    x[i] = random();
//    printf("%d ", x[i]);
  }
  checkSort(x, N);

  t1 = clock(); /* get timestamp before sort */
  
  allSort(x, N);

  t2 = clock(); /* get timestamp after sort */
  printf("Elapsed: %.4f\n", (t2 - t1) / (double) CLOCKS_PER_SEC);

  checkSort(x, N);

}

/* wrapper for sort; all your code changes go here */

void *multiThread(void * i){
    
    int myId = *((int*) i);
    
    printf("x old = %d\n", x);
    printf("myId value = %d\n", myId);
    printf("x new = %d\n", x);
    
    int numberSplit = N/P;
    printf("to value = %d\n", numberSplit);

    printf("Number check: %d\n", &x[myId * (N/P)]);
    
    
    checkSort(&x[myId * (N/P)], numberSplit);
    mergeSort(&x[myId * (N/P)], numberSplit);
    checkSort(&x[myId * (N/P)], numberSplit);
    
    return NULL;
}

void allSort(int *arg0, int arg1) {

 
    pthread_t threadArray[P];
    int idArray[P];    
    int i;
    for (i=0; i<P; i++){
        idArray[i] = i;
        int retVal = pthread_create(&threadArray[i], NULL, multiThread, (void*) &idArray[i]);
        if (retVal > 0){
            printf("Error occurred in creating thread.\n");
            exit(0);
       }
    }
    for (i=0; i<P; i++){
        int retVal = pthread_join(threadArray[i], NULL);
        if (retVal > 0){
            printf("Error occurred in joining thread.");
            exit(0);
        }
    }
    
// ***** ITIRATIVE THREAD CREATION CHECK *****    
//    pthread_t thread1, thread2;
//    int id0 = 0;
//    int id1 = 1;
    
//    pthread_create(&thread1, NULL, multiThread, (void*) &id0);
//    pthread_create(&thread2, NULL, multiThread, (void*) &id1);
    
//    pthread_join(thread1, NULL);
//    pthread_join(thread2, NULL);
    
    merge(x, N/P, x+(N/P), N/P);
    
//    printf("SORTED LIST\n");
//    int j;
//    for (j=0; j<N; j++) {
//         printf("%d \n", x[j]);
//    }
    
    
    
    
    
    
    
//    mergeSort(arg0, arg1);
//    int i;
//    for (i=0; i<N; i++) {
//    printf("%d ", x[i]);
//  }
}


/* merge sort of arg1 integers, starting at arg0 */

void mergeSort(int *arg0, int arg1)
{
  int temp, count, *local, *ptr0, *ptr1, *ptr, count0, count1;

  if (arg1==1)
    return;
  else if (arg1==2) {
    if (*arg0 > *(arg0+1)) {
      temp = *arg0;
      *arg0 = *(arg0+1);
      *(arg0+1) = temp;
    }
    return;
  }
  else {
    count = arg1 / 2;
    ptr0 = arg0;
    ptr1 = arg0+count;
    mergeSort(ptr0, count);
    mergeSort(ptr1, arg1 - count);
    merge(ptr0, count, ptr1, arg1 - count);
    return;
  }
}

/* merge two sorted lists, starting at p0 and p1 */
/* p0 has c0 elements, p1 has c1 elements */
/* copy resulting list to starting address p0 */

void merge(int *p0, int c0, int *p1, int c1) {
  int * local, *list, count, totCount;

  list = p0;
  local = (int *) calloc(c0 + c1,sizeof(int));
  count = c0 + c1;
  totCount = count;
  while (count > 0) {
    if (*p0 > *p1) {
      *local = *p1;
      p1++;
      c1--;
    }
    else {
      *local = *p0;
      p0++;
      c0--;
    }
    count--;
    local++;
    if ((c0 == 0) || (c1 == 0))
      break;
  }
  if (count!=0) {
    if (c0 == 0)
      while (c1 > 0) {
	*local = *p1;
	p1++;
	local++;
	c1--;
      }
    else {
      while (c0 > 0) {
	*local = *p0;
	p0++;
	local++;
	c0--;
      }
    }
  }
  
  local = local - totCount;
  for (count=0;count<totCount;count++)
    *list++ = *local++;  
}

void checkSort(int *data, int num) {
  int i;
  int flag = 0;

  for (i=0; i<num-1; i++) {
    if (data[i] > data[i+1]) {
      flag = 1;
      break;
    }
  }
  if (flag == 0)
    printf("data is sorted\n");
  else
    printf("data is not sorted\n");
}