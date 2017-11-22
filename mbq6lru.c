#include <stdio.h>

#define NSETS 1000000

// compiled -O1
int main(int argc, char* argv[]) {
    /*In my configuration, I have a 128-set direct-mapped cache with an 8-byte cache line*/
    int a[NSETS];
    int b[NSETS];
    int c[NSETS];
    int i,j;
    /*Each iteration accesses a cache-line that is more than one cache-line apart from the previous iteration, so a next-line prefetcher would not work well for this certain memory access pattern. However, a stride prefetcher can capture the stride pattern to prefetch, which is more flexible than the next-line prefetcher in this sense. The stride prefetcher has a near 0 miss rate for the following access pattern.*/
    for (i=0; i<NSETS; i++) {
      for (j=0; j<4; j++) {
        a[j] = j;
        b[j] = j;
        c[j] = j;
      }
    }
    return 0;
}

