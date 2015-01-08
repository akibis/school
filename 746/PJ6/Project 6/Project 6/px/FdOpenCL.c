#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "Fdiff.h"

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif
 
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
 
int main(int argc, char **argv) {

    FILE *input;
    int width;
    int numCycles;
    int i, j, n;
    float *u0, *u1;
    float inTemp;
    int cycle = 0;
    int numInit;
    int tile;

    // usage
    if (argc != 3)
    {
      printf("Usage: ./Fd [input file] W");
      exit(0);
    }
    
    // read arguments
    input = fopen(argv[1], "r");
    tile = atoi(argv[2]);
    
    // read input file
    fscanf(input, "%d", &numCycles);
    fscanf(input, "%d", &width);
    fscanf(input, "%d", &numInit);
    printf("# cycles %d width %d # initializations %d\n", numCycles, width, numInit);
    
    // init grids on the host
    u0 = (float *) calloc(width * width, sizeof(float));
    u1 = (float *) calloc(width * width, sizeof(float));
    initGrid(u0, u1, width);
    
    // input values
    for (n=0; n<numInit; n++) {
      fscanf(input, "%d%d%f", &i, &j, &inTemp);
      dataAt(u1, i, j, width) = inTemp;
    }
    fclose( input );
 
    // Load the kernel source code into the array source_str
    FILE *fp;
    char *source_str;
    size_t source_size;
 
    fp = fopen("update_grid.cl", "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose( fp );
 
    // Get platform and device information
    printf("\nGetting platform");
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    printError(ret);

    printf("\nGetting devices");
    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_DEFAULT, 1, 
            &device_id, &ret_num_devices);
    printError(ret);
 
    // Create an OpenCL context
    printf("\nCreating OpenCL context");
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
    printError(ret);
 
    // Create a command queue
    printf("\nCreating command queue");
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
    printError(ret);
 
    // Create memory buffers on the device 
    printf("\nCreating memory buffer 0");
    cl_mem u0_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, 
            width * width * sizeof(float), NULL, &ret);
    printError(ret);
    printf("\nCreating memory buffer 1");
    cl_mem u1_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE,
            width * width * sizeof(float), NULL, &ret);
    printError(ret);
    printf("\nCreating memory buffer 3");
    cl_mem width_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
            sizeof(int), NULL, &ret);
    printError(ret);
    cl_mem temp_mem_obj = NULL;


    // Start recording time
    struct timeval tv;
    gettimeofday(&tv, NULL);
    double t0 = tv.tv_sec*1e6 + tv.tv_usec;

 
    // Copy the grids u0 and u1 to their respective memory buffers
    printf("\nCopying grid 0 to memory buffer 0");
    ret = clEnqueueWriteBuffer(command_queue, u0_mem_obj, CL_TRUE, 0,
            width * width * sizeof(float), u0, 0, NULL, NULL);
    printError(ret);
    printf("\nCopying grid 1 to memory buffer 1");
    ret = clEnqueueWriteBuffer(command_queue, u1_mem_obj, CL_TRUE, 0, 
            width * width * sizeof(float), u1, 0, NULL, NULL);
    printError(ret);
    printf("\nCopying width of the grid to memory buffer");
    ret = clEnqueueWriteBuffer(command_queue, width_mem_obj, CL_TRUE, 0, 
            sizeof(int), &width, 0, NULL, NULL);
    printError(ret);
 
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
    printf("\nCreating kernel");
    cl_kernel kernel = clCreateKernel(program, "update_grid", &ret);
    printError(ret);

    // Execute the OpenCL kernel on the list
    size_t global_item_size = (((width * width) / (tile * tile)) + 1) * tile * tile; // <--- I make it evenly divisible by the local size
    size_t local_item_size = tile * tile; 

    // main loop
    for (cycle=0; cycle<numCycles; cycle++) {
 
    // Set the arguments of the kernel
        ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&u0_mem_obj);
        ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&u1_mem_obj);
        ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&width_mem_obj);


        /* debug
        printf("\n\n----------------------------------------------------------------------------------\nBefore:\n");
        float *tmp = (float *) malloc(width * width * sizeof(float));
        clEnqueueReadBuffer(command_queue, u0_mem_obj, CL_TRUE, 0, width * width * sizeof(float), tmp, 0, NULL, NULL);
        printGrid(tmp, width);*/
        
        printf("\nExecuting kernel at cycle %d", cycle);
        ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, 
                &global_item_size, &local_item_size, 0, NULL, NULL);
        printError(ret);

        /* debug
        printf("\nAfter:\n");
        clEnqueueReadBuffer(command_queue, u0_mem_obj, CL_TRUE, 0, width * width * sizeof(float), tmp, 0, NULL, NULL);
        printGrid(tmp, width);
        free(tmp);
        printf("----------------------------------------------------------------------------------\n");*/

         // swap grids
        temp_mem_obj = u0_mem_obj;
        u0_mem_obj = u1_mem_obj;
        u1_mem_obj = temp_mem_obj;
    }
    
    // Read the memory buffer u1 on the device to the local variable u1
    printf("\nReading memory from buffer to host");
    ret = clEnqueueReadBuffer(command_queue, u1_mem_obj, CL_TRUE, 0, 
            width * width * sizeof(float), u1, 0, NULL, NULL);
    printError(ret);

    // calculate elapsed time
    gettimeofday(&tv, NULL);
    double t1 = tv.tv_sec*1e6 + tv.tv_usec;
    printf("Elapsed GPU time = %f ms\n", (t1-t0)*1e-3);

    // dump results
    dumpGrid(u1, width);

 
    // Clean up
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(u0_mem_obj);
    ret = clReleaseMemObject(u1_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    free(u0);
    free(u1);
    return 0;
}