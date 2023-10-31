#include "../../includes/model/catalog.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
    if (argc == 3){
        run_batch(argv);
    }
    return 0;
}