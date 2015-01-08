#ifndef _FDIFF_H_
#define _FDIFF_H_

#define dataAt(DATA, I, J, W) DATA[(I) * (W) + J]

void updateGrid(float *, float *, int);
void printGrid(float *, int);
void printMid(float g[], int w, int r);
void initGrid(float [], float [], int);
void dumpGrid(float g[], int w);

#endif
