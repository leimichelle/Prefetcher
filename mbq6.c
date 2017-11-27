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
    /*In my configuration, I have a 128-set direct-mapped cache with an 8-byte cache line*/
    struct s a[NSETS];
    int b[NSETS];
    int i,j;
    for (i=0; i<NSETS; i+=3) {
        for (j=0; j<3; j++) {
          a[i+j].a = i+j;
        }
        b[i] = i;
    }
    return 0;
}

