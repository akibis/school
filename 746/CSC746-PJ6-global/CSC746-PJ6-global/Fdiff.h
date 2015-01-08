#ifndef _FDIFF_H_
#define _FDIFF_H_

#define dataAt(DATA, I, J, W) DATA[(I) * (W) + J]

// void updateGrid(double *, double *, int);
//__global__ void updateGrid(float *, float *, int, int);
// converting doubles to float after getting the following error:
// ptxas /tmp/tmpxft_00007261_00000000-5_Fdutils_CUDA.ptx, line 91; warning : Double is not supported. Demoting to float
void printGrid(float *, int);
void printMid(float g[], int w, int r);
void initGrid(float [], float [], int);
void dumpGrid(float g[], int w);

#endif