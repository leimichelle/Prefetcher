#include <stdio.h>

#define NSETS 1000000

// compiled -O1
int main(int argc, char* argv[]) {
    /*In my configuration, I have a 128-set direct-mapped cache with an 8-byte cache line*/
    int a[NSETS];
    int b[NSETS];
    int c[NSETS];
    int i,j;
    for (i=0; i<NSETS; i++) {
      for (j=0; j<4; j++) {
        a[j] = j;
        b[j] = j;
        c[j] = j;
      }
    }
    return 0;
}

