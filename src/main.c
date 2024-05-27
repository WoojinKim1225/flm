#include <stdio.h>
#include "include/flm.h"


int main(int argc, char** argv) {
    
    if (argc < 2) {
        printf("Please specify input file\n");
        return 1;
    }
    
    flmCompileFile(argv[1]);

    return 0;
}