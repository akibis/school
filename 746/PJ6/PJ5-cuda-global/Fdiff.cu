/*************************

   File: Fdiff_CUDA.c
   Compile: nvcc Fdiff_CUDA.cu Fdutils_CUDA.cu -O3 -o FdGPU -lm
   Use: ./Fd [input file] [tile size]  | qsub -d `pwd` -q fermi.q
        ./Fd [input file] [tile size]  | qsub -d `pwd` -q g92.q

   Performs 4 nearest neighbor updates on 2-D grid
   Input file format:

   # cycles
   width of grid (including boundary)
   # initial data points

   3 integers per data point: i and j indices, data


*************************/

#include <stdio.h>
#include <stdlib.h>
#include "Fdiff.h"
#include "cuda.h"

int main(int arg, char **argv) {
  int width;
  int numCycles;
  int i, j, n;
  float *u0, *u1, *tptr;
  double inTemp;
  int cycle = 0;
  int numInit;

  // value of second command line argument
  //int TILE_SIZE = atoi(argv[2]);

  //printf("Tile: %d\n", TILE_SIZE);
  //faceprintf("success.\n");
  FILE *fp;

  fp = fopen(argv[1], "r");

  // first three values in file
  fscanf(fp, "%d", &numCycles);
  fscanf(fp, "%d", &width);
  fscanf(fp, "%d", &numInit);
  printf("# cycles %d width %d # initializations %d\n", numCycles, width, numInit);

//  printf("Tile size: %d\n", TILE_SIZE);
  u0 = (float *) calloc(width * width, sizeof(float));
  u1 = (float *) calloc(width * width, sizeof(float));

  // Create CUDA timers
  float elapsed_time;
  cudaEvent_t start_timer, stop_timer;
  cudaEventCreate(&start_timer);
  cudaEventCreate(&stop_timer);

  // Allocate memory on device
  int memory_size = width * width * sizeof(float);
  float *device_u0, *device_u1;
  cudaMalloc((void**) &device_u0, memory_size);
  cudaMalloc((void**) &device_u1, memory_size);

  initGrid(u0, u1, width);

  for (n=0; n<numInit; n++) {
    fscanf(fp, "%d%d%lf", &i, &j, &inTemp);
    dataAt(u1, i, j, width) = inTemp;
  }

  // printGrid(u1, width);

  // Start timer
  cudaEventRecord(start_timer, 0);

  // Copy from host to device
  cudaMemcpy(device_u0, u0, memory_size, cudaMemcpyHostToDevice);
  cudaMemcpy(device_u1, u1, memory_size, cudaMemcpyHostToDevice);

  // Tile size is limited by hardware, allowing a maximum of 1024 threads per block.
  // So max width for 2D grid is 32.
  int blockWidth = (width/10); // 10 is most optimal value
  int TILE_SIZE = width / blockWidth; // Round up

//  if (TILE_SIZE > 10)
//	  TILE_SIZE = 10;
  dim3 numBlocks ((width/TILE_SIZE), (width/TILE_SIZE));
  dim3 numThreads (TILE_SIZE, TILE_SIZE);

  printf("blockWidth: %d\n", ((width + TILE_SIZE -1)/TILE_SIZE));
  printf("width: %d, TILE_SIZE: %d\n", width, TILE_SIZE);
  printf("numBlocks: %d, numThreadsPerBlock: %d\n", (width*width)/(TILE_SIZE*TILE_SIZE), (TILE_SIZE*TILE_SIZE));

  for (cycle=0; cycle<numCycles; cycle++) {
    // updateGrid(u0, u1, width);
    // printGrid(u0, width);
    // Threads--

	/*
	 * Passing int args to kernel is only for 1D data sets. If you want to set up different data,
	 * have to declare different dims.
	 *
	 * Ex:
	 *
	 * 	dim2 numBlocks(width/TILE_SIZE, width/TILE_SIZE);
	 * 	dim2 numThreads(TILE_SIZE, TILE_SIZE);
	 *
	 * 	### ONLY WORKS FOR KERNEL CODE ###
	 * 	numBlocks.x = width/TILE_SIZE;
	 * 	numBlocks.y = width/TILE_SIZE;
	 *
	 * 	numThreads.x = TILE_SIZE;
	 * 	numThreads.y = TILE_SIZE;
	 *
	 *  ##################################
	 *
	 */



    updateGrid<<<numBlocks, numThreads>>>(device_u0, device_u1, width, TILE_SIZE);

    // Sync threads
    cudaThreadSynchronize();

    tptr = device_u0;
    device_u0 = device_u1;
    device_u1 = tptr;
  }

  // After finishing, copy data from device to host
  cudaMemcpy(u0, device_u0, memory_size, cudaMemcpyDeviceToHost);
  cudaMemcpy(u1, device_u1, memory_size, cudaMemcpyDeviceToHost);

  // Stop timer, calculate elapsed time
  cudaEventRecord(stop_timer, 0);
  cudaEventSynchronize(stop_timer);
  cudaEventElapsedTime(&elapsed_time, start_timer, stop_timer);

  printf("Elapsed time = %f ms\n", elapsed_time);
  dumpGrid(u1, width);

  //printGrid(u1, width);

  // Free used vars
  free(u0);
  free(u1);
  cudaFree(device_u0);
  cudaFree(device_u1);

}
