# rawMem
Template based routines to allocate multidimensional arrays using raw pointers.

To use the routines, simply include rawMem.h in your code:

```C++
#include "rawMem.h"

int main(){

    // --- Allocate array --- //
    
    long x0 = 0, x1 = 10, y0 = -5, y1 = 5, z0=1, z1 = 100;
    float ***a = rmem::rarray<float>(z0, z1, y0, y1, x0, x1);


    // --- Do something with it --- //
    a[1][1][1] = 1.0;


    // --- deallocate memory --- //

    rmem::del_rarray(a, z0, y0, x0);
}

```
