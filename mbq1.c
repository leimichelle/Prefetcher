#include <stdio.h>

#define NSETS 32

struct s {
    int a;
    int b;
    int c;
    int d;
};
// compiled 
int main(int argc, char* argv[]) {
    /*In my configuration, I have a 64-set direct-mapped cache with an 8-byte cache line*/
    struct s a[NSETS];
    int i;
    /*Each struct accesses two cache-lines, and only accesses each once. Therefore, without a prefetcher, it will suffer from cache misses, because the same cache-line is never accessed more than once. With the next-line prefetcher, if I write to the array of struct s sequentially, I should get an almost 0% L1 miss rate because the prefetcher always prefetches the next cache-line.*/
    for (i=0; i<NSETS; i++) {
        a[i].a = i;
        a[i].c = i;
    }
    return 0;
}
