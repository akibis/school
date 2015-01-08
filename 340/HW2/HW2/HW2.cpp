/*
Name: complexity-forLoops.cpp
Copyright: 
Author: hui yang
Date: 21/09/13 13:23
Description: illustrate the complexity of three for-loops
*/

#include <iostream>

using namespace std;

int main()
{
int cnt_per_iter = 0, cnt_tot = 0;

int i=0, j=0, n=7; //loop-rel variables
 
// FIRST LOOP
for (i=0; i<n; i++)
{
cnt_tot+= 1;
}

cout << "After finishing the 1st for-loop: i=" << i
<< "; cnt_tot=" << cnt_tot << "\n\n";

//initialize the counting variables for the next loop	
cnt_per_iter = 0; 
cnt_tot = 0;

// SECOND LOOP
for (i=0; i<n; i++)
{	

j = 0;
cout << "starting iteration (i, j)=(" << i << "," << j << "):";	
cnt_per_iter = 0;
for (j; j<n; j++){
cnt_per_iter += 1;
cnt_tot += 1;
}
cout << " ...finished! (i, j)=(" << i << "," << j << "):" 
<< "cnt_per_iter=" << cnt_per_iter <<endl;
}
cout << "After finishing the 2nd for-loop: i=" << i
<< "; j=" << j 
<< "; cnt_tot=" << cnt_tot << "\n\n";

//initialize the counting variables for the next loop	
cnt_per_iter = 0; 
cnt_tot = 0;

// THIRD LOOP
for (i=0; i<n; i++)
{	

j = i;
cout << "starting iteration (i, j)=(" << i << "," << j << "):";	
cnt_per_iter = 0;

for (j; j<n; j++){
cnt_per_iter += 1;
cnt_tot += 1;
}
cout << " ...finished! (i, j)=(" << i << "," << j << "):" 
<< "cnt_per_iter=" << cnt_per_iter <<endl;
}
cout << "After finishing the 3rd for-loop: i=" << i
<< "; j=" << j 
<< "; cnt_tot=" << cnt_tot << "\n\n";

return(0);
}