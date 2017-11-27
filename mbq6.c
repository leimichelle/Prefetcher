#include <stdio.h>

#define NSETS 1000000

struct s {
    int a;
    int b;
    int c;
    int d;
};
// compiled -O2
int main(int argc, char* argv[]) {
    /*In my configuration, I have a 64-set direct-mapped cache with an 8-byte cache line*/
    /*Also, the size of the RPT table has been manually recompiled to 1*/
    struct s a[NSETS];
    int b[NSETS];
    int i,j;
    /* This micro-benchmark tests the new RPT eviction policy */
    for (i=0; i<NSETS; i+=3) {
        /*Within each iteration, the instr falls into a steady state, with stride 16*/
        for (j=0; j<3; j++) {
          a[i+j].a = i+j;
        }
        /*Without the eviction policy, this instr would have overwritten the above entry
         * causing first a miss on variable 'b', then in the next iteration, 'a' would miss once
         * because when it gets reinitialized into the RPT no prefetch is made
         * 
         * With the new eviction policy, this instr just causes the RPT entry for 'a' to go from
         * steady state to init state, which is fine because, 'a' would still keep prefetching
         * in the next loop iteration
         * /
        b[i] = i;
    }
    return 0;
}

