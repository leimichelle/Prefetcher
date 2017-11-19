#include <stdio.h>

#define NSETS 128
// compiled with -O0
int main(int argc, char* argv[]) {
    //In my configuration, I have a 64-set direct-mapped cache with an 8-byte cache line,
    //so I would initiate an array of 128 integers (128*4=64*8)to avoid capacity miss 
    int a[NSETS];
    int i;
    //If I write to the array sequentially, I should get an almost zero L1 miss rate because
    //the prefetcher always prefetches the next cache-line.
    for (i=0; i<NSETS; i++) {
        a[i] = i;    
    }
    return 0;
}
