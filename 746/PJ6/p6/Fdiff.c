/*************************

   File: Fdiff.c
   Compile: gcc Fdiff.c Fdutils.c -O3 -o gpu -l OpenCL
   Use: ./gpu [input file] [tile size]  | qsub -d `pwd` -q fermi.q
        ./gpu [input file] [tile size]  | qsub -d `pwd` -q g92.q

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
#include <CL/cl.h>
//#include <sys/time.h>


#define MAX_SOURCE_SIZE (0x100000)

void printError(cl_int err)
{
    switch (err) {
        case CL_SUCCESS:                            printf("\nSuccess!\n"); return;
        case CL_DEVICE_NOT_FOUND:                   printf("\nDevice not found.\n"); return;
        case CL_DEVICE_NOT_AVAILABLE:               printf("\nDevice not available\n"); return;
        case CL_COMPILER_NOT_AVAILABLE:             printf("\nCompiler not available\n"); return;
        case CL_MEM_OBJECT_ALLOCATION_FAILURE:      printf("\nMemory object allocation failure\n"); return;
        case CL_OUT_OF_RESOURCES:                   printf("\nOut of resources\n"); return;
        case CL_OUT_OF_HOST_MEMORY:                 printf("\nOut of host memory\n"); return;
        case CL_PROFILING_INFO_NOT_AVAILABLE:       printf("\nProfiling information not available\n"); return;
        case CL_MEM_COPY_OVERLAP:                   printf("\nMemory copy overlap\n"); return;
        case CL_IMAGE_FORMAT_MISMATCH:              printf("\nImage format mismatch\n"); return;
        case CL_IMAGE_FORMAT_NOT_SUPPORTED:         printf("\nImage format not supported\n"); return;
        case CL_BUILD_PROGRAM_FAILURE:              printf("\nProgram build failure\n"); return;
        case CL_MAP_FAILURE:                        printf("\nMap failure\n"); return;
        case CL_INVALID_VALUE:                      printf("\nInvalid value\n"); return;
        case CL_INVALID_DEVICE_TYPE:                printf("\nInvalid device type\n"); return;
        case CL_INVALID_PLATFORM:                   printf("\nInvalid platform\n"); return;
        case CL_INVALID_DEVICE:                     printf("\nInvalid device\n"); return;
        case CL_INVALID_CONTEXT:                    printf("\nInvalid context\n"); return;
        case CL_INVALID_QUEUE_PROPERTIES:           printf("\nInvalid queue properties\n"); return;
        case CL_INVALID_COMMAND_QUEUE:              printf("\nInvalid command queue\n"); return;
        case CL_INVALID_HOST_PTR:                   printf("\nInvalid host pointer\n"); return;
        case CL_INVALID_MEM_OBJECT:                 printf("\nInvalid memory object\n"); return;
        case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:    printf("\nInvalid image format descriptor\n"); return;
        case CL_INVALID_IMAGE_SIZE:                 printf("\nInvalid image size\n"); return;
        case CL_INVALID_SAMPLER:                    printf("\nInvalid sampler\n"); return;
        case CL_INVALID_BINARY:                     printf("\nInvalid binary\n"); return;
        case CL_INVALID_BUILD_OPTIONS:              printf("\nInvalid build options\n"); return;
        case CL_INVALID_PROGRAM:                    printf("\nInvalid program\n"); return;
        case CL_INVALID_PROGRAM_EXECUTABLE:         printf("\nInvalid program executable\n"); return;
        case CL_INVALID_KERNEL_NAME:                printf("\nInvalid kernel name\n"); return;
        case CL_INVALID_KERNEL_DEFINITION:          printf("\nInvalid kernel definition\n"); return;
        case CL_INVALID_KERNEL:                     printf("\nInvalid kernel\n"); return;
        case CL_INVALID_ARG_INDEX:                  printf("\nInvalid argument index\n"); return;
        case CL_INVALID_ARG_VALUE:                  printf("\nInvalid argument value\n"); return;
        case CL_INVALID_ARG_SIZE:                   printf("\nInvalid argument size\n"); return;
        case CL_INVALID_KERNEL_ARGS:                printf("\nInvalid kernel arguments\n"); return;
        case CL_INVALID_WORK_DIMENSION:             printf("\nInvalid work dimension\n"); return;
        case CL_INVALID_WORK_GROUP_SIZE:            printf("\nInvalid work group size\n"); return;
        case CL_INVALID_WORK_ITEM_SIZE:             printf("\nInvalid work item size\n"); return;
        case CL_INVALID_GLOBAL_OFFSET:              printf("\nInvalid global offset\n"); return;
        case CL_INVALID_EVENT_WAIT_LIST:            printf("\nInvalid event wait list\n"); return;
        case CL_INVALID_EVENT:                      printf("\nInvalid event\n"); return;
        case CL_INVALID_OPERATION:                  printf("\nInvalid operation\n"); return;
        case CL_INVALID_GL_OBJECT:                  printf("\nInvalid OpenGL object\n"); return;
        case CL_INVALID_BUFFER_SIZE:                printf("\nInvalid buffer size\n"); return;
        case CL_INVALID_MIP_LEVEL:                  printf("\nInvalid mip-map level\n"); return;
        default: printf("\nUnknown\n"); return;
    }
}

int main(int arg, char **argv) {
  int width;
  int numCycles;
  int i, j, n;
  float *u0, *u1;
  float inTemp;
  int cycle = 0;
  int numInit;
  int TILE_SIZE = 10;

  // value of second command line argument
  //int TILE_SIZE = atoi(argv[2]);

  //printf("Tile: %d\n", TILE_SIZE);
  //faceprintf("success.\n");
  FILE *fp; // input file pointer
  FILE *kp; // kernel file pointer
  char *source_str;
  size_t source_size;

  fp = fopen(argv[1], "r");

    // read input file
    fscanf(fp, "%d", &numCycles);
    fscanf(fp, "%d", &width);
    fscanf(fp, "%d", &numInit);
    printf("# cycles %d width %d # initializations %d\n", numCycles, width, numInit);


//  Allocate host memory
  u0 = (float *) calloc(width * width, sizeof(float));
  u1 = (float *) calloc(width * width, sizeof(float));
  initGrid(u0, u1, width);

      // input values
    for (n=0; n<numInit; n++) {
      fscanf(fp, "%d%d%f", &i, &j, &inTemp);
      dataAt(u1, i, j, width) = inTemp;
    }
    
      kp = fopen("kernel.cl", "r");
    if (!kp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }

  source_str = (char*)malloc(MAX_SOURCE_SIZE);
  source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
  fclose( fp );	
	
	
	fclose(fp);
/*


BEGIN OPENCL INITIALIZATION


*/

// Get platform and device information
  cl_platform_id platform_id = NULL;
  cl_device_id device_id = NULL;   
  cl_uint ret_num_devices;
  cl_uint ret_num_platforms;
  cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
  
  // get ids

  printf("Getting IDs\n");
  
  ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_DEFAULT, 1, 
            &device_id, &ret_num_devices);

// Create an OpenCL context
  printf("Creating Context\n");
  cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);

// Create a command queue
  printf("Creating queue\n");
  cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

/*

END INITIALIZATION


*/

  // Allocate memory on device
  printf("Allocating memory\n");
  int memory_size = width * width * sizeof(float);
  cl_mem device_u0 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, memory_size, NULL, &ret);
  cl_mem device_u1 = clCreateBuffer(context, CL_MEM_READ_ONLY, memory_size, NULL, &ret);  

  initGrid(u0, u1, width);
  

  // printGrid(u1, width);

  // Start timer
//  struct timeval tv;
//  gettimeofday(&tv, NULL);
//  double t0 = tv.tv_sec*1e6 + tv.tv_usec;

  // Copy from host to device
  printf("Copy from host to device\n");
  ret = clEnqueueWriteBuffer(command_queue, device_u1, CL_TRUE, 0, memory_size, u1, 0, NULL, NULL);

  // Create a program from the kernel source
    printf("\nCreating program");
    cl_program program = clCreateProgramWithSource(context, 1, 
		(const char **)&source_str, (const size_t *)&source_size, &ret);
    printError(ret);


  // Build the program
    printf("\nBuilding program");
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    printError(ret);

  // Create the OpenCL kernel
	printf("Create kernel\n");
    cl_kernel kernel = clCreateKernel(program, "updateGrid", &ret);

	size_t global_size = (width * width) / (TILE_SIZE * TILE_SIZE);
	size_t local_size = TILE_SIZE * TILE_SIZE;

	// create temp device variable
	cl_mem temp = NULL;

// run loop
	printf("Start loop.\n");
  for (cycle=0; cycle<numCycles; cycle++) {


  // Set kernel args
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&device_u0);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&device_u1);
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&width);
	ret = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void *)&TILE_SIZE);

    // Execute the OpenCL kernel on the list

    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, 
            &global_size, &local_size, 0, NULL, NULL);
	printError(ret);

    temp = device_u0;
    device_u0 = device_u1;
    device_u1 = temp;

  }
   
    // Read the memory buffer C on the device to the local variable C
    int *C = (int*)malloc(sizeof(int)*TILE_SIZE);
    ret = clEnqueueReadBuffer(command_queue, device_u1, CL_TRUE, 0, 
            width * width * sizeof(int), u1, 0, NULL, NULL);


//    gettimeofday(&tv, NULL);
//    double t1 = tv.tv_sec*1e6 + tv.tv_usec;
//    printf("Elapsed GPU time = %f ms\n", (t1-t0)*1e-3);
  dumpGrid(u1, width);

  //printGrid(u1, width);

  // Free used vars
   // Clean up
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(device_u0);
    ret = clReleaseMemObject(device_u1);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    free(u0);
    free(u1);

}
