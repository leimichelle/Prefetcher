#include <stdio.h>

#define NSETS 1000000

struct s {
  int a;
  int b;
};
// compiled with -O2 
int main(int argc, char* argv[]) {
    /*In my configuration, I have a 64-set direct-mapped cache with an 8-byte cache line*/
    struct s a[NSETS];
    int i;
    /*Each struct fits in one cache-line. Without a prefetcher, it will suffer 
     * from cache misses, because the same cache-line is never accessed more than once.
     * With the next-line prefetcher, if I write to the array of struct s sequentially,
     * I should get an almost 0% L1 miss rate because the prefetcher always prefetches
     * the next cache-line.*/
    for (i=0; i<NSETS; i++) {
        a[i].a = i;
    }
    return 0;
}
