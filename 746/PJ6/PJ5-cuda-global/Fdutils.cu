#include <stdio.h>
#include "Fdiff.h"

/****

     tu[] is input grid
     u[] is output grid
     w is width of grid

     compute 4-nearest neighbor updates

****/

/*
void updateGrid(double u[], double tu[], int w) {
  int i, j;
  double uv2;

  for (i=1; i<w-1; i++) {
    for (j=1; j<w-1; j++) {

      dataAt(u, i, j, w) = .25 * (dataAt(tu, i+1, j, w)
                                  + dataAt(tu, i-1, j, w)
                                  + dataAt(tu, i, j+1, w)
                                  + dataAt(tu, i, j-1, w));
    }
  }
}*/


__global__ void updateGrid(float u[], float tu[], int w, int tile) {

	//printf("in gpu.\n");
  // Calculate i, j based on thread
  int i = blockDim.x * blockIdx.x + threadIdx.x;
  int j = blockDim.y * blockIdx.y + threadIdx.y;

  //printf("i = %d | j = %d\n", i, j);

  //printf("blockDim.x: %d | blockIdx.x: %d | threadIdx.x: %d\n", blockDim.x, blockIdx.x, threadIdx.x);
  //printf("blockDim.y: %d | blockIdy.y: %d | threadIdy.y: %d\n", blockDim.x, blockIdx.x, threadIdx.x);

  // Deleted for loops from the original code;
  // Each point in the grid is updated by a thread now
  if((i>0 && i < w-1) && (j>0 && j < w-1))
    dataAt(u, i, j, w) = .25f * (dataAt(tu, i+1, j, w) + dataAt(tu, i-1, j, w) + dataAt(tu, i, j+1, w) + dataAt(tu, i, j-1,w));

}

void printGrid(float g[], int w) {
  int i, j;

  for (i=0; i<w; i++) {
    for (j=0; j<w; j++) {
      printf("%7.3f ", dataAt(g, i, j, w));
    }
    printf("\n");
  }
}

void dumpGrid(float g[], int w) {
  int i, j;
  FILE *fp;

  fp = fopen("./dump.out", "w");

  for (i=0; i<w; i++) {
    for (j=0; j<w; j++) {
      fprintf(fp, "%f ", dataAt(g, i, j, w));
    }
    fprintf(fp, "\n");
  }
  fclose(fp);
}

void initGrid(float u0[], float u1[], int w) {
  int i, j;

  for (i=0; i<w; i++) {
    for (j=0; j<w; j++) {
      dataAt(u0, i, j, w) = 0.;
      dataAt(u1, i, j, w) = 0.;
    }
  }
}
