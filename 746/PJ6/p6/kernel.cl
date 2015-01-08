__kernel void updateGrid(__global float u[], __global float tu[], int w, int tile) {

	//printf("in gpu.\n");
  // Calculate i, j based on thread
  int i = get_global_id(0);
  int j = get_global_id(1);

  //printf("i = %d | j = %d\n", i, j);

  //printf("blockDim.x: %d | blockIdx.x: %d | threadIdx.x: %d\n", blockDim.x, blockIdx.x, threadIdx.x);
  //printf("blockDim.y: %d | blockIdy.y: %d | threadIdy.y: %d\n", blockDim.x, blockIdx.x, threadIdx.x);

  // Deleted for loops from the original code;
  // Each point in the grid is updated by a thread now
  if((i>0 && i < w-1) && (j>0 && j < w-1))
    dataAt(u, i, j, w) = .25f * (dataAt(tu, i+1, j, w) + dataAt(tu, i-1, j, w) + dataAt(tu, i, j+1, w) + dataAt(tu, i, j-1,w));

}