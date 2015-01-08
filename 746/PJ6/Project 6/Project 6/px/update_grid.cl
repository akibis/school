__kernel void update_grid(__global float *u0, __global float *u1, __global const int *width_ptr) {
 
    // Get the index of the current element to be processed
    int id = get_global_id(0);

    // get width of the grid
    int width = width_ptr[0];

    // row and column
	int row = id / width;
	int col = id % width;

	// the points on the border doesn't update
	if (row > 0 && 
	    col > 0 && 
	    row < width - 1 && 
	    col < width - 1)
	{
	  // update point using its neighboors' values
	  u0[row * width + col] = .25 * (u1[(row+1) * width + col]
	        + u1[(row-1) * width + col]
	        + u1[row * width + (col+1)]
	        + u1[row * width + (col-1)]);
	}
}