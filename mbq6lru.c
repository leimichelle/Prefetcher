#include <stdio.h>

#define NSETS 1000000

// compiled -O1
int main(int argc, char* argv[]) {
    /*In my configuration, I have a 1-set 4-way associative cache with an 16-byte cache line*/
    int a[NSETS];
    int b[NSETS];
    int c[NSETS];
    int i,j;
    /* All cache lines map to the same 4-way set, before the 4th j iteration,
     * this is what the set would look like:
     * head -> c[0-3] -> b[0-3] -> a[0-3] -> tail
     * 
     * With the old replacement policy, prefetch would happen and be placed at the head of queue
     * Regular stride 4th iteration:
     * head -> a[4-7] -> a[0-3] -> c[0-3] -> b[0-3] -> tail
     * head -> b[4-7] -> b[0-3] -> a[4-7] -> a[0-3] -> tail
     * head -> c[4-7] -> c[0-3] -> b[4-7] -> b[0-3] -> tail ***miss***
     * Next loop, 1st iteration:
     * head -> a[0-3] -> c[4-7] -> c[0-3] -> b[4-7] -> tail ***miss***
     * head -> b[0-3] -> a[0-3] -> c[4-7] -> c[0-3] -> tail ***miss***
     * 
     * As you can see, the useless [4-7] blocks push out the useful [0-3] blocks
     * 
     * With the new replacement policy, prefetches get put at the end of the the tail
     * New replacement policy 4th iteration:
     * head -> a[0-3] -> c[0-3] -> b[0-3] -> a[4-7] -> tail
     * head -> b[0-3] -> a[0-3] -> c[0-3] -> b[4-7] -> tail
     * head -> c[0-3] -> b[0-3] -> a[0-3] -> c[4-7] -> tail
     * 
     * As you can see, the useless [4-7] blocks will just push each other out of the queue
     * and no misses will occur
     * /
    for (i=0; i<NSETS; i++) {
      for (j=0; j<4; j++) {
        a[j] = j;
        b[j] = j;
        c[j] = j;
      }
    }
    return 0;
}

