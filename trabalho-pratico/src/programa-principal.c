#include "../includes/controller/batchC.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
    if (argc == 3){
        run_batch(argv[1], argv[2]);
    }
    return 0;
}